#include "stdafx.h"

#include "_cylinder.h"

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

TEST(Fcylinder, Invalidate)
{
    Fcylinder cylinder;

    cylinder.m_center.set(1.0f, 2.0f, 3.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 5.0f;

    EXPECT_EQ(&cylinder.invalidate(), &cylinder);

    expect_vec_near(cylinder.m_center, 0.0f, 0.0f, 0.0f);
    expect_vec_near(cylinder.m_direction, 0.0f, 0.0f, 0.0f);
    EXPECT_FLOAT_EQ(cylinder.m_height, 0.0f);
    EXPECT_FLOAT_EQ(cylinder.m_radius, 0.0f);
}

TEST(Fcylinder, ParallelAxisIntersectsBothCaps)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{0.0f, 0.0f, -10.0f},
        Fvector{0.0f, 0.0f, 1.0f},
        t,
        code);

    EXPECT_EQ(count, 2);

    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_FLOAT_EQ(t[1], 15.0f);

    EXPECT_EQ(code[0], Fcylinder::cyl_cap);
    EXPECT_EQ(code[1], Fcylinder::cyl_cap);
}

TEST(Fcylinder, ParallelAxisOutsideRadiusMisses)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{3.0f, 0.0f, -10.0f},
        Fvector{0.0f, 0.0f, 1.0f},
        t,
        code);

    EXPECT_EQ(count, 0);
}

TEST(Fcylinder, PerpendicularAxisIntersectsBothWalls)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{-5.0f, 0.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        t,
        code);

    EXPECT_EQ(count, 2);

    EXPECT_FLOAT_EQ(t[0], 3.0f);
    EXPECT_FLOAT_EQ(t[1], 7.0f);

    EXPECT_EQ(code[0], Fcylinder::cyl_wall);
    EXPECT_EQ(code[1], Fcylinder::cyl_wall);
}

TEST(Fcylinder, PerpendicularAxisMissesOutsideCaps)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{-5.0f, 0.0f, 6.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        t,
        code);

    EXPECT_EQ(count, 0);
}

TEST(Fcylinder, PerpendicularAxisMissesOutsideRadius)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{-5.0f, 3.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        t,
        code);

    EXPECT_EQ(count, 0);
}

TEST(Fcylinder, PerpendicularAxisTangent)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{-5.0f, 2.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        t,
        code);

    EXPECT_EQ(count, 1);
    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_EQ(code[0], Fcylinder::cyl_wall);
}

TEST(Fcylinder, ObliqueRayIntersectsTwoCaps)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 5.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{0.0f, 0.0f, -10.0f},
        Fvector{0.2f, 0.0f, 1.0f},
        t,
        code);

    EXPECT_EQ(count, 2);

    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_FLOAT_EQ(t[1], 15.0f);

    EXPECT_EQ(code[0], Fcylinder::cyl_cap);
    EXPECT_EQ(code[1], Fcylinder::cyl_cap);
}

TEST(Fcylinder, ObliqueRayIntersectsCapAndWall)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{-3.0f, 0.0f, -10.0f},
        Fvector{1.0f, 0.0f, 2.0f},
        t,
        code);

    EXPECT_EQ(count, 2);

    EXPECT_EQ(code[0], Fcylinder::cyl_cap);
    EXPECT_EQ(code[1], Fcylinder::cyl_wall);

    EXPECT_NEAR(t[0], 5.0f / std::sqrt(5.0f), 1e-5f);
    EXPECT_NEAR(t[1], 1.0f / std::sqrt(5.0f), 1e-5f);
}

TEST(Fcylinder, RayIntersectionOriginOutside)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float dist = 100.0f;

    const auto result = cylinder.intersect(
        Fvector{-5.0f, 0.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        dist);

    EXPECT_EQ(result, Fcylinder::rpOriginOutside);
    EXPECT_FLOAT_EQ(dist, 3.0f);
}

TEST(Fcylinder, RayIntersectionOriginInside)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float dist = 100.0f;

    const auto result = cylinder.intersect(
        Fvector{0.0f, 0.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        dist);

    EXPECT_EQ(result, Fcylinder::rpOriginInside);
    EXPECT_FLOAT_EQ(dist, 2.0f);
}

TEST(Fcylinder, RayIntersectionMiss)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float dist = 100.0f;

    const auto result = cylinder.intersect(
        Fvector{-5.0f, 3.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        dist);

    EXPECT_EQ(result, Fcylinder::rpNone);
    EXPECT_FLOAT_EQ(dist, 100.0f);
}

TEST(Fcylinder, RayIntersectionDoesNotIncreaseDistance)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float dist = 2.0f;

    const auto result = cylinder.intersect(
        Fvector{-5.0f, 0.0f, 0.0f},
        Fvector{1.0f, 0.0f, 0.0f},
        dist);

    EXPECT_EQ(result, Fcylinder::rpNone);
    EXPECT_FLOAT_EQ(dist, 2.0f);
}

TEST(Fcylinder, ReverseAxisDirection)
{
    Fcylinder cylinder;
    cylinder.m_center.set(0.0f, 0.0f, 0.0f);
    cylinder.m_direction.set(0.0f, 0.0f, 1.0f);
    cylinder.m_height = 10.0f;
    cylinder.m_radius = 2.0f;

    float t[2] = {};
    Fcylinder::ecode code[2] = {};

    const int count = cylinder.intersect(
        Fvector{0.0f, 0.0f, 10.0f},
        Fvector{0.0f, 0.0f, -1.0f},
        t,
        code);

    EXPECT_EQ(count, 2);

    EXPECT_FLOAT_EQ(t[0], 5.0f);
    EXPECT_FLOAT_EQ(t[1], 15.0f);

    EXPECT_EQ(code[0], Fcylinder::cyl_cap);
    EXPECT_EQ(code[1], Fcylinder::cyl_cap);
}
