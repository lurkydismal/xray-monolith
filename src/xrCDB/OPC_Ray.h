///	Contains code for rays.
///
///	@file		IceRay.h
///	@author		Pierre Terdiman
///	@date		April, 4, 2000

#pragma once

/// Infinite 3D ray.
///
/// A ray is represented by an origin point and a direction vector extending
/// infinitely in the positive direction. The direction is expected to be
/// normalized unless otherwise specified by the calling code.
class ICEMATHS_API Ray {
public:
    /// Constructs an uninitialized ray.
    inline_ Ray() {}

    /// Constructs a ray from an origin and direction.
    ///
    /// @param orig Ray origin.
    /// @param dir Ray direction. Expected to be normalized.
    inline_ Ray( const Point& orig, const Point& dir )
        : mOrig( orig ), mDir( dir ) {}

    /// Constructs a copy of another ray.
    ///
    /// @param ray Ray to copy.
    inline_ Ray( const Ray& ray ) : mOrig( ray.mOrig ), mDir( ray.mDir ) {}

    /// Destroys the ray.
    inline_ ~Ray() {}

    Point mOrig; ///< Ray origin.
    Point mDir;  ///< Ray direction. Expected to be normalized.
};

/// Finite 3D line segment.
///
/// A segment is represented by its two endpoints.
class ICEMATHS_API Segment {
public:
    /// Constructs an uninitialized segment.
    inline_ Segment() {}

    /// Constructs a segment from two endpoints.
    ///
    /// @param p0 Segment start point.
    /// @param p1 Segment end point.
    inline_ Segment( const Point& p0, const Point& p1 )
        : mP0( p0 ), mP1( p1 ) {}

    /// Constructs a segment by copying another segment.
    ///
    /// @param seg Segment to copy.
    inline_ Segment( const Segment& seg ) : mP0( seg.mP0 ), mP1( seg.mP1 ) {}

    /// Destroys the segment.
    inline_ ~Segment() {}

    /// Returns the segment's start point.
    ///
    /// @return Reference to the first endpoint.
    inline_ const Point& GetOrigin() const { return mP0; }

    /// Computes the segment direction vector.
    ///
    /// The returned vector is not normalized and has a magnitude equal to the
    /// segment length.
    ///
    /// @return Direction vector from the first endpoint to the second.
    inline_ Point ComputeDirection() const { return mP1 - mP0; }

    /// Sets the segment from an origin and direction vector.
    ///
    /// The first endpoint is set to @p origin and the second endpoint becomes
    /// `origin + direction`.
    ///
    /// @param origin Segment start point.
    /// @param direction Vector from the start point to the end point.
    inline_ void SetOriginDirection( const Point& origin,
                                     const Point& direction ) {
        mP0 = mP1 = origin;
        mP1 += direction;
    }

    /// Computes a point on the segment.
    ///
    /// @param pt Receives the computed point.
    /// @param t Segment parameter, where `0` corresponds to `mP0` and `1`
    ///          corresponds to `mP1`.
    inline_ void ComputePoint( Point& pt, float t ) const {
        pt = mP0 + t * ( mP1 - mP0 );
    }

    Point mP0; ///< Segment start point.
    Point mP1; ///< Segment end point.
};
