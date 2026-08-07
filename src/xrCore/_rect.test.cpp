#include "stdafx.h"

#include "_rect.h"

#include <gtest/gtest.h>

namespace
{
    using Rect = Frect;
    using Vec  = Fvector2;

    void ExpectRectEq(
        const Rect& r,
        float x1, float y1,
        float x2, float y2)
    {
        EXPECT_FLOAT_EQ(r.x1, x1);
        EXPECT_FLOAT_EQ(r.y1, y1);
        EXPECT_FLOAT_EQ(r.x2, x2);
        EXPECT_FLOAT_EQ(r.y2, y2);
    }
}

TEST(Rect, SetComponents)
{
    Rect r;

    auto& ret = r.set(1,2,3,4);

    EXPECT_EQ(&ret, &r);
    ExpectRectEq(r,1,2,3,4);
}

TEST(Rect, SetVectors)
{
    Vec lt, rb;

    lt.set(1,2);
    rb.set(3,4);

    Rect r;
    r.set(lt,rb);

    ExpectRectEq(r,1,2,3,4);
}

TEST(Rect, SetRectangle)
{
    Rect a,b;

    a.set(1,2,3,4);

    b.set(a);

    ExpectRectEq(b,1,2,3,4);
}

TEST(Rect, Null)
{
    Rect r;

    r.set(1,2,3,4);
    r.null();

    ExpectRectEq(r,0,0,0,0);
}

TEST(Rect, Add)
{
    Rect r;

    r.set(1,2,3,4);

    r.add(10,20);

    ExpectRectEq(r,11,22,13,24);
}

TEST(Rect, Sub)
{
    Rect r;

    r.set(11,22,13,24);

    r.sub(10,20);

    ExpectRectEq(r,1,2,3,4);
}

TEST(Rect, Multiply)
{
    Rect r;

    r.set(1,2,3,4);

    r.mul(2,3);

    ExpectRectEq(r,2,6,6,12);
}

TEST(Rect, Divide)
{
    Rect r;

    r.set(2,6,6,12);

    r.div(2,3);

    ExpectRectEq(r,1,2,3,4);
}

TEST(Rect, AddFromSource)
{
    Rect src;
    Rect dst;

    src.set(1,2,3,4);

    dst.add(src,10,20);

    ExpectRectEq(dst,11,22,13,24);
}

TEST(Rect, SubFromSource)
{
    Rect src;
    Rect dst;

    src.set(11,22,13,24);

    dst.sub(src,10,20);

    ExpectRectEq(dst,1,2,3,4);
}

TEST(Rect, MultiplyFromSource)
{
    Rect src;
    Rect dst;

    src.set(1,2,3,4);

    dst.mul(src,2,3);

    ExpectRectEq(dst,2,6,6,12);
}

TEST(Rect, DivideFromSource)
{
    Rect src;
    Rect dst;

    src.set(2,6,6,12);

    dst.div(src,2,3);

    ExpectRectEq(dst,1,2,3,4);
}

TEST(Rect, ContainsPoint)
{
    Rect r;

    r.set(0,0,10,20);

    EXPECT_TRUE(r.in(0,0));
    EXPECT_TRUE(r.in(10,20));
    EXPECT_TRUE(r.in(5,5));

    EXPECT_FALSE(r.in(-1,5));
    EXPECT_FALSE(r.in(5,-1));
    EXPECT_FALSE(r.in(11,5));
    EXPECT_FALSE(r.in(5,21));
}

TEST(Rect, ContainsVector)
{
    Rect r;
    Vec p;

    r.set(0,0,10,20);

    p.set(5,6);

    EXPECT_TRUE(r.in(p));

    p.set(100,0);

    EXPECT_FALSE(r.in(p));
}

TEST(Rect, WidthHeight)
{
    Rect r;

    r.set(1,2,11,22);

    EXPECT_FLOAT_EQ(r.width(),10);
    EXPECT_FLOAT_EQ(r.height(),20);
}

TEST(Rect, GetSize)
{
    Rect r;
    Vec sz;

    r.set(1,2,11,22);

    r.getsize(sz);

    EXPECT_FLOAT_EQ(sz.x,10);
    EXPECT_FLOAT_EQ(sz.y,20);
}

TEST(Rect, GetCenter)
{
    Rect r;
    Vec c;

    r.set(2,4,6,8);

    r.getcenter(c);

    EXPECT_FLOAT_EQ(c.x,4);
    EXPECT_FLOAT_EQ(c.y,6);
}

TEST(Rect, Grow)
{
    Rect r;

    r.set(2,3,4,5);

    r.grow(1,2);

    ExpectRectEq(r,1,1,5,7);
}

TEST(Rect, Shrink)
{
    Rect r;

    r.set(1,1,5,7);

    r.shrink(1,2);

    ExpectRectEq(r,2,3,4,5);
}

TEST(Rect, Intersects)
{
    Rect a,b;

    a.set(0,0,10,10);
    b.set(10,10,20,20);

    EXPECT_TRUE(a.intersected(b));
}

TEST(Rect, DoesNotIntersect)
{
    Rect a,b;

    a.set(0,0,10,10);
    b.set(11,11,20,20);

    EXPECT_FALSE(a.intersected(b));
}

TEST(Rect, Intersection)
{
    Rect a,b,c;

    a.set(0,0,10,10);
    b.set(5,2,12,8);

    EXPECT_TRUE(c.intersection(a,b));

    ExpectRectEq(c,5,2,10,8);
}

TEST(Rect, IntersectionFails)
{
    Rect a,b,c;

    a.set(0,0,10,10);
    b.set(20,20,30,30);

    EXPECT_FALSE(c.intersection(a,b));
}
