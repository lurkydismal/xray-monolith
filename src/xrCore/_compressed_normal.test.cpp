#include "stdafx.h"

#include "_compressed_normal.h"

#include <gtest/gtest.h>

#include <cmath>
#include <cstdint>

namespace
{
    constexpr float EPSILON = 1e-5f;
    constexpr float NORMAL_EPSILON = 1e-4f;

    constexpr u16 SIGN_MASK = 0xe000;
    constexpr u16 PAYLOAD_MASK = 0x1fff;

    void expect_vec_near(
        const Fvector& actual,
        float x,
        float y,
        float z,
        float epsilon = EPSILON)
    {
        EXPECT_NEAR(actual.x, x, epsilon);
        EXPECT_NEAR(actual.y, y, epsilon);
        EXPECT_NEAR(actual.z, z, epsilon);
    }

    float dot(const Fvector& a, const Fvector& b)
    {
        return a.x * b.x + a.y * b.y + a.z * b.z;
    }

    float length(const Fvector& v)
    {
        return std::sqrt(
            v.x * v.x +
            v.y * v.y +
            v.z * v.z);
    }

    Fvector normalized(Fvector v)
    {
        v.normalize();
        return v;
    }

    Fvector decompress(u16 compressed)
    {
        Fvector result;
        pvDecompress(result, compressed);
        return result;
    }

    u16 compress(float x, float y, float z)
    {
        Fvector v;
        v.set(x, y, z);
        return pvCompress(v);
    }
}


// -----------------------------------------------------------------------------
// Initialization
// -----------------------------------------------------------------------------

TEST(CompressedNormal, InitializeStaticsIsIdempotent)
{
    pvInitializeStatics();

    const u16 compressed = compress(1.0f, 2.0f, 3.0f);

    Fvector first;
    pvDecompress(first, compressed);

    pvInitializeStatics();

    Fvector second;
    pvDecompress(second, compressed);

    expect_vec_near(second, first.x, first.y, first.z, NORMAL_EPSILON);
}


// -----------------------------------------------------------------------------
// Basic round trips
// -----------------------------------------------------------------------------

TEST(CompressedNormal, RoundTripPositiveX)
{
    pvInitializeStatics();

    const Fvector input = {1.0f, 0.0f, 0.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, 1.0f, 0.0f, 0.0f);
}


TEST(CompressedNormal, RoundTripPositiveY)
{
    pvInitializeStatics();

    const Fvector input = {0.0f, 1.0f, 0.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, 0.0f, 1.0f, 0.0f);
}


TEST(CompressedNormal, RoundTripPositiveZ)
{
    pvInitializeStatics();

    const Fvector input = {0.0f, 0.0f, 1.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, 0.0f, 0.0f, 1.0f);
}


TEST(CompressedNormal, RoundTripNegativeX)
{
    pvInitializeStatics();

    const Fvector input = {-1.0f, 0.0f, 0.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, -1.0f, 0.0f, 0.0f);
}


TEST(CompressedNormal, RoundTripNegativeY)
{
    pvInitializeStatics();

    const Fvector input = {0.0f, -1.0f, 0.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, 0.0f, -1.0f, 0.0f);
}


TEST(CompressedNormal, RoundTripNegativeZ)
{
    pvInitializeStatics();

    const Fvector input = {0.0f, 0.0f, -1.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    expect_vec_near(output, 0.0f, 0.0f, -1.0f);
}


// -----------------------------------------------------------------------------
// Diagonals
// -----------------------------------------------------------------------------

TEST(CompressedNormal, RoundTripEqualPositiveComponents)
{
    pvInitializeStatics();

    const Fvector input = normalized(Fvector{1.0f, 1.0f, 1.0f});

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    EXPECT_GT(dot(input, output), 0.999f);
}


TEST(CompressedNormal, RoundTripEqualNegativeComponents)
{
    pvInitializeStatics();

    const Fvector input = normalized(Fvector{-1.0f, -1.0f, -1.0f});

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    EXPECT_GT(dot(input, output), 0.999f);
}


TEST(CompressedNormal, RoundTripMixedSigns)
{
    pvInitializeStatics();

    const Fvector input = normalized(Fvector{-1.0f, 2.0f, -3.0f});

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    EXPECT_GT(dot(input, output), 0.999f);
}


// -----------------------------------------------------------------------------
// Non-unit input
// -----------------------------------------------------------------------------

TEST(CompressedNormal, InputDoesNotHaveToBeUnitLength)
{
    pvInitializeStatics();

    const Fvector input = {10.0f, 20.0f, 30.0f};

    const u16 compressed = pvCompress(input);

    Fvector output;
    pvDecompress(output, compressed);

    const Fvector expected = normalized(input);

    EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    EXPECT_GT(dot(expected, output), 0.999f);
}


TEST(CompressedNormal, ScalingInputDoesNotChangeCompression)
{
    pvInitializeStatics();

    const Fvector a = {1.0f, 2.0f, 3.0f};
    const Fvector b = {10.0f, 20.0f, 30.0f};

    EXPECT_EQ(pvCompress(a), pvCompress(b));
}


TEST(CompressedNormal, NegativeScalingPreservesOppositeDirection)
{
    pvInitializeStatics();

    const Fvector a = {1.0f, 2.0f, 3.0f};
    const Fvector b = {-10.0f, -20.0f, -30.0f};

    Fvector da;
    Fvector db;

    pvDecompress(da, pvCompress(a));
    pvDecompress(db, pvCompress(b));

    EXPECT_NEAR(dot(da, db), -1.0f, NORMAL_EPSILON);
}


// -----------------------------------------------------------------------------
// Sign bits
// -----------------------------------------------------------------------------

TEST(CompressedNormal, SignBitsAreIndependentOfMagnitude)
{
    pvInitializeStatics();

    const Fvector positive = normalized(Fvector{1.0f, 2.0f, 3.0f});
    const Fvector negative = normalized(Fvector{-1.0f, -2.0f, -3.0f});

    const u16 positivePacked = pvCompress(positive);
    const u16 negativePacked = pvCompress(negative);

    EXPECT_EQ(
        positivePacked & PAYLOAD_MASK,
        negativePacked & PAYLOAD_MASK
    );

    EXPECT_EQ(
        (positivePacked ^ negativePacked) & SIGN_MASK,
        SIGN_MASK
    );
}


TEST(CompressedNormal, XSignBit)
{
    pvInitializeStatics();

    const u16 positive = pvCompress(Fvector{1.0f, 2.0f, 3.0f});
    const u16 negative = pvCompress(Fvector{-1.0f, 2.0f, 3.0f});

    EXPECT_EQ(
        (positive ^ negative) & 0x8000,
        0x8000
    );

    EXPECT_EQ(
        (positive ^ negative) & 0x6000,
        0
    );
}


TEST(CompressedNormal, YSignBit)
{
    pvInitializeStatics();

    const u16 positive = pvCompress(Fvector{1.0f, 2.0f, 3.0f});
    const u16 negative = pvCompress(Fvector{1.0f, -2.0f, 3.0f});

    EXPECT_EQ(
        (positive ^ negative) & 0x4000,
        0x4000
    );

    EXPECT_EQ(
        (positive ^ negative) & 0xa000,
        0
    );
}


TEST(CompressedNormal, ZSignBit)
{
    pvInitializeStatics();

    const u16 positive = pvCompress(Fvector{1.0f, 2.0f, 3.0f});
    const u16 negative = pvCompress(Fvector{1.0f, 2.0f, -3.0f});

    EXPECT_EQ(
        (positive ^ negative) & 0x2000,
        0x2000
    );

    EXPECT_EQ(
        (positive ^ negative) & 0xc000,
        0
    );
}


// -----------------------------------------------------------------------------
// All sign combinations
// -----------------------------------------------------------------------------

TEST(CompressedNormal, AllSignCombinations)
{
    pvInitializeStatics();

    const Fvector magnitudes = normalized(Fvector{1.0f, 2.0f, 3.0f});

    for (int sx : {-1, 1})
    {
        for (int sy : {-1, 1})
        {
            for (int sz : {-1, 1})
            {
                Fvector input;
                input.set(
                    magnitudes.x * float(sx),
                    magnitudes.y * float(sy),
                    magnitudes.z * float(sz)
                );

                const u16 packed = pvCompress(input);

                Fvector output;
                pvDecompress(output, packed);

                SCOPED_TRACE(
                    std::string("signs = ") +
                    std::to_string(sx) + ", " +
                    std::to_string(sy) + ", " +
                    std::to_string(sz)
                );

                EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
                EXPECT_GT(dot(input, output), 0.999f);

                EXPECT_EQ(
                    output.x < 0.0f,
                    sx < 0
                );

                EXPECT_EQ(
                    output.y < 0.0f,
                    sy < 0
                );

                EXPECT_EQ(
                    output.z < 0.0f,
                    sz < 0
                );
            }
        }
    }
}


// -----------------------------------------------------------------------------
// Unit-length invariant
// -----------------------------------------------------------------------------

TEST(CompressedNormal, DecompressedVectorIsUnitLength)
{
    pvInitializeStatics();

    const Fvector inputs[] =
    {
        {1, 0, 0},
        {0, 1, 0},
        {0, 0, 1},
        {1, 1, 0},
        {1, 0, 1},
        {0, 1, 1},
        {1, 1, 1},
        {-1, 2, -3},
        {4, -5, 6},
        {-7, -11, 13},
    };

    for (const Fvector& input : inputs)
    {
        Fvector output;
        pvDecompress(output, pvCompress(input));

        SCOPED_TRACE(
            std::to_string(input.x) + ", " +
            std::to_string(input.y) + ", " +
            std::to_string(input.z)
        );

        EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    }
}


// -----------------------------------------------------------------------------
// Directional accuracy
// -----------------------------------------------------------------------------

TEST(CompressedNormal, RoundTripHasSmallAngularError)
{
    pvInitializeStatics();

    const Fvector inputs[] =
    {
        normalized(Fvector{1, 2, 3}),
        normalized(Fvector{-1, 2, 3}),
        normalized(Fvector{1, -2, 3}),
        normalized(Fvector{1, 2, -3}),
        normalized(Fvector{-1, -2, 3}),
        normalized(Fvector{-1, 2, -3}),
        normalized(Fvector{1, -2, -3}),
        normalized(Fvector{-1, -2, -3}),
        normalized(Fvector{7, 11, 13}),
        normalized(Fvector{-17, 23, -31}),
    };

    for (const Fvector& input : inputs)
    {
        Fvector output;
        pvDecompress(output, pvCompress(input));

        SCOPED_TRACE(
            std::to_string(input.x) + ", " +
            std::to_string(input.y) + ", " +
            std::to_string(input.z)
        );

        EXPECT_GT(dot(input, output), 0.999f);
    }
}


// -----------------------------------------------------------------------------
// Compression stability
// -----------------------------------------------------------------------------

TEST(CompressedNormal, CompressionIsDeterministic)
{
    pvInitializeStatics();

    const Fvector input = normalized(Fvector{-17, 23, -31});

    const u16 expected = pvCompress(input);

    for (int i = 0; i < 100; ++i)
        EXPECT_EQ(pvCompress(input), expected);
}


TEST(CompressedNormal, DecompressionIsDeterministic)
{
    pvInitializeStatics();

    const u16 compressed = pvCompress(
        normalized(Fvector{17, -23, 31})
    );

    Fvector expected;
    pvDecompress(expected, compressed);

    for (int i = 0; i < 100; ++i)
    {
        Fvector actual;
        pvDecompress(actual, compressed);

        expect_vec_near(
            actual,
            expected.x,
            expected.y,
            expected.z,
            0.0f
        );
    }
}


// -----------------------------------------------------------------------------
// Payload coverage
// -----------------------------------------------------------------------------

TEST(CompressedNormal, EveryPayloadProducesUnitVector)
{
    pvInitializeStatics();

    for (u16 payload = 0; payload <= PAYLOAD_MASK; ++payload)
    {
        Fvector output;
        pvDecompress(output, payload);

        SCOPED_TRACE(payload);

        EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
    }
}


TEST(CompressedNormal, EveryPayloadWithAllSignsProducesUnitVector)
{
    pvInitializeStatics();

    constexpr u16 signs[] =
    {
        0x0000,
        0x2000,
        0x4000,
        0x6000,
        0x8000,
        0xa000,
        0xc000,
        0xe000,
    };

    for (u16 payload = 0; payload <= PAYLOAD_MASK; ++payload)
    {
        for (u16 sign : signs)
        {
            const u16 packed = payload | sign;

            Fvector output;
            pvDecompress(output, packed);

            SCOPED_TRACE(
                "packed = " + std::to_string(packed)
            );

            EXPECT_NEAR(length(output), 1.0f, NORMAL_EPSILON);
        }
    }
}


// -----------------------------------------------------------------------------
// Bit-level regression tests
// -----------------------------------------------------------------------------

TEST(CompressedNormal, PositiveAxisEncodingsAreStable)
{
    pvInitializeStatics();

    // These are useful as hard regression checks because the current
    // implementation has a deterministic mapping of the axes into the
    // 13-bit payload.
    EXPECT_EQ(pvCompress(Fvector{1, 0, 0}) & PAYLOAD_MASK, 0x0000);
    EXPECT_EQ(pvCompress(Fvector{0, 1, 0}) & PAYLOAD_MASK, 0x3f80);
    EXPECT_EQ(pvCompress(Fvector{0, 0, 1}) & PAYLOAD_MASK, 0x007e);
}


TEST(CompressedNormal, NegativeAxisEncodingsOnlyChangeSignBits)
{
    pvInitializeStatics();

    const u16 px = pvCompress(Fvector{1, 0, 0});
    const u16 nx = pvCompress(Fvector{-1, 0, 0});

    const u16 py = pvCompress(Fvector{0, 1, 0});
    const u16 ny = pvCompress(Fvector{0, -1, 0});

    const u16 pz = pvCompress(Fvector{0, 0, 1});
    const u16 nz = pvCompress(Fvector{0, 0, -1});

    EXPECT_EQ(px & PAYLOAD_MASK, nx & PAYLOAD_MASK);
    EXPECT_EQ(py & PAYLOAD_MASK, ny & PAYLOAD_MASK);
    EXPECT_EQ(pz & PAYLOAD_MASK, nz & PAYLOAD_MASK);

    EXPECT_EQ((px ^ nx) & SIGN_MASK, 0x8000);
    EXPECT_EQ((py ^ ny) & SIGN_MASK, 0x4000);
    EXPECT_EQ((pz ^ nz) & SIGN_MASK, 0x2000);
}
