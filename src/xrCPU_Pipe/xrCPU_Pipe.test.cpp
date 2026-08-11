#define ENGINE_API
#define ECORE_API

#include "../xrCore/xrCore.h"
#include "../Layers/xrRender/SkeletonXVertRender.h"
#include "bone.h"
#include "xrCPU_Pipe.h"

#include <gtest/gtest.h>

#include <array>
#include <cmath>
#include <cstdint>
#include <vector>

extern xrSkin1W xrSkin1W_x86;
extern xrSkin2W xrSkin2W_x86;
extern xrSkin3W xrSkin3W_x86;
extern xrSkin4W xrSkin4W_x86;

extern xrSkin1W xrSkin1W_SSE;
extern xrSkin2W xrSkin2W_SSE;
extern xrSkin3W xrSkin3W_SSE;
extern xrSkin4W xrSkin4W_SSE;

extern xrSkin4W xrSkin4W_thread;

extern xrPLC_calc3 PLC_calc3_x86;
extern xrPLC_calc3 PLC_calc3_SSE;

extern "C" void __cdecl xrBind_PSGP(xrDispatchTable* T, _processor_info* ID);

namespace
{

struct BoneFixture
{
    std::vector<CBoneInstance> bones;

    explicit BoneFixture(size_t count)
        : bones(count)
    {
    }

    void SetTransform(size_t index, const Fmatrix& matrix)
    {
        bones[index].mRenderTransform = matrix;
    }

    CBoneInstance* data()
    {
        return bones.data();
    }
};

} // namespace

namespace
{

constexpr float EPS = 1e-5f;

void ExpectVec3Near(const Fvector& actual, const Fvector& expected, float eps = EPS)
{
    EXPECT_NEAR(actual.x, expected.x, eps);
    EXPECT_NEAR(actual.y, expected.y, eps);
    EXPECT_NEAR(actual.z, expected.z, eps);
}

Fmatrix Translation(float x, float y, float z)
{
    Fmatrix result;
    result.identity();
    result.translate_over(x, y, z);
    return result;
}

void ExpectRenderVertexEqual(
    const vertRender& actual,
    const Fvector& expectedPosition,
    const Fvector& expectedNormal,
    float expectedU,
    float expectedV)
{
    ExpectVec3Near(actual.P, expectedPosition);
    ExpectVec3Near(actual.N, expectedNormal);

    EXPECT_FLOAT_EQ(actual.u, expectedU);
    EXPECT_FLOAT_EQ(actual.v, expectedV);
}

TEST(XrSkin1W, TransformsVerticesAndCopiesUV)
{
    BoneFixture bones(2);

    bones.SetTransform(0, Translation(10.f, 20.f, 30.f));
    bones.SetTransform(1, Translation(-5.f, 4.f, 7.f));

    std::array<vertBoned1W, 2> src{};

    src[0].P.set(1.f, 2.f, 3.f);
    src[0].N.set(0.f, 1.f, 0.f);
    src[0].u = 0.25f;
    src[0].v = 0.75f;
    src[0].matrix = 0;

    src[1].P.set(4.f, 5.f, 6.f);
    src[1].N.set(1.f, 0.f, 0.f);
    src[1].u = 0.5f;
    src[1].v = 0.125f;
    src[1].matrix = 1;

    std::array<vertRender, 2> dst{};

    xrSkin1W_x86(dst.data(), src.data(), src.size(), bones.data());

    ExpectRenderVertexEqual(
        dst[0],
        Fvector().set(11.f, 22.f, 33.f),
        Fvector().set(0.f, 1.f, 0.f),
        0.25f,
        0.75f);

    ExpectRenderVertexEqual(
        dst[1],
        Fvector().set(-1.f, 9.f, 13.f),
        Fvector().set(1.f, 0.f, 0.f),
        0.5f,
        0.125f);
}

TEST(XrSkin1W, HandlesUnrolledLoopBoundary)
{
    BoneFixture bones(1);
    bones.SetTransform(0, Translation(100.f, 200.f, 300.f));

    for (const u32 count : {0u, 1u, 7u, 8u, 9u, 15u, 16u, 17u, 31u, 32u, 33u})
    {
        std::vector<vertBoned1W> src(count);
        std::vector<vertRender> dst(count);

        for (u32 i = 0; i < count; ++i)
        {
            src[i].P.set(
                static_cast<float>(i),
                static_cast<float>(i + 1),
                static_cast<float>(i + 2));

            src[i].N.set(0.f, 0.f, 1.f);
            src[i].u = static_cast<float>(i) * 0.1f;
            src[i].v = static_cast<float>(i) * 0.2f;
            src[i].matrix = 0;
        }

        xrSkin1W_x86(dst.data(), src.data(), count, bones.data());

        for (u32 i = 0; i < count; ++i)
        {
            ExpectVec3Near(
                dst[i].P,
                Fvector().set(
                    static_cast<float>(i) + 100.f,
                    static_cast<float>(i + 1) + 200.f,
                    static_cast<float>(i + 2) + 300.f));

            ExpectVec3Near(dst[i].N, Fvector().set(0.f, 0.f, 1.f));

            EXPECT_FLOAT_EQ(dst[i].u, src[i].u);
            EXPECT_FLOAT_EQ(dst[i].v, src[i].v);
        }
    }
}

TEST(XrSkin2W, UsesSingleBoneWhenBoneIndicesAreEqual)
{
    BoneFixture bones(1);
    bones.SetTransform(0, Translation(10.f, 20.f, 30.f));

    vertBoned2W src{};
    src.P.set(1.f, 2.f, 3.f);
    src.N.set(0.f, 0.f, 1.f);
    src.u = 0.25f;
    src.v = 0.75f;
    src.matrix0 = 0;
    src.matrix1 = 0;
    src.w = 0.37f;

    vertRender dst{};

    xrSkin2W_x86(&dst, &src, 1, bones.data());

    ExpectRenderVertexEqual(
        dst,
        Fvector().set(11.f, 22.f, 33.f),
        Fvector().set(0.f, 0.f, 1.f),
        0.25f,
        0.75f);
}

TEST(XrSkin2W, InterpolatesBetweenTwoBones)
{
    BoneFixture bones(2);

    bones.SetTransform(0, Translation(10.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 20.f, 0.f));

    vertBoned2W src{};
    src.P.set(1.f, 2.f, 3.f);
    src.N.set(0.f, 0.f, 1.f);
    src.u = 0.5f;
    src.v = 0.75f;

    src.matrix0 = 0;
    src.matrix1 = 1;
    src.w = 0.25f;

    vertRender dst{};

    xrSkin2W_x86(&dst, &src, 1, bones.data());

    // P0 = (11, 2, 3)
    // P1 = (1, 22, 3)
    // lerp(P0, P1, 0.25)
    // = (8.5, 7, 3)
    ExpectRenderVertexEqual(
        dst,
        Fvector().set(8.5f, 7.f, 3.f),
        Fvector().set(0.f, 0.f, 1.f),
        0.5f,
        0.75f);
}

TEST(XrSkin2W, WeightExtremes)
{
    BoneFixture bones(2);

    bones.SetTransform(0, Translation(10.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 20.f, 0.f));

    for (float w : {0.f, 1.f})
    {
        vertBoned2W src{};
        src.P.set(1.f, 2.f, 3.f);
        src.N.set(0.f, 0.f, 1.f);
        src.matrix0 = 0;
        src.matrix1 = 1;
        src.w = w;

        vertRender dst{};

        xrSkin2W_x86(&dst, &src, 1, bones.data());

        const Fvector expected =
            w == 0.f
                ? Fvector().set(11.f, 2.f, 3.f)
                : Fvector().set(1.f, 22.f, 3.f);

        ExpectVec3Near(dst.P, expected);
    }
}

TEST(XrSkin3W, BlendsThreeBones)
{
    BoneFixture bones(3);

    bones.SetTransform(0, Translation(10.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 20.f, 0.f));
    bones.SetTransform(2, Translation(0.f, 0.f, 30.f));

    vertBoned3W src{};

    src.P.set(1.f, 2.f, 3.f);
    src.N.set(0.f, 0.f, 1.f);

    src.m[0] = 0;
    src.m[1] = 1;
    src.m[2] = 2;

    src.w[0] = 0.2f;
    src.w[1] = 0.3f;
    // implicit weight 2 = 0.5

    src.u = 0.125f;
    src.v = 0.875f;

    vertRender dst{};

    xrSkin3W_x86(&dst, &src, 1, bones.data());

    // bone 0: (11, 2, 3) * .2
    // bone 1: (1, 22, 3) * .3
    // bone 2: (1, 2, 33) * .5
    //
    // = (3, 4, 18)
    ExpectRenderVertexEqual(
        dst,
        Fvector().set(3.f, 4.f, 18.f),
        Fvector().set(0.f, 0.f, 1.f),
        0.125f,
        0.875f);
}

TEST(XrSkin3W, UsesRemainingWeightForThirdBone)
{
    BoneFixture bones(3);

    bones.SetTransform(0, Translation(100.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 100.f, 0.f));
    bones.SetTransform(2, Translation(0.f, 0.f, 100.f));

    vertBoned3W src{};

    src.P.set(0.f, 0.f, 0.f);
    src.N.set(0.f, 0.f, 1.f);

    src.m[0] = 0;
    src.m[1] = 1;
    src.m[2] = 2;

    src.w[0] = 0.25f;
    src.w[1] = 0.25f;

    vertRender dst{};

    xrSkin3W_x86(&dst, &src, 1, bones.data());

    ExpectVec3Near(dst.P, Fvector().set(25.f, 25.f, 50.f));
}

TEST(XrSkin4W, BlendsFourBones)
{
    BoneFixture bones(4);

    bones.SetTransform(0, Translation(10.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 20.f, 0.f));
    bones.SetTransform(2, Translation(0.f, 0.f, 30.f));
    bones.SetTransform(3, Translation(40.f, 0.f, 0.f));

    vertBoned4W src{};

    src.P.set(1.f, 2.f, 3.f);
    src.N.set(0.f, 0.f, 1.f);

    src.m[0] = 0;
    src.m[1] = 1;
    src.m[2] = 2;
    src.m[3] = 3;

    src.w[0] = 0.1f;
    src.w[1] = 0.2f;
    src.w[2] = 0.3f;
    // implicit fourth weight = 0.4

    src.u = 0.2f;
    src.v = 0.8f;

    vertRender dst{};

    xrSkin4W_x86(&dst, &src, 1, bones.data());

    // bone 0 = (11, 2, 3) * .1
    // bone 1 = (1, 22, 3) * .2
    // bone 2 = (1, 2, 33) * .3
    // bone 3 = (41, 2, 3) * .4
    //
    // = (17, 10, 12)
    ExpectRenderVertexEqual(
        dst,
        Fvector().set(17.f, 10.f, 12.f),
        Fvector().set(0.f, 0.f, 1.f),
        0.2f,
        0.8f);
}

TEST(XrSkin4W, HandlesZeroVertexCount)
{
    BoneFixture bones(1);
    bones.SetTransform(0, Fmatrix().identity());

    vertRender dst{};
    vertBoned4W src{};

    xrSkin4W_x86(&dst, &src, 0, bones.data());

    // Primarily a sanitizer/regression test:
    // the call must simply return without touching memory.
}

Fvector ReferenceSkin4W(
    const vertBoned4W& v,
    CBoneInstance* bones)
{
    Fvector result{};

    const float w3 = 1.f - v.w[0] - v.w[1] - v.w[2];

    Fvector p;

    bones[v.m[0]].mRenderTransform.transform_tiny(p, v.P);
    p.mul(v.w[0]);
    result.add(p);

    bones[v.m[1]].mRenderTransform.transform_tiny(p, v.P);
    p.mul(v.w[1]);
    result.add(p);

    bones[v.m[2]].mRenderTransform.transform_tiny(p, v.P);
    p.mul(v.w[2]);
    result.add(p);

    bones[v.m[3]].mRenderTransform.transform_tiny(p, v.P);
    p.mul(w3);
    result.add(p);

    return result;
}

TEST(XrSkin4W, MatchesReferenceImplementation)
{
    BoneFixture bones(8);

    for (size_t i = 0; i < bones.bones.size(); ++i)
    {
        bones.SetTransform(
            i,
            Translation(
                static_cast<float>(i * 3),
                static_cast<float>(i * 7),
                static_cast<float>(i * 11)));
    }

    std::vector<vertBoned4W> src(100);
    std::vector<vertRender> dst(100);

    for (size_t i = 0; i < src.size(); ++i)
    {
        auto& v = src[i];

        v.P.set(
            static_cast<float>(i) * 0.13f,
            static_cast<float>(i) * -0.27f,
            static_cast<float>(i) * 0.41f);

        v.N.set(0.f, 0.f, 1.f);

        v.m[0] = 0;
        v.m[1] = 1;
        v.m[2] = 2;
        v.m[3] = 3;

        v.w[0] = 0.1f;
        v.w[1] = 0.2f;
        v.w[2] = 0.3f;
    }

    xrSkin4W_x86(
        dst.data(),
        src.data(),
        static_cast<u32>(src.size()),
        bones.data());

    for (size_t i = 0; i < src.size(); ++i)
    {
        ExpectVec3Near(
            dst[i].P,
            ReferenceSkin4W(src[i], bones.data()));
    }
}

#if 0
TEST(XrSkin4WThread, ProducesSameResultAsSingleThreaded)
{
    // Initialize ttapi with however the real engine initializes it.

    BoneFixture bones(4);

    bones.SetTransform(0, Translation(10.f, 0.f, 0.f));
    bones.SetTransform(1, Translation(0.f, 20.f, 0.f));
    bones.SetTransform(2, Translation(0.f, 0.f, 30.f));
    bones.SetTransform(3, Translation(40.f, 0.f, 0.f));

    for (u32 count : {
        0u,
        1u,
        63u,
        64u,
        65u,
        127u,
        128u,
        129u,
        255u,
        256u,
        257u,
        511u,
        512u,
        513u,
    })
    {
        std::vector<vertBoned4W> src(count);
        std::vector<vertRender> expected(count);
        std::vector<vertRender> actual(count);

        for (u32 i = 0; i < count; ++i)
        {
            src[i].P.set(
                static_cast<float>(i),
                static_cast<float>(i) * 2.f,
                static_cast<float>(i) * 3.f);

            src[i].N.set(0.f, 0.f, 1.f);

            src[i].m[0] = 0;
            src[i].m[1] = 1;
            src[i].m[2] = 2;
            src[i].m[3] = 3;

            src[i].w[0] = 0.1f;
            src[i].w[1] = 0.2f;
            src[i].w[2] = 0.3f;

            src[i].u = static_cast<float>(i);
            src[i].v = static_cast<float>(i) * 2.f;
        }

        xrSkin4W_x86(
            expected.data(),
            src.data(),
            count,
            bones.data());

        xrSkin4W_thread(
            actual.data(),
            src.data(),
            count,
            bones.data());

        for (u32 i = 0; i < count; ++i)
        {
            ExpectVec3Near(actual[i].P, expected[i].P);
            ExpectVec3Near(actual[i].N, expected[i].N);

            EXPECT_FLOAT_EQ(actual[i].u, expected[i].u);
            EXPECT_FLOAT_EQ(actual[i].v, expected[i].v);
        }
    }
}
#endif

TEST(XrBindPSGP, InstallsGenericImplementations)
{
    xrDispatchTable table{};

    _processor_info processor{};
    processor.feature = 0;

    xrBind_PSGP(&table, &processor);

    ASSERT_NE(table.skin1W, nullptr);
    ASSERT_NE(table.skin2W, nullptr);
    ASSERT_NE(table.skin3W, nullptr);
    ASSERT_NE(table.skin4W, nullptr);
    ASSERT_NE(table.PLC_calc3, nullptr);

    EXPECT_EQ(table.skin1W, &xrSkin1W_x86);
    EXPECT_EQ(table.skin2W, &xrSkin2W_x86);
    EXPECT_EQ(table.skin3W, &xrSkin3W_x86);
    EXPECT_EQ(table.PLC_calc3, &PLC_calc3_x86);
}

TEST(XrDispatchTable, HasExpectedLayout)
{
    EXPECT_EQ(sizeof(xrDispatchTable),
              sizeof(void*) * 5);

    EXPECT_EQ(offsetof(xrDispatchTable, skin1W),
              sizeof(void*) * 0);

    EXPECT_EQ(offsetof(xrDispatchTable, skin2W),
              sizeof(void*) * 1);

    EXPECT_EQ(offsetof(xrDispatchTable, skin3W),
              sizeof(void*) * 2);

    EXPECT_EQ(offsetof(xrDispatchTable, skin4W),
              sizeof(void*) * 3);

    EXPECT_EQ(offsetof(xrDispatchTable, PLC_calc3),
              sizeof(void*) * 4);

    static_assert(sizeof(xrDispatchTable) == sizeof(void*) * 5);

    static_assert(offsetof(xrDispatchTable, skin1W) == sizeof(void*) * 0);
    static_assert(offsetof(xrDispatchTable, skin2W) == sizeof(void*) * 1);
    static_assert(offsetof(xrDispatchTable, skin3W) == sizeof(void*) * 2);
    static_assert(offsetof(xrDispatchTable, skin4W) == sizeof(void*) * 3);
    static_assert(offsetof(xrDispatchTable, PLC_calc3) == sizeof(void*) * 4);
}

} // namespace
