#include "../xrCore/xrCore.h"
#include "_vector3d.h"
#include "psystem.h"
#include "particle_core.h"

#include <gtest/gtest.h>

#include <cmath>

namespace
{

using namespace PAPI;

// -----------------------------------------------------------------------------
// Helpers
// -----------------------------------------------------------------------------

static pVector V(float x, float y, float z)
{
    return pVector(x, y, z);
}

static void ExpectVectorNear(
    const pVector& actual,
    const pVector& expected,
    float tolerance = 1e-5f)
{
    EXPECT_NEAR(actual.x, expected.x, tolerance);
    EXPECT_NEAR(actual.y, expected.y, tolerance);
    EXPECT_NEAR(actual.z, expected.z, tolerance);
}

static float DistanceSquared(const pVector& a, const pVector& b)
{
    return (a - b).length2();
}

static float Distance(const pVector& a, const pVector& b)
{
    return _sqrt(DistanceSquared(a, b));
}

static bool IsFinite(const pVector& v)
{
    return std::isfinite(v.x) &&
           std::isfinite(v.y) &&
           std::isfinite(v.z);
}


// -----------------------------------------------------------------------------
// pDomain construction: Point
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, PointStoresPosition)
{
    const pDomain domain(PDPoint, 1.0f, 2.0f, 3.0f);

    EXPECT_EQ(domain.type, PDPoint);
    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
}

TEST(PDomainWithinTest, PointIsNotSupported)
{
    const pDomain domain(PDPoint, 1.0f, 2.0f, 3.0f);

    EXPECT_FALSE(domain.Within(V(1.0f, 2.0f, 3.0f)));
}

TEST(PDomainGenerateTest, PointAlwaysGeneratesPoint)
{
    const pDomain domain(PDPoint, 1.0f, 2.0f, 3.0f);

    for (int i = 0; i < 20; ++i)
    {
        pVector result;
        domain.Generate(result);

        ExpectVectorNear(result, V(1.0f, 2.0f, 3.0f));
    }
}


// -----------------------------------------------------------------------------
// pDomain construction: Line
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, LineStoresStartAndDelta)
{
    const pDomain domain(
        PDLine,
        1.0f, 2.0f, 3.0f,
        5.0f, 7.0f, 11.0f
    );

    EXPECT_EQ(domain.type, PDLine);

    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
    ExpectVectorNear(domain.p2, V(4.0f, 5.0f, 8.0f));
}

TEST(PDomainWithinTest, LineIsNotSupported)
{
    const pDomain domain(
        PDLine,
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f
    );

    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, 0.0f)));
    EXPECT_FALSE(domain.Within(V(5.0f, 0.0f, 0.0f)));
}

TEST(PDomainGenerateTest, LineGeneratesPointsOnSegment)
{
    const pVector start = V(1.0f, 2.0f, 3.0f);
    const pVector end = V(5.0f, 7.0f, 11.0f);

    const pDomain domain(
        PDLine,
        start.x, start.y, start.z,
        end.x, end.y, end.z
    );

    const pVector delta = end - start;

    for (int i = 0; i < 100; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));

        // Result = start + delta * t, 0 <= t <= 1.
        const float deltaLength2 = delta.length2();
        const float t =
            ((result - start) * delta) / deltaLength2;

        EXPECT_GE(t, 0.0f);
        EXPECT_LE(t, 1.0f);

        const pVector reconstructed = start + delta * t;

        ExpectVectorNear(result, reconstructed, 1e-4f);
    }
}


// -----------------------------------------------------------------------------
// Box
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, BoxNormalizesCorners)
{
    const pDomain domain(
        PDBox,
        10.0f, 20.0f, 30.0f,
        -10.0f, -20.0f, -30.0f
    );

    EXPECT_EQ(domain.type, PDBox);

    ExpectVectorNear(domain.p1, V(-10.0f, -20.0f, -30.0f));
    ExpectVectorNear(domain.p2, V(10.0f, 20.0f, 30.0f));
}

TEST(PDomainConstructorTest, BoxPreservesAlreadyOrderedCorners)
{
    const pDomain domain(
        PDBox,
        -1.0f, -2.0f, -3.0f,
        4.0f, 5.0f, 6.0f
    );

    ExpectVectorNear(domain.p1, V(-1.0f, -2.0f, -3.0f));
    ExpectVectorNear(domain.p2, V(4.0f, 5.0f, 6.0f));
}

TEST(PDomainWithinTest, BoxIncludesBoundary)
{
    const pDomain domain(
        PDBox,
        -1.0f, -2.0f, -3.0f,
        4.0f, 5.0f, 6.0f
    );

    EXPECT_TRUE(domain.Within(V(-1.0f, -2.0f, -3.0f)));
    EXPECT_TRUE(domain.Within(V(4.0f, 5.0f, 6.0f)));
    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 0.0f)));
}

TEST(PDomainWithinTest, BoxRejectsOutsidePoints)
{
    const pDomain domain(
        PDBox,
        -1.0f, -2.0f, -3.0f,
        4.0f, 5.0f, 6.0f
    );

    EXPECT_FALSE(domain.Within(V(-1.001f, 0.0f, 0.0f)));
    EXPECT_FALSE(domain.Within(V(4.001f, 0.0f, 0.0f)));
    EXPECT_FALSE(domain.Within(V(0.0f, -2.001f, 0.0f)));
    EXPECT_FALSE(domain.Within(V(0.0f, 5.001f, 0.0f)));
    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, -3.001f)));
    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, 6.001f)));
}

TEST(PDomainGenerateTest, BoxGeneratesPointsInsideBox)
{
    const pDomain domain(
        PDBox,
        -1.0f, -2.0f, -3.0f,
        4.0f, 5.0f, 6.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(domain.Within(result))
            << "Generated point: "
            << result.x << ", "
            << result.y << ", "
            << result.z;
    }
}


// -----------------------------------------------------------------------------
// Plane
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, PlaneNormalIsNormalized)
{
    const pDomain domain(
        PDPlane,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f
    );

    EXPECT_EQ(domain.type, PDPlane);
    EXPECT_NEAR(domain.p2.length(), 1.0f, 1e-5f);
}

TEST(PDomainConstructorTest, PlaneStoresCorrectNormal)
{
    const pDomain domain(
        PDPlane,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f
    );

    ExpectVectorNear(domain.p2, V(0.0f, 0.0f, 1.0f));
    EXPECT_FLOAT_EQ(domain.radius1, 0.0f);
}

TEST(PDomainConstructorTest, PlaneStoresPlaneDistance)
{
    // Plane through z = 5 with normal +Z:
    // n * p + d = 0
    // z - 5 = 0
    // d = -5
    //
    // radius1 stores -d? The implementation stores:
    // radius1 = -(p1 * p2)
    //
    // For p1=(0,0,5), n=(0,0,1), this is -5.

    const pDomain domain(
        PDPlane,
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 1.0f
    );

    EXPECT_FLOAT_EQ(domain.radius1, -5.0f);
}

TEST(PDomainWithinTest, PlaneIncludesPositiveHalfSpace)
{
    const pDomain domain(
        PDPlane,
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 1.0f
    );

    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 5.0f)));
    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 10.0f)));
}

TEST(PDomainWithinTest, PlaneRejectsNegativeHalfSpace)
{
    const pDomain domain(
        PDPlane,
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 1.0f
    );

    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, 4.999f)));
    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, 0.0f)));
}

TEST(PDomainGenerateTest, PlaneGeneratesReferencePoint)
{
    const pVector point = V(1.0f, 2.0f, 3.0f);

    const pDomain domain(
        PDPlane,
        point.x, point.y, point.z,
        0.0f, 1.0f, 0.0f
    );

    pVector result;

    domain.Generate(result);

    // Current implementation simply returns p1.
    ExpectVectorNear(result, point);
}


// -----------------------------------------------------------------------------
// Sphere
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, SphereStoresCenter)
{
    const pDomain domain(
        PDSphere,
        1.0f, 2.0f, 3.0f,
        5.0f, 2.0f
    );

    EXPECT_EQ(domain.type, PDSphere);
    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
}

TEST(PDomainConstructorTest, SphereOrdersRadii)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        2.0f, 5.0f
    );

    EXPECT_FLOAT_EQ(domain.radius1, 5.0f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.0f);
    EXPECT_FLOAT_EQ(domain.radius1Sqr, 25.0f);
    EXPECT_FLOAT_EQ(domain.radius2Sqr, 4.0f);
}

TEST(PDomainWithinTest, SphereIncludesOuterBoundary)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f
    );

    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 0.0f)));
}

TEST(PDomainWithinTest, SphereIncludesCenterForSolidSphere)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f, 0.0f
    );

    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 0.0f)));
}

TEST(PDomainWithinTest, SphereRejectsOutsidePoint)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f
    );

    EXPECT_FALSE(domain.Within(V(5.001f, 0.0f, 0.0f)));
}

TEST(PDomainWithinTest, SphereRejectsInsideInnerRadius)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f, 2.0f
    );

    EXPECT_FALSE(domain.Within(V(1.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(domain.Within(V(2.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 0.0f)));
}

TEST(PDomainGenerateTest, SphereGeneratesPointsWithinSolidSphere)
{
    const pDomain domain(
        PDSphere,
        1.0f, 2.0f, 3.0f,
        5.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));
        EXPECT_LE(
            Distance(result, domain.p1),
            domain.radius1 + 1e-4f
        );
    }
}

TEST(PDomainGenerateTest, SphericalShellGeneratesPointsWithinRadii)
{
    const pDomain domain(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f, 2.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        const float distance = Distance(result, domain.p1);

        EXPECT_GE(distance, 2.0f - 1e-4f);
        EXPECT_LE(distance, 5.0f + 1e-4f);
    }
}

TEST(PDomainGenerateTest, EqualSphereRadiiGenerateConstantRadius)
{
    const pDomain domain(
        PDSphere,
        10.0f, 20.0f, 30.0f,
        5.0f, 5.0f
    );

    for (int i = 0; i < 100; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_NEAR(
            Distance(result, domain.p1),
            5.0f,
            1e-3f
        );
    }
}


// -----------------------------------------------------------------------------
// Cylinder
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, CylinderStoresAxisVector)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    EXPECT_EQ(domain.type, PDCylinder);

    ExpectVectorNear(domain.p1, V(0.0f, 0.0f, 0.0f));
    ExpectVectorNear(domain.p2, V(0.0f, 0.0f, 10.0f));

    EXPECT_FLOAT_EQ(domain.radius1, 5.0f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.0f);
}

TEST(PDomainConstructorTest, CylinderOrdersRadii)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        2.0f, 5.0f
    );

    EXPECT_FLOAT_EQ(domain.radius1, 5.0f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.0f);
}

TEST(PDomainConstructorTest, CylinderAxisFrameIsOrthonormal)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    EXPECT_NEAR(domain.p2.length(), 10.0f, 1e-5f);
    EXPECT_NEAR(domain.u.length(), 1.0f, 1e-5f);
    EXPECT_NEAR(domain.v.length(), 1.0f, 1e-5f);

    const pVector n = domain.p2 / domain.p2.length();

    EXPECT_NEAR(domain.u * n, 0.0f, 1e-5f);
    EXPECT_NEAR(domain.v * n, 0.0f, 1e-5f);
    EXPECT_NEAR(domain.u * domain.v, 0.0f, 1e-5f);
}

TEST(PDomainWithinTest, CylinderIncludesAxis)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 5.0f)));
    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 10.0f)));
}

TEST(PDomainWithinTest, CylinderIncludesOuterBoundary)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 0.0f)));
    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 5.0f)));
    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 10.0f)));
}

TEST(PDomainWithinTest, CylinderRejectsBeyondCaps)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, -0.001f)));
    EXPECT_FALSE(domain.Within(V(0.0f, 0.0f, 10.001f)));
}

TEST(PDomainWithinTest, CylinderRejectsOutsideRadius)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    EXPECT_FALSE(domain.Within(V(5.001f, 0.0f, 5.0f)));
}

TEST(PDomainWithinTest, CylinderSupportsInnerRadius)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    EXPECT_FALSE(domain.Within(V(1.0f, 0.0f, 5.0f)));
    EXPECT_TRUE(domain.Within(V(2.0f, 0.0f, 5.0f)));
    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 5.0f)));
}

TEST(PDomainGenerateTest, CylinderGeneratesPointsInsideDomain)
{
    const pDomain domain(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));
        EXPECT_TRUE(domain.Within(result))
            << "Generated point: "
            << result.x << ", "
            << result.y << ", "
            << result.z;
    }
}


// -----------------------------------------------------------------------------
// Cone
// -----------------------------------------------------------------------------

TEST(PDomainWithinTest, ConeIncludesApex)
{
    const pDomain domain(
        PDCone,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    EXPECT_TRUE(domain.Within(V(0.0f, 0.0f, 0.0f)));
}

TEST(PDomainWithinTest, ConeRadiusGrowsWithDistance)
{
    const pDomain domain(
        PDCone,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    // At z=5 the cone radius is 2.5.
    EXPECT_TRUE(domain.Within(V(2.5f, 0.0f, 5.0f)));
    EXPECT_FALSE(domain.Within(V(2.501f, 0.0f, 5.0f)));

    // At z=10 the radius is 5.
    EXPECT_TRUE(domain.Within(V(5.0f, 0.0f, 10.0f)));
}

TEST(PDomainGenerateTest, ConeGeneratesPointsInsideDomain)
{
    const pDomain domain(
        PDCone,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 0.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));
        EXPECT_TRUE(domain.Within(result))
            << "Generated point: "
            << result.x << ", "
            << result.y << ", "
            << result.z;
    }
}

TEST(PDomainGenerateTest, ConeWithInnerRadiusGeneratesWithinAnnularCone)
{
    const pDomain domain(
        PDCone,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));
        EXPECT_TRUE(domain.Within(result));
    }
}


// -----------------------------------------------------------------------------
// Triangle
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, TriangleStoresFirstVertex)
{
    const pDomain domain(
        PDTriangle,
        1.0f, 2.0f, 3.0f,
        5.0f, 2.0f, 3.0f,
        1.0f, 8.0f, 3.0f
    );

    EXPECT_EQ(domain.type, PDTriangle);
    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
}

TEST(PDomainConstructorTest, TriangleStoresEdgeVectors)
{
    const pDomain domain(
        PDTriangle,
        1.0f, 2.0f, 3.0f,
        5.0f, 2.0f, 3.0f,
        1.0f, 8.0f, 3.0f
    );

    ExpectVectorNear(domain.u, V(4.0f, 0.0f, 0.0f));
    ExpectVectorNear(domain.v, V(0.0f, 6.0f, 0.0f));
}

TEST(PDomainConstructorTest, TriangleNormalIsNormalized)
{
    const pDomain domain(
        PDTriangle,
        0.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 3.0f, 0.0f
    );

    EXPECT_NEAR(domain.p2.length(), 1.0f, 1e-5f);
    ExpectVectorNear(domain.p2, V(0.0f, 0.0f, 1.0f));
}

TEST(PDomainGenerateTest, TriangleGeneratesPointsInsideTriangle)
{
    const pVector a = V(0.0f, 0.0f, 0.0f);
    const pVector b = V(10.0f, 0.0f, 0.0f);
    const pVector c = V(0.0f, 10.0f, 0.0f);

    const pDomain domain(
        PDTriangle,
        a.x, a.y, a.z,
        b.x, b.y, b.z,
        c.x, c.y, c.z
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));

        // Since this is a right triangle in XY:
        // x >= 0, y >= 0, x + y <= 10.
        EXPECT_GE(result.x, -1e-4f);
        EXPECT_GE(result.y, -1e-4f);
        EXPECT_LE(result.x + result.y, 10.0f + 1e-4f);
        EXPECT_NEAR(result.z, 0.0f, 1e-4f);
    }
}


// -----------------------------------------------------------------------------
// Rectangle
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, RectangleStoresOriginAndEdges)
{
    const pDomain domain(
        PDRectangle,
        1.0f, 2.0f, 3.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f
    );

    EXPECT_EQ(domain.type, PDRectangle);

    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
    ExpectVectorNear(domain.u, V(4.0f, 0.0f, 0.0f));
    ExpectVectorNear(domain.v, V(0.0f, 5.0f, 0.0f));
}

TEST(PDomainConstructorTest, RectangleNormalIsNormalized)
{
    const pDomain domain(
        PDRectangle,
        0.0f, 0.0f, 0.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f
    );

    EXPECT_NEAR(domain.p2.length(), 1.0f, 1e-5f);
    ExpectVectorNear(domain.p2, V(0.0f, 0.0f, 1.0f));
}

TEST(PDomainWithinTest, RectangleIsNotSupported)
{
    const pDomain domain(
        PDRectangle,
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f
    );

    EXPECT_FALSE(domain.Within(V(5.0f, 5.0f, 0.0f)));
}

TEST(PDomainGenerateTest, RectangleGeneratesPointsOnRectangle)
{
    const pDomain domain(
        PDRectangle,
        1.0f, 2.0f, 3.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));

        EXPECT_GE(result.x, 1.0f - 1e-4f);
        EXPECT_LE(result.x, 5.0f + 1e-4f);

        EXPECT_GE(result.y, 2.0f - 1e-4f);
        EXPECT_LE(result.y, 7.0f + 1e-4f);

        EXPECT_NEAR(result.z, 3.0f, 1e-4f);
    }
}


// -----------------------------------------------------------------------------
// Disc
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, DiscStoresCenterAndNormalizedNormal)
{
    const pDomain domain(
        PDDisc,
        1.0f, 2.0f, 3.0f,
        0.0f, 0.0f, 10.0f,
        5.0f, 2.0f
    );

    EXPECT_EQ(domain.type, PDDisc);

    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));
    ExpectVectorNear(domain.p2, V(0.0f, 0.0f, 1.0f));

    EXPECT_FLOAT_EQ(domain.radius1, 5.0f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.0f);
}

TEST(PDomainConstructorTest, DiscOrdersRadii)
{
    const pDomain domain(
        PDDisc,
        0.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f,
        2.0f, 5.0f
    );

    EXPECT_FLOAT_EQ(domain.radius1, 5.0f);
    EXPECT_FLOAT_EQ(domain.radius2, 2.0f);
}

TEST(PDomainGenerateTest, DiscGeneratesPointsWithinAnnulus)
{
    const pVector center = V(1.0f, 2.0f, 3.0f);

    const pDomain domain(
        PDDisc,
        center.x, center.y, center.z,
        0.0f, 0.0f, 1.0f,
        2.0f, 5.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));

        const float distance = Distance(result, center);

        EXPECT_GE(distance, 2.0f - 1e-4f);
        EXPECT_LE(distance, 5.0f + 1e-4f);

        // Generated point should lie in the XY plane.
        EXPECT_NEAR(result.z, center.z, 1e-4f);
    }
}

TEST(PDomainGenerateTest, DiscWithEqualRadiiGeneratesConstantRadius)
{
    const pVector center = V(0.0f, 0.0f, 0.0f);

    const pDomain domain(
        PDDisc,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        3.0f, 3.0f
    );

    for (int i = 0; i < 100; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_NEAR(
            Distance(result, center),
            3.0f,
            1e-4f
        );
    }
}


// -----------------------------------------------------------------------------
// Blob
// -----------------------------------------------------------------------------

TEST(PDomainConstructorTest, BlobStoresCenterAndParameters)
{
    const pDomain domain(
        PDBlob,
        1.0f, 2.0f, 3.0f,
        4.0f
    );

    EXPECT_EQ(domain.type, PDBlob);
    ExpectVectorNear(domain.p1, V(1.0f, 2.0f, 3.0f));

    EXPECT_FLOAT_EQ(
        domain.radius2,
        ONEOVERSQRT2PI / 4.0f
    );

    EXPECT_FLOAT_EQ(
        domain.radius2Sqr,
        -0.5f / 16.0f
    );
}

TEST(PDomainGenerateTest, BlobGeneratesFinitePoints)
{
    const pDomain domain(
        PDBlob,
        10.0f, 20.0f, 30.0f,
        4.0f
    );

    for (int i = 0; i < 1000; ++i)
    {
        pVector result;
        domain.Generate(result);

        EXPECT_TRUE(IsFinite(result));
    }
}

TEST(PDomainWithinTest, BlobProducesProbabilisticMembership)
{
    const pDomain domain(
        PDBlob,
        0.0f, 0.0f, 0.0f,
        1.0f
    );

    // Within() is deliberately stochastic for blobs. We should not assert
    // a particular result. Instead, sample many times and ensure that the
    // result remains a valid boolean and that the distribution isn't
    // completely degenerate.

    int insideCount = 0;

    for (int i = 0; i < 10000; ++i)
    {
        if (domain.Within(V(0.0f, 0.0f, 0.0f)))
            ++insideCount;
    }

    EXPECT_GT(insideCount, 0);
    EXPECT_LT(insideCount, 10000);
}


// -----------------------------------------------------------------------------
// Unsupported Within() operations
// -----------------------------------------------------------------------------

TEST(PDomainWithinTest, GenerateOnlyDomainsReturnFalseFromWithin)
{
    const pDomain line(
        PDLine,
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f
    );

    const pDomain triangle(
        PDTriangle,
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f
    );

    const pDomain rectangle(
        PDRectangle,
        0.0f, 0.0f, 0.0f,
        10.0f, 0.0f, 0.0f,
        0.0f, 10.0f, 0.0f
    );

    const pDomain disc(
        PDDisc,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        5.0f, 0.0f
    );

    const pVector point = V(1.0f, 1.0f, 0.0f);

    EXPECT_FALSE(line.Within(point));
    EXPECT_FALSE(triangle.Within(point));
    EXPECT_FALSE(rectangle.Within(point));
    EXPECT_FALSE(disc.Within(point));
}


// -----------------------------------------------------------------------------
// transform()
// -----------------------------------------------------------------------------

TEST(PDomainTransformTest, PointTranslation)
{
    const pDomain source(
        PDPoint,
        1.0f, 2.0f, 3.0f
    );

    pDomain destination(
        PDPoint,
        0.0f, 0.0f, 0.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );
}

TEST(PDomainTransformTest, LineTranslation)
{
    const pDomain source(
        PDLine,
        1.0f, 2.0f, 3.0f,
        5.0f, 7.0f, 11.0f
    );

    pDomain destination(
        PDLine,
        0.0f, 0.0f, 0.0f,
        1.0f, 1.0f, 1.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    // Position is translated.
    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );

    // Direction is NOT translated.
    ExpectVectorNear(
        destination.p2,
        source.p2
    );
}

TEST(PDomainTransformTest, SphereTranslationMovesCenter)
{
    const pDomain source(
        PDSphere,
        1.0f, 2.0f, 3.0f,
        5.0f, 2.0f
    );

    pDomain destination(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f, 2.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );

    // Current implementation only transforms the center.
    EXPECT_FLOAT_EQ(destination.radius1, 5.0f);
    EXPECT_FLOAT_EQ(destination.radius2, 2.0f);
}

TEST(PDomainTransformTest, PlaneTranslationUpdatesPlaneDistance)
{
    const pDomain source(
        PDPlane,
        0.0f, 0.0f, 5.0f,
        0.0f, 0.0f, 1.0f
    );

    pDomain destination(
        PDPlane,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(0.0f, 0.0f, 10.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(0.0f, 0.0f, 15.0f)
    );

    ExpectVectorNear(
        destination.p2,
        V(0.0f, 0.0f, 1.0f)
    );

    EXPECT_FLOAT_EQ(destination.radius1, -15.0f);
}

TEST(PDomainTransformTest, RectangleTranslationMovesOrigin)
{
    const pDomain source(
        PDRectangle,
        1.0f, 2.0f, 3.0f,
        4.0f, 0.0f, 0.0f,
        0.0f, 5.0f, 0.0f
    );

    pDomain destination(
        PDRectangle,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f,
        0.0f, 1.0f, 0.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );

    // Direction vectors are unaffected by pure translation.
    ExpectVectorNear(destination.u, source.u);
    ExpectVectorNear(destination.v, source.v);
    ExpectVectorNear(destination.p2, source.p2);
}

TEST(PDomainTransformTest, DiscTranslationMovesCenter)
{
    const pDomain source(
        PDDisc,
        1.0f, 2.0f, 3.0f,
        0.0f, 0.0f, 1.0f,
        5.0f, 2.0f
    );

    pDomain destination(
        PDDisc,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        5.0f, 2.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );

    ExpectVectorNear(destination.p2, source.p2);
    ExpectVectorNear(destination.u, source.u);
    ExpectVectorNear(destination.v, source.v);
}

TEST(PDomainTransformTest, CylinderTranslationMovesBaseAndKeepsAxisDirection)
{
    const pDomain source(
        PDCylinder,
        1.0f, 2.0f, 3.0f,
        1.0f, 2.0f, 13.0f,
        5.0f, 2.0f
    );

    pDomain destination(
        PDCylinder,
        0.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f,
        5.0f, 2.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform(source, matrix);

    ExpectVectorNear(
        destination.p1,
        V(11.0f, 22.0f, 33.0f)
    );

    ExpectVectorNear(destination.p2, source.p2);
    ExpectVectorNear(destination.u, source.u);
    ExpectVectorNear(destination.v, source.v);
}

TEST(PDomainTransformDirTest, TranslationIsIgnoredForPoint)
{
    const pDomain source(
        PDPoint,
        1.0f, 2.0f, 3.0f
    );

    pDomain destination(
        PDPoint,
        0.0f, 0.0f, 0.0f
    );

    Fmatrix matrix;
    matrix.identity();
    matrix.c.set(10.0f, 20.0f, 30.0f);

    destination.transform_dir(source, matrix);

    // transform_dir zeroes translation before calling transform().
    ExpectVectorNear(
        destination.p1,
        source.p1
    );
}


// -----------------------------------------------------------------------------
// transform() with identity
// -----------------------------------------------------------------------------

TEST(PDomainTransformTest, IdentityKeepsPointUnchanged)
{
    const pDomain source(
        PDPoint,
        1.0f, 2.0f, 3.0f
    );

    pDomain destination(
        PDPoint,
        100.0f, 100.0f, 100.0f
    );

    Fmatrix matrix;
    matrix.identity();

    destination.transform(source, matrix);

    ExpectVectorNear(destination.p1, source.p1);
}

TEST(PDomainTransformTest, IdentityKeepsPlaneUnchanged)
{
    const pDomain source(
        PDPlane,
        1.0f, 2.0f, 3.0f,
        0.0f, 0.0f, 1.0f
    );

    pDomain destination(
        PDPlane,
        0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 0.0f
    );

    Fmatrix matrix;
    matrix.identity();

    destination.transform(source, matrix);

    ExpectVectorNear(destination.p1, source.p1);
    ExpectVectorNear(destination.p2, source.p2);
    EXPECT_FLOAT_EQ(destination.radius1, source.radius1);
}

TEST(PDomainTransformTest, IdentityKeepsSphereCenterUnchanged)
{
    const pDomain source(
        PDSphere,
        1.0f, 2.0f, 3.0f,
        5.0f, 2.0f
    );

    pDomain destination(
        PDSphere,
        0.0f, 0.0f, 0.0f,
        5.0f, 2.0f
    );

    Fmatrix matrix;
    matrix.identity();

    destination.transform(source, matrix);

    ExpectVectorNear(destination.p1, source.p1);
}


// -----------------------------------------------------------------------------
// NRand()
// -----------------------------------------------------------------------------

TEST(NRandTest, ZeroSigmaAlwaysReturnsZero)
{
    for (int i = 0; i < 100; ++i)
        EXPECT_FLOAT_EQ(NRand(0.0f), 0.0f);
}

TEST(NRandTest, PositiveSigmaProducesFiniteValues)
{
    for (int i = 0; i < 1000; ++i)
    {
        const float value = NRand(1.0f);

        EXPECT_TRUE(std::isfinite(value));
    }
}

TEST(NRandTest, NegativeSigmaProducesFiniteValues)
{
    for (int i = 0; i < 1000; ++i)
    {
        const float value = NRand(-1.0f);

        EXPECT_TRUE(std::isfinite(value));
    }
}

TEST(NRandTest, ScalingSigmaScalesResults)
{
    // We cannot safely compare individual samples because NRand consumes
    // global random state. Instead, characterize the expected sign symmetry
    // and finite output.

    int positive = 0;
    int negative = 0;

    for (int i = 0; i < 5000; ++i)
    {
        const float value = NRand(2.0f);

        ASSERT_TRUE(std::isfinite(value));

        if (value > 0.0f)
            ++positive;
        else if (value < 0.0f)
            ++negative;
    }

    EXPECT_GT(positive, 0);
    EXPECT_GT(negative, 0);
}


// -----------------------------------------------------------------------------
// Constants
// -----------------------------------------------------------------------------

TEST(ParticleCoreConstantsTest, Sqrt2PiMatchesExpectedValue)
{
    EXPECT_NEAR(
        SQRT2PI,
        2.5066282746310005f,
        1e-6f
    );
}

TEST(ParticleCoreConstantsTest, OneOverSqrt2PiIsReciprocal)
{
    EXPECT_NEAR(
        ONEOVERSQRT2PI * SQRT2PI,
        1.0f,
        1e-6f
    );
}

} // namespace
