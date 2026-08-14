#if 0
#include "../xrCDB/xrCDB.h"
#include "../xrCore/xrCore.h"
#include "../xrPhysics.h"
#include "../xrSound/Sound.h"

class CGameMtlLibrary;

#include <gtest/gtest.h>

#include "dSortTriPrimitive.h"

namespace
{

Triangle MakeTriangle(
    CDB::TRI* tri,
    const dReal& nx,
    const dReal& ny,
    const dReal& nz,
    const dReal& pos)
{
    Triangle result{};

    result.T = tri;
    result.norm[0] = nx;
    result.norm[1] = ny;
    result.norm[2] = nz;
    result.pos = pos;

    return result;
}

CDB::TRI MakeCdbTriangle(
    u32 v0,
    u32 v1,
    u32 v2)
{
    CDB::TRI result{};

    result.verts[0] = v0;
    result.verts[1] = v1;
    result.verts[2] = v2;

    return result;
}

TEST(NegativeTriSetIgnoredByPositiveTriTest, IdenticalTrianglesAreIgnored)
{
    CDB::TRI tri{};
    tri.verts[0] = 0;
    tri.verts[1] = 1;
    tri.verts[2] = 2;

    const Fvector vertices[] =
    {
        Fvector().set(0.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),
    };

    Triangle negative{};
    negative.T = &tri;
    negative.norm.set(0.0f, 1.0f, 0.0f);
    negative.pos = 0.0f;

    Triangle positive{};
    positive.T = &tri;
    positive.norm.set(0.0f, 1.0f, 0.0f);
    positive.pos = 0.0f;

    EXPECT_TRUE(
        negative_tri_set_ignored_by_positive_tri(
            negative,
            positive,
            vertices
        )
    );
}

TEST(NegativeTriSetIgnoredByPositiveTriTest, TrianglesWithSameVerticesAreIgnored)
{
    CDB::TRI negative_tri{};
    negative_tri.verts[0] = 0;
    negative_tri.verts[1] = 1;
    negative_tri.verts[2] = 2;

    CDB::TRI positive_tri{};
    positive_tri.verts[0] = 2;
    positive_tri.verts[1] = 0;
    positive_tri.verts[2] = 1;

    const Fvector vertices[] =
    {
        Fvector().set(0.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),
    };

    Triangle negative{};
    negative.T = &negative_tri;
    negative.norm.set(0.0f, 1.0f, 0.0f);
    negative.pos = 0.0f;

    Triangle positive{};
    positive.T = &positive_tri;
    positive.norm.set(0.0f, 1.0f, 0.0f);
    positive.pos = 0.0f;

    EXPECT_TRUE(
        negative_tri_set_ignored_by_positive_tri(
            negative,
            positive,
            vertices
        )
    );
}

TEST(NegativeTriSetIgnoredByPositiveTriTest, PositiveTriangleBehindNegativePlaneIsIgnored)
{
    CDB::TRI negative_tri{};
    negative_tri.verts[0] = 0;
    negative_tri.verts[1] = 1;
    negative_tri.verts[2] = 2;

    CDB::TRI positive_tri{};
    positive_tri.verts[0] = 3;
    positive_tri.verts[1] = 4;
    positive_tri.verts[2] = 5;

    const Fvector vertices[] =
    {
        Fvector().set(0.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),

        Fvector().set(0.0f, -1.0f, 0.0f),
        Fvector().set(1.0f, -1.0f, 0.0f),
        Fvector().set(0.0f, -2.0f, 0.0f),
    };

    Triangle negative{};
    negative.T = &negative_tri;
    negative.norm.set(0.0f, 1.0f, 0.0f);
    negative.pos = 0.0f;

    Triangle positive{};
    positive.T = &positive_tri;
    positive.norm.set(0.0f, 1.0f, 0.0f);
    positive.pos = 0.0f;

    EXPECT_TRUE(
        negative_tri_set_ignored_by_positive_tri(
            negative,
            positive,
            vertices
        )
    );
}

TEST(NegativeTriSetIgnoredByPositiveTriTest, PositiveTriangleInFrontIsNotIgnored)
{
    CDB::TRI negative_tri{};
    negative_tri.verts[0] = 0;
    negative_tri.verts[1] = 1;
    negative_tri.verts[2] = 2;

    CDB::TRI positive_tri{};
    positive_tri.verts[0] = 3;
    positive_tri.verts[1] = 4;
    positive_tri.verts[2] = 5;

    const Fvector vertices[] =
    {
        Fvector().set(0.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),

        Fvector().set(0.0f, 1.0f, 0.0f),
        Fvector().set(1.0f, 1.0f, 0.0f),
        Fvector().set(0.0f, 2.0f, 0.0f),
    };

    Triangle negative{};
    negative.T = &negative_tri;
    negative.norm.set(0.0f, 1.0f, 0.0f);
    negative.pos = 0.0f;

    Triangle positive{};
    positive.T = &positive_tri;
    positive.norm.set(0.0f, 1.0f, 0.0f);
    positive.pos = 0.0f;

    EXPECT_FALSE(
        negative_tri_set_ignored_by_positive_tri(
            negative,
            positive,
            vertices
        )
    );
}

TEST(NegativeTriSetIgnoredByPositiveTriTest, OneSharedVertexDoesNotAutomaticallyIgnore)
{
    CDB::TRI negative_tri{};
    negative_tri.verts[0] = 0;
    negative_tri.verts[1] = 1;
    negative_tri.verts[2] = 2;

    CDB::TRI positive_tri{};
    positive_tri.verts[0] = 0; // shared
    positive_tri.verts[1] = 3;
    positive_tri.verts[2] = 4;

    const Fvector vertices[] =
    {
        Fvector().set(0.0f, 0.0f, 0.0f),
        Fvector().set(1.0f, 0.0f, 0.0f),
        Fvector().set(0.0f, 1.0f, 0.0f),

        Fvector().set(1.0f, 1.0f, 0.0f),
        Fvector().set(2.0f, 1.0f, 0.0f),
    };

    Triangle negative{};
    negative.T = &negative_tri;
    negative.norm.set(0.0f, 1.0f, 0.0f);
    negative.pos = 0.0f;

    Triangle positive{};
    positive.T = &positive_tri;
    positive.norm.set(0.0f, 1.0f, 0.0f);
    positive.pos = 0.0f;

    EXPECT_FALSE(
        negative_tri_set_ignored_by_positive_tri(
            negative,
            positive,
            vertices
        )
    );
}

TEST(SetBackTrajectoryCntTest, CalculatesNormalizedTrajectoryNormal)
{
    CDB::TRI tri{};

    dxGeom* o1 = nullptr;
    dxGeom* o2 = nullptr;

    Triangle negative{};
    negative.T = &tri;

    dxGeomUserData data1{};
    dxGeomUserData data2{};

    dGeomSetUserData(o1, &data1);
    dGeomSetUserData(o2, &data2);

    const dReal p[] =
    {
        1.0,
        2.0,
        3.0,
    };

    const dReal last_pos[] =
    {
        1.0,
        6.0,
        3.0,
    };

    dContactGeom contact{};

    const int result = SetBackTrajectoryCnt(
        p,
        last_pos,
        negative,
        o1,
        o2,
        &contact
    );

    ASSERT_EQ(result, 1);

    EXPECT_EQ(contact.g1, o2);
    EXPECT_EQ(contact.g2, o1);

    // -(last_pos - p) = -(0, 4, 0)
    // normalized = (0, -1, 0)
    EXPECT_DOUBLE_EQ(contact.normal[0], 0.0);
    EXPECT_DOUBLE_EQ(contact.normal[1], -1.0);
    EXPECT_DOUBLE_EQ(contact.normal[2], 0.0);

    EXPECT_DOUBLE_EQ(contact.depth, 4.0);

    EXPECT_DOUBLE_EQ(contact.pos[0], 1.0);
    EXPECT_DOUBLE_EQ(contact.pos[1], 2.0);
    EXPECT_DOUBLE_EQ(contact.pos[2], 3.0);
}

TEST(SetBackTrajectoryCntTest, ZeroTrajectoryUsesDefaultNormal)
{
    CDB::TRI tri{};

    dxGeom* o1 = nullptr;
    dxGeom* o2 = nullptr;

    dxGeomUserData data1{};
    dxGeomUserData data2{};

    dGeomSetUserData(o1, &data1);
    dGeomSetUserData(o2, &data2);

    Triangle negative{};
    negative.T = &tri;

    const dReal p[] =
    {
        10.0,
        20.0,
        30.0,
    };

    const dReal last_pos[] =
    {
        10.0,
        20.0,
        30.0,
    };

    dContactGeom contact{};

    const int result = SetBackTrajectoryCnt(
        p,
        last_pos,
        negative,
        o1,
        o2,
        &contact
    );

    ASSERT_EQ(result, 1);

    EXPECT_DOUBLE_EQ(contact.normal[0], 0.0);
    EXPECT_DOUBLE_EQ(contact.normal[1], -1.0);
    EXPECT_DOUBLE_EQ(contact.normal[2], 0.0);

    EXPECT_FLOAT_EQ(contact.depth, 0.0f);

    EXPECT_DOUBLE_EQ(contact.pos[0], p[0]);
    EXPECT_DOUBLE_EQ(contact.pos[1], p[1]);
    EXPECT_DOUBLE_EQ(contact.pos[2], p[2]);
}

} // namespace
#endif
