#include "stdafx.h"

#include "_sphere.h"

#include <gtest/gtest.h>

template <typename T>
void expect_vec_near(
    const _vector3<T>& actual,
    T x,
    T y,
    T z,
    T abs_error = T(1e-5))
{
    EXPECT_NEAR(actual.x, x, abs_error);
    EXPECT_NEAR(actual.y, y, abs_error);
    EXPECT_NEAR(actual.z, z, abs_error);
}

template <typename T>
void expect_vec_near(
    const _vector3<T>& actual,
    const _vector3<T>& expected,
    T abs_error = T(1e-5))
{
    expect_vec_near(
        actual,
        expected.x,
        expected.y,
        expected.z,
        abs_error);
}

TEST(Fsphere, SetPointAndRadius)
{
    Fsphere sphere;

    sphere.set(Fvector{1.0f, 2.0f, 3.0f}, 4.0f);

    expect_vec_near(sphere.P, 1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(sphere.R, 4.0f);
}

TEST(Fsphere, SetFromSphere)
{
    Fsphere source;
    source.set(Fvector{1.0f, 2.0f, 3.0f}, 4.0f);

    Fsphere result;
    result.set(source);

    expect_vec_near(result.P, 1.0f, 2.0f, 3.0f);
    EXPECT_FLOAT_EQ(result.R, 4.0f);
}

TEST(Fsphere, Identity)
{
    Fsphere sphere;

    sphere.identity();

    expect_vec_near(sphere.P, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(sphere.R, 1.0f);
}

TEST(Fsphere, RayIntersectionTwoPoints)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        100.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_EQ(quantity, 2);
    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_FLOAT_EQ(t[1], 15.0f);
}

TEST(Fsphere, RayIntersectionOriginInside)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{0.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        100.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpOriginInside);
    EXPECT_EQ(quantity, 1);
    EXPECT_FLOAT_EQ(t[0], 5.0f);
}

TEST(Fsphere, RayIntersectionTangent)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 5.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        100.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_EQ(quantity, 1);
    EXPECT_FLOAT_EQ(t[0], 10.0f);
}

TEST(Fsphere, RayIntersectionMiss)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 6.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        100.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpNone);
    EXPECT_EQ(quantity, 0);
}

TEST(Fsphere, RayIntersectionBehindOrigin)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        100.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpNone);
    EXPECT_EQ(quantity, 0);
}

TEST(Fsphere, RayIntersectionRangeLimitsResult)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    int quantity = 0;
    float t[2] = {};

    const auto result = sphere.intersect(
        start,
        dir,
        4.0f,
        quantity,
        t);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_EQ(quantity, 2);
    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_FLOAT_EQ(t[1], 15.0f);
}

TEST(Fsphere, IntersectFullUpdatesDistance)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float dist = 100.0f;

    const auto result = sphere.intersect_full(start, dir, dist);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_FLOAT_EQ(dist, 5.0f);
}

TEST(Fsphere, IntersectFullDoesNotIncreaseDistance)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float dist = 3.0f;

    const auto result = sphere.intersect_full(start, dir, dist);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_FLOAT_EQ(dist, 3.0f);
}

TEST(Fsphere, IntersectDistanceUpdatesOnHit)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float dist = 100.0f;

    const auto result = sphere.intersect(start, dir, dist);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_FLOAT_EQ(dist, 5.0f);
}

TEST(Fsphere, IntersectDistanceReturnsNoneWhenHitIsFarther)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float dist = 3.0f;

    const auto result = sphere.intersect(start, dir, dist);

    EXPECT_EQ(result, Fsphere::rpNone);
    EXPECT_FLOAT_EQ(dist, 3.0f);
}

TEST(Fsphere, Intersect2Hit)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 0.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float range = 100.0f;

    const auto result = sphere.intersect2(start, dir, range);

    EXPECT_EQ(result, Fsphere::rpOriginOutside);
    EXPECT_FLOAT_EQ(range, 5.0f);
}

TEST(Fsphere, Intersect2Miss)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    const Fvector start{-10.0f, 6.0f, 0.0f};
    const Fvector dir{1.0f, 0.0f, 0.0f};

    float range = 100.0f;

    const auto result = sphere.intersect2(start, dir, range);

    EXPECT_EQ(result, Fsphere::rpNone);
    EXPECT_FLOAT_EQ(range, 100.0f);
}

TEST(Fsphere, SimpleRayIntersectionHit)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_TRUE(
        sphere.intersect(
            Fvector{-10.0f, 0.0f, 0.0f},
            Fvector{1.0f, 0.0f, 0.0f}));
}

TEST(Fsphere, SimpleRayIntersectionMiss)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_FALSE(
        sphere.intersect(
            Fvector{-10.0f, 6.0f, 0.0f},
            Fvector{1.0f, 0.0f, 0.0f}));
}

TEST(Fsphere, SphereIntersectionOverlapping)
{
    Fsphere a;
    a.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    Fsphere b;
    b.set(Fvector{8.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_TRUE(a.intersect(b));
    EXPECT_TRUE(b.intersect(a));
}

TEST(Fsphere, SphereIntersectionSeparated)
{
    Fsphere a;
    a.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    Fsphere b;
    b.set(Fvector{11.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_FALSE(a.intersect(b));
    EXPECT_FALSE(b.intersect(a));
}

TEST(Fsphere, SphereIntersectionTouching)
{
    Fsphere a;
    a.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    Fsphere b;
    b.set(Fvector{10.0f, 0.0f, 0.0f}, 5.0f);

    // Current implementation uses strict '<'.
    EXPECT_FALSE(a.intersect(b));
}

TEST(Fsphere, ContainsPointInside)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_TRUE(sphere.contains(Fvector{3.0f, 0.0f, 0.0f}));
}

TEST(Fsphere, ContainsPointOnBoundary)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_TRUE(sphere.contains(Fvector{5.0f, 0.0f, 0.0f}));
}

TEST(Fsphere, ContainsPointOutside)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_FALSE(sphere.contains(Fvector{5.1f, 0.0f, 0.0f}));
}

TEST(Fsphere, ContainsSphere)
{
    Fsphere outer;
    outer.set(Fvector{0.0f, 0.0f, 0.0f}, 10.0f);

    Fsphere inner;
    inner.set(Fvector{3.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_TRUE(outer.contains(inner));
}

TEST(Fsphere, DoesNotContainLargerSphere)
{
    Fsphere outer;
    outer.set(Fvector{0.0f, 0.0f, 0.0f}, 5.0f);

    Fsphere inner;
    inner.set(Fvector{0.0f, 0.0f, 0.0f}, 6.0f);

    EXPECT_FALSE(outer.contains(inner));
}

TEST(Fsphere, DoesNotContainSphereExtendingOutside)
{
    Fsphere outer;
    outer.set(Fvector{0.0f, 0.0f, 0.0f}, 10.0f);

    Fsphere inner;
    inner.set(Fvector{6.0f, 0.0f, 0.0f}, 5.0f);

    EXPECT_FALSE(outer.contains(inner));
}

TEST(Fsphere, ContainsIdenticalSphere)
{
    Fsphere a;
    a.set(Fvector{1.0f, 2.0f, 3.0f}, 5.0f);

    Fsphere b;
    b.set(Fvector{1.0f, 2.0f, 3.0f}, 5.0f);

    EXPECT_TRUE(a.contains(b));
}

TEST(Fsphere, Volume)
{
    Fsphere sphere;
    sphere.set(Fvector{0.0f, 0.0f, 0.0f}, 3.0f);

    EXPECT_NEAR(
        sphere.volume(),
        4.0f / 3.0f * PI * 27.0f,
        1e-5f);
}
