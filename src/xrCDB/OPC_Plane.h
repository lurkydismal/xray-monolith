/// Plane equation and utility functions.
///
/// @file IcePlane.h
/// @author Pierre Terdiman
/// @date April 4, 2000

#pragma once

/// Tolerance used when testing whether a point lies on a plane.
#define PLANE_EPSILON        (1.0e-7f)

/// Plane represented by the equation: n · p + d = 0.
class ICEMATHS_API Plane
{
public:
    /// Constructs an uninitialized plane.
    inline_ Plane()
    {
    }

    /// Constructs a plane from its coefficients.
    ///
    /// @param nx X component of the normal.
    /// @param ny Y component of the normal.
    /// @param nz Z component of the normal.
    /// @param d Plane constant.
    inline_ Plane(float nx, float ny, float nz, float d) { Set(nx, ny, nz, d); }

    /// Constructs a plane from a point and a normal.
    ///
    /// @param p Point on the plane.
    /// @param n Plane normal.
    inline_ Plane(const Point& p, const Point& n) { Set(p, n); }

    /// Constructs a plane passing through three points.
    ///
    /// @param p0 First point.
    /// @param p1 Second point.
    /// @param p2 Third point.
    inline_ Plane(const Point& p0, const Point& p1, const Point& p2) { Set(p0, p1, p2); }

    /// Constructs a plane directly from its normal and constant.
    ///
    /// @param n Plane normal.
    /// @param d Plane constant.
    inline_ Plane(const Point& n, float d)
    {
        this->n = n;
        this->d = d;
    }

    /// Constructs a copy of another plane.
    inline_ Plane(const Plane& plane) : n(plane.n), d(plane.d)
    {
    }

    /// Destroys the plane.
    inline_ ~Plane()
    {
    }

    /// Sets all plane coefficients to zero.
    ///
    /// @return Reference to this plane.
    inline_ Plane& Zero()
    {
        n.Zero();
        d = 0.0f;
        return *this;
    }

    /// Sets the plane from its coefficients.
    ///
    /// @param nx X component of the normal.
    /// @param ny Y component of the normal.
    /// @param nz Z component of the normal.
    /// @param d Plane constant.
    /// @return Reference to this plane.
    inline_ Plane& Set(float nx, float ny, float nz, float d)
    {
        n.Set(nx, ny, nz);
        this->d = d;
        return *this;
    }

    /// Sets the plane from a point and a normal.
    ///
    /// @param p Point on the plane.
    /// @param n Plane normal.
    /// @return Reference to this plane.
    inline_ Plane& Set(const Point& p, const Point& n)
    {
        this->n = n;
        d = - p | n;
        return *this;
    }

    /// Sets the plane from three non-collinear points.
    ///
    /// @param p0 First point.
    /// @param p1 Second point.
    /// @param p2 Third point.
    /// @return Reference to this plane.
    Plane& Set(const Point& p0, const Point& p1, const Point& p2);

    /// Computes the signed distance from a point to the plane.
    ///
    /// Positive values indicate the point lies in the direction of the normal,
    /// negative values indicate the opposite side, and zero indicates the point
    /// lies on the plane.
    ///
    /// @param p Point to test.
    /// @return Signed distance from the plane.
    inline_ float Distance(const Point& p) const { return (p | n) + d; }

    /// Tests whether a point lies on the plane.
    ///
    /// @param p Point to test.
    /// @return true if the point is within PLANE_EPSILON of the plane.
    inline_ bool Belongs(const Point& p) const { return _abs(Distance(p)) < PLANE_EPSILON; }

    /// Normalizes the plane equation.
    ///
    /// Scales the normal to unit length and adjusts the plane constant
    /// accordingly.
    inline_ void Normalize()
    {
        float Denom = 1.0f / n.Magnitude();
        n.x *= Denom;
        n.y *= Denom;
        n.z *= Denom;
        d *= Denom;
    }

public:
    Point n; ///< Plane normal.
    float d; ///< TPlane constant in the equation n · p + d = 0.

    /// Converts the plane to its normal vector.
    inline_ operator Point() const { return n; }

#if 0
    inline_ operator HPoint() const { return HPoint(n, d); }

    // Arithmetic operators
    inline_ Plane operator*(const Matrix4x4& m) const {
		// Old code from Irion. Kept for reference.
		Plane Ret(*this);
		return Ret *= m;
	}

    inline_ Plane& operator*=(const Matrix4x4& m) {
		// Old code from Irion. Kept for reference.
		Point n2 = HPoint(n, 0.0f) * m;
		d = -((Point) (HPoint( -d*n, 1.0f ) * m) | n2);
		n = n2;
		return *this;
	}
#endif
};

/// Transforms a plane by a 4×4 transformation matrix.
///
/// This is equivalent to multiplying the plane by the matrix, but avoids
/// constructing temporary objects.
///
/// @param transformed Receives the transformed plane.
/// @param plane Source plane.
/// @param transform Transformation matrix.
inline_ void TransformPlane(Plane& transformed, const Plane& plane, const Matrix4x4& transform)
{
    // Extract the rotation component.
    Matrix3x3 Rot = transform;

    // Rotate the normal.
    transformed.n = plane.n * Rot;

    // Compute the transformed plane constant.
    Point Trans;
    transform.GetTrans(Trans);
    transformed.d = (plane.d * transformed.n - Trans) | transformed.n;
}

/// Transforms a plane in place.
///
/// @param plane Plane to transform.
/// @param transform Transformation matrix.
inline_ void TransformPlane(Plane& plane, const Matrix4x4& transform)
{
    // Extract the rotation component.
    Matrix3x3 Rot = transform;

    // Rotate the normal
    plane.n *= Rot;

    // Compute the transformed plane constant.
    Point Trans;
    transform.GetTrans(Trans);
    plane.d = (plane.d * plane.n - Trans) | plane.n;
}
