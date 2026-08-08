#include "stdafx.h"

#include "_fbox2.h"

#include <gtest/gtest.h>

namespace
{
    using Box = Fbox2;
    using Vec = Fvector2;

    void expect_vec_eq(const Vec& actual, float x, float y)
    {
        EXPECT_FLOAT_EQ(actual.x, x);
        EXPECT_FLOAT_EQ(actual.y, y);
    }

    void expect_box_eq(
        const Box& actual,
        float min_x, float min_y,
        float max_x, float max_y)
    {
        expect_vec_eq(actual.min, min_x, min_y);
        expect_vec_eq(actual.max, max_x, max_y);
    }
}


// -----------------------------------------------------------------------------
// Construction / assignment
// -----------------------------------------------------------------------------

TEST(Fbox2, SetFromVectors)
{
    Box box;

    Vec min = {1.0f, 2.0f};
    Vec max = {3.0f, 4.0f};

    EXPECT_EQ(&box.set(min, max), &box);

    expect_box_eq(box, 1, 2, 3, 4);
}


TEST(Fbox2, SetFromCoordinates)
{
    Box box;

    EXPECT_EQ(&box.set(1, 2, 3, 4), &box);

    expect_box_eq(box, 1, 2, 3, 4);
}


TEST(Fbox2, SetFromBox)
{
    Box source;
    source.set(1, 2, 3, 4);

    Box box;

    EXPECT_EQ(&box.set(source), &box);

    expect_box_eq(box, 1, 2, 3, 4);
}


TEST(Fbox2, Null)
{
    Box box;
    box.set(1, 2, 3, 4);

    EXPECT_EQ(&box.null(), &box);

    expect_box_eq(box, 0, 0, 0, 0);
}


TEST(Fbox2, Identity)
{
    Box box;

    EXPECT_EQ(&box.identity(), &box);

    // Characterizes the current implementation.
    // Note that the implementation calls min.set() with 3 arguments even
    // though Tvector is _vector2<T>; compilation of this test therefore
    // depends on the actual _vector2 API accepting that call.
    expect_box_eq(box, -0.5f, -0.5f, 0.5f, 0.5f);
}


TEST(Fbox2, Invalidate)
{
    Box box;

    EXPECT_EQ(&box.invalidate(), &box);

    EXPECT_EQ(box.min.x, type_max(float));
    EXPECT_EQ(box.min.y, type_max(float));
    EXPECT_EQ(box.max.x, type_min(float));
    EXPECT_EQ(box.max.y, type_min(float));
}


// -----------------------------------------------------------------------------
// Grow / shrink
// -----------------------------------------------------------------------------

TEST(Fbox2, GrowScalar)
{
    Box box;
    box.set(1, 2, 5, 6);

    EXPECT_EQ(&box.grow(2.0f), &box);

    expect_box_eq(box, -1, 0, 7, 8);
}


TEST(Fbox2, GrowVector)
{
    Box box;
    box.set(1, 2, 5, 6);

    Vec amount = {2, 3};

    EXPECT_EQ(&box.grow(amount), &box);

    expect_box_eq(box, -1, -1, 7, 9);
}


TEST(Fbox2, ShrinkScalar)
{
    Box box;
    box.set(1, 2, 7, 8);

    EXPECT_EQ(&box.shrink(2.0f), &box);

    expect_box_eq(box, 3, 4, 5, 6);
}


TEST(Fbox2, ShrinkVector)
{
    Box box;
    box.set(1, 2, 7, 8);

    Vec amount = {2, 3};

    EXPECT_EQ(&box.shrink(amount), &box);

    expect_box_eq(box, 3, 5, 5, 5);
}


// -----------------------------------------------------------------------------
// Translation
// -----------------------------------------------------------------------------

TEST(Fbox2, Add)
{
    Box box;
    box.set(1, 2, 5, 6);

    Vec offset = {10, 20};

    EXPECT_EQ(&box.add(offset), &box);

    expect_box_eq(box, 11, 22, 15, 26);
}


TEST(Fbox2, Offset)
{
    Box box;
    box.set(1, 2, 5, 6);

    Vec offset = {10, 20};

    EXPECT_EQ(&box.offset(offset), &box);

    expect_box_eq(box, 11, 22, 15, 26);
}


TEST(Fbox2, AddFromOtherBoxWithOffset)
{
    Box source;
    source.set(1, 2, 5, 6);

    Vec offset = {10, 20};

    Box box;

    EXPECT_EQ(&box.add(source, offset), &box);

    expect_box_eq(box, 11, 22, 15, 26);
}


// -----------------------------------------------------------------------------
// Contains
// -----------------------------------------------------------------------------

TEST(Fbox2, ContainsPoint)
{
    Box box;
    box.set(0, 0, 10, 20);

    EXPECT_TRUE(box.contains(5, 10));
}


TEST(Fbox2, ContainsPointOnBoundary)
{
    Box box;
    box.set(0, 0, 10, 20);

    EXPECT_TRUE(box.contains(0, 0));
    EXPECT_TRUE(box.contains(10, 20));
    EXPECT_TRUE(box.contains(0, 20));
    EXPECT_TRUE(box.contains(10, 0));
}


TEST(Fbox2, DoesNotContainPointOutside)
{
    Box box;
    box.set(0, 0, 10, 20);

    EXPECT_FALSE(box.contains(-0.001f, 10));
    EXPECT_FALSE(box.contains(10.001f, 10));
    EXPECT_FALSE(box.contains(5, -0.001f));
    EXPECT_FALSE(box.contains(5, 20.001f));
}


TEST(Fbox2, ContainsVector)
{
    Box box;
    box.set(0, 0, 10, 20);

    Vec point = {5, 10};

    EXPECT_TRUE(box.contains(point));
}


TEST(Fbox2, ContainsBox)
{
    Box outer;
    outer.set(0, 0, 10, 20);

    Box inner;
    inner.set(2, 3, 8, 17);

    EXPECT_TRUE(outer.contains(inner));
}


TEST(Fbox2, DoesNotContainPartiallyOutsideBox)
{
    Box outer;
    outer.set(0, 0, 10, 20);

    Box inner;
    inner.set(2, 3, 11, 17);

    EXPECT_FALSE(outer.contains(inner));
}


TEST(Fbox2, DoesNotContainBoxOutside)
{
    Box outer;
    outer.set(0, 0, 10, 20);

    Box other;
    other.set(20, 30, 40, 50);

    EXPECT_FALSE(outer.contains(other));
}


// -----------------------------------------------------------------------------
// Similar
// -----------------------------------------------------------------------------

TEST(Fbox2, SimilarBoxes)
{
    Box a;
    Box b;

    a.set(1, 2, 3, 4);
    b.set(1, 2, 3, 4);

    EXPECT_TRUE(a.similar(b));
}


TEST(Fbox2, DifferentBoxesAreNotSimilar)
{
    Box a;
    Box b;

    a.set(1, 2, 3, 4);
    b.set(1, 2, 3, 5);

    EXPECT_FALSE(a.similar(b));
}


// -----------------------------------------------------------------------------
// Modify / merge
// -----------------------------------------------------------------------------

TEST(Fbox2, ModifyExpandsBox)
{
    Box box;
    box.set(0, 0, 10, 20);

    Vec point = {-5, 30};

    EXPECT_EQ(&box.modify(point), &box);

    expect_box_eq(box, -5, 0, 10, 30);
}


TEST(Fbox2, ModifyPointInsideDoesNothing)
{
    Box box;
    box.set(0, 0, 10, 20);

    Vec point = {5, 10};

    box.modify(point);

    expect_box_eq(box, 0, 0, 10, 20);
}


TEST(Fbox2, MergeBox)
{
    Box box;
    box.set(0, 0, 10, 20);

    Box other;
    other.set(-5, 5, 30, 15);

    EXPECT_EQ(&box.merge(other), &box);

    expect_box_eq(box, -5, 0, 30, 20);
}


TEST(Fbox2, MergeTwoBoxes)
{
    Box a;
    a.set(0, 0, 10, 20);

    Box b;
    b.set(-5, 5, 30, 40);

    Box result;

    EXPECT_EQ(&result.merge(a, b), &result);

    expect_box_eq(result, -5, 0, 30, 40);
}


TEST(Fbox2, MergeTwoBoxesResetsExistingResult)
{
    Box a;
    a.set(0, 0, 10, 20);

    Box b;
    b.set(30, 40, 50, 60);

    Box result;
    result.set(-100, -100, 100, 100);

    result.merge(a, b);

    expect_box_eq(result, 0, 0, 50, 60);
}


// -----------------------------------------------------------------------------
// Size / radius / center / sphere
// -----------------------------------------------------------------------------

TEST(Fbox2, GetSize)
{
    Box box;
    box.set(1, 2, 11, 22);

    Vec size;

    box.getsize(size);

    expect_vec_eq(size, 10, 20);
}


TEST(Fbox2, GetRadiusVector)
{
    Box box;
    box.set(0, 0, 10, 20);

    Vec radius;

    box.getradius(radius);

    expect_vec_eq(radius, 5, 10);
}


TEST(Fbox2, GetRadius)
{
    Box box;
    box.set(0, 0, 6, 8);

    // Half-size is (3, 4), magnitude = 5.
    EXPECT_FLOAT_EQ(box.getradius(), 5.0f);
}


TEST(Fbox2, GetCenter)
{
    Box box;
    box.set(0, 10, 10, 30);

    Vec center;

    box.getcenter(center);

    expect_vec_eq(center, 5, 20);
}


TEST(Fbox2, GetSphere)
{
    Box box;
    box.set(-3, -4, 3, 4);

    Vec center;
    float radius;

    box.getsphere(center, radius);

    expect_vec_eq(center, 0, 0);

    // Distance from center to max = sqrt(3^2 + 4^2).
    EXPECT_FLOAT_EQ(radius, 5.0f);
}


// -----------------------------------------------------------------------------
// Intersection
// -----------------------------------------------------------------------------

TEST(Fbox2, IntersectsOverlappingBoxes)
{
    Box a;
    a.set(0, 0, 10, 10);

    Box b;
    b.set(5, 5, 15, 15);

    EXPECT_TRUE(a.intersect(b));
}


TEST(Fbox2, IntersectsWhenTouchingXEdge)
{
    Box a;
    a.set(0, 0, 10, 10);

    Box b;
    b.set(10, 0, 20, 10);

    EXPECT_TRUE(a.intersect(b));
}


TEST(Fbox2, IntersectsWhenTouchingYEdge)
{
    Box a;
    a.set(0, 0, 10, 10);

    Box b;
    b.set(0, 10, 10, 20);

    EXPECT_TRUE(a.intersect(b));
}


TEST(Fbox2, DoesNotIntersectWhenSeparatedOnX)
{
    Box a;
    a.set(0, 0, 10, 10);

    Box b;
    b.set(10.001f, 0, 20, 10);

    EXPECT_FALSE(a.intersect(b));
}


TEST(Fbox2, DoesNotIntersectWhenSeparatedOnY)
{
    Box a;
    a.set(0, 0, 10, 10);

    Box b;
    b.set(0, 10.001f, 10, 20);

    EXPECT_FALSE(a.intersect(b));
}


TEST(Fbox2, OneBoxContainsAnother)
{
    Box outer;
    outer.set(0, 0, 10, 10);

    Box inner;
    inner.set(2, 2, 8, 8);

    EXPECT_TRUE(outer.intersect(inner));
    EXPECT_TRUE(inner.intersect(outer));
}


// -----------------------------------------------------------------------------
// sort
// -----------------------------------------------------------------------------

TEST(Fbox2, SortsReversedX)
{
    Box box;
    box.set(10, 2, 0, 8);

    EXPECT_EQ(&box.sort(), &box);

    expect_box_eq(box, 0, 2, 10, 8);
}


TEST(Fbox2, SortsReversedY)
{
    Box box;
    box.set(1, 10, 9, 0);

    EXPECT_EQ(&box.sort(), &box);

    expect_box_eq(box, 1, 0, 9, 10);
}


TEST(Fbox2, SortsBothAxes)
{
    Box box;
    box.set(10, 20, 0, 0);

    EXPECT_EQ(&box.sort(), &box);

    expect_box_eq(box, 0, 0, 10, 20);
}


TEST(Fbox2, SortLeavesAlreadySortedBoxUnchanged)
{
    Box box;
    box.set(1, 2, 10, 20);

    box.sort();

    expect_box_eq(box, 1, 2, 10, 20);
}


// -----------------------------------------------------------------------------
// Pick
// -----------------------------------------------------------------------------

TEST(Fbox2, PickHitsLeftEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 0};
    Vec dir = {1, 0};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox2, PickHitsRightEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {2, 0};
    Vec dir = {-1, 0};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox2, PickHitsBottomEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {0, -2};
    Vec dir = {0, 1};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox2, PickHitsTopEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {0, 2};
    Vec dir = {0, -1};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox2, PickMisses)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 2};
    Vec dir = {1, 0};

    EXPECT_FALSE(box.Pick(start, dir));
}


TEST(Fbox2, PickWithZeroXDirection)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {0, -2};
    Vec dir = {0, 1};

    EXPECT_TRUE(box.Pick(start, dir));
}


TEST(Fbox2, PickWithZeroYDirection)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 0};
    Vec dir = {1, 0};

    EXPECT_TRUE(box.Pick(start, dir));
}


// -----------------------------------------------------------------------------
// pick_exact
// -----------------------------------------------------------------------------

TEST(Fbox2, PickExactHits)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 0};
    Vec dir = {1, 0};

    EXPECT_TRUE(box.pick_exact(start, dir));
}


TEST(Fbox2, PickExactMisses)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 2};
    Vec dir = {1, 0};

    EXPECT_FALSE(box.pick_exact(start, dir));
}


TEST(Fbox2, PickExactHitsNearBoundary)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec start = {-2, 1.0f + EPS * 0.5f};
    Vec dir = {1, 0};

    EXPECT_TRUE(box.pick_exact(start, dir));
}


// -----------------------------------------------------------------------------
// Pick2
// -----------------------------------------------------------------------------

TEST(Fbox2, Pick2ReturnsOriginWhenInside)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {0, 0};
    Vec dir = {1, 0};
    Vec coord;

    EXPECT_TRUE(box.Pick2(origin, dir, coord));

    expect_vec_eq(coord, 0, 0);
}


TEST(Fbox2, Pick2ReturnsIntersectionOnLeftEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {-2, 0};
    Vec dir = {1, 0};
    Vec coord;

    EXPECT_TRUE(box.Pick2(origin, dir, coord));

    expect_vec_eq(coord, -1, 0);
}


TEST(Fbox2, Pick2ReturnsIntersectionOnRightEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {2, 0};
    Vec dir = {-1, 0};
    Vec coord;

    EXPECT_TRUE(box.Pick2(origin, dir, coord));

    expect_vec_eq(coord, 1, 0);
}


TEST(Fbox2, Pick2ReturnsIntersectionOnBottomEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {0, -2};
    Vec dir = {0, 1};
    Vec coord;

    EXPECT_TRUE(box.Pick2(origin, dir, coord));

    expect_vec_eq(coord, 0, -1);
}


TEST(Fbox2, Pick2ReturnsIntersectionOnTopEdge)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {0, 2};
    Vec dir = {0, -1};
    Vec coord;

    EXPECT_TRUE(box.Pick2(origin, dir, coord));

    expect_vec_eq(coord, 0, 1);
}


TEST(Fbox2, Pick2Misses)
{
    Box box;
    box.set(-1, -1, 1, 1);

    Vec origin = {-2, 2};
    Vec dir = {1, 0};
    Vec coord;

    EXPECT_FALSE(box.Pick2(origin, dir, coord));
}


// -----------------------------------------------------------------------------
// Corners
// -----------------------------------------------------------------------------

TEST(Fbox2, GetPointCurrentImplementation)
{
    Box box;
    box.set(1, 2, 10, 20);

    Vec result;

    box.getpoint(0, result);
    expect_vec_eq(result, 1, 2);

    box.getpoint(1, result);
    expect_vec_eq(result, 1, 2);

    box.getpoint(2, result);
    expect_vec_eq(result, 10, 2);

    box.getpoint(3, result);
    expect_vec_eq(result, 10, 2);
}


TEST(Fbox2, GetPointOutOfRangeReturnsZero)
{
    Box box;
    box.set(1, 2, 10, 20);

    Vec result;

    box.getpoint(4, result);

    expect_vec_eq(result, 0, 0);
}


TEST(Fbox2, GetPointsCurrentImplementation)
{
    Box box;
    box.set(1, 2, 10, 20);

    Vec points[4];

    box.getpoints(points);

    expect_vec_eq(points[0], 1, 2);
    expect_vec_eq(points[1], 1, 2);
    expect_vec_eq(points[2], 10, 2);
    expect_vec_eq(points[3], 10, 2);
}


// -----------------------------------------------------------------------------
// _valid
// -----------------------------------------------------------------------------

TEST(Fbox2, ValidBoxIsValid)
{
    Box box;
    box.set(0, 0, 10, 20);

    EXPECT_TRUE(_valid(box));
}


TEST(Fbox2, InvalidBoxIsInvalid)
{
    Box box;
    box.invalidate();

    EXPECT_FALSE(_valid(box));
}
