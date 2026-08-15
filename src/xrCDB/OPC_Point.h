/// Provides a three-dimensional point/vector class and related utilities.
///
/// This file defines the `Point` class along with supporting types, constants,
/// and helper macros used for common 3D vector mathematics, including
/// arithmetic operations, interpolation, transformations, projections,
/// normalization, and geometric queries.
///
/// @file IcePoint.h
/// @author Pierre Terdiman
/// @date April 4, 2000

#pragma once

/// Identifies individual vector components.
enum PointComponent
{
    _X = 0, ///< X component.
    _Y = 1, ///< Y component.
    _Z = 2, ///< Z component.
    _W = 3, ///< W component.
    _FORCE_DWORD = 0x7fffffff, ///< Forces the enumeration to be stored as a 32-bit value.
};

class HPoint;
class Plane;
class Matrix3x3;
class Matrix4x4;

/// Computes the 2D cross product (signed area) of two vectors.
#define CROSS2D(a, b)    (a.x*b.y - b.x*a.y)

/// Squared magnitude threshold used for near-zero comparisons.
#define EPSILON2 1.0e-20f;

class ICEMATHS_API icePoint;
#define Point icePoint

/// Represents a three-dimensional point or vector.
///
/// `Point` provides a wide range of operations for 3D mathematics, including
/// arithmetic, interpolation, normalization, geometric queries, coordinate
/// transformations, and projection. Most operations modify the current object
/// and return a reference to it, allowing method chaining.
class ICEMATHS_API icePoint
{
public:
    /// Constructs an uninitialized point.
    inline_ Point()
    {
    }

    /// Constructs a point with all components initialized to the specified value.
    ///
    /// @param val Value assigned to all components.
    inline_ Point(float val) : x(val), y(val), z(val)
    {
    }

    /// Constructs a point from individual component values.
    ///
    /// @param _x X component.
    /// @param _y Y component.
    /// @param _z Z component.
    inline_ Point(float _x, float _y, float _z) : x(_x), y(_y), z(_z)
    {
    }

    /// Constructs a point from the first three elements of an array.
    ///
    /// @param f Array containing the X, Y, and Z components.
    inline_ Point(float f[3]) : x(f[_X]), y(f[_Y]), z(f[_Z])
    {
    }

    /// Constructs a point by copying another point.
    ///
    /// @param p Point to copy.
    inline_ Point(const Point& p) : x(p.x), y(p.y), z(p.z)
    {
    }

    /// Destroys the point.
    inline_ ~Point()
    {
    }

    /// Sets all components to zero.
    ///
    /// @return Reference to this point.
    inline_ Point& Zero()
    {
        x = y = z = 0.0f;
        return *this;
    }

    /// Sets all components to the largest representable floating-point value.
    ///
    /// @return Reference to this point.
    inline_ Point& SetPlusInfinity()
    {
        x = y = z = flt_max;
        return *this;
    }

    /// Sets all components to the smallest representable floating-point value.
    ///
    /// @return Reference to this point.
    inline_ Point& SetMinusInfinity()
    {
        x = y = z = flt_min;
        return *this;
    }

    /// Sets this point to a random unit vector with non-negative components.
    ///
    /// @return Reference to this point.
    Point& PositiveUnitRandomVector();

    /// Sets this point to a random unit vector.
    ///
    /// @return Reference to this point.
    Point& UnitRandomVector();

    /// Sets the point from individual component values.
    ///
    /// @param _x X component.
    /// @param _y Y component.
    /// @param _z Z component.
    /// @return Reference to this point.
    inline_ Point& Set(float _x, float _y, float _z)
    {
        x = _x;
        y = _y;
        z = _z;
        return *this;
    }

    /// Sets the point from the first three elements of an array.
    ///
    /// @param f Array containing the X, Y, and Z components.
    /// @return Reference to this point.
    inline_ Point& Set(float f[3])
    {
        x = f[_X];
        y = f[_Y];
        z = f[_Z];
        return *this;
    }

    /// Copies the components from another point.
    ///
    /// @param src Point to copy.
    /// @return Reference to this point.
    inline_ Point& Set(const Point& src)
    {
        x = src.x;
        y = src.y;
        z = src.z;
        return *this;
    }

    /// Adds another point to this point.
    ///
    /// @param p Point to add.
    /// @return Reference to this point.
    inline_ Point& Add(const Point& p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    /// Adds individual component values to this point.
    ///
    /// @param _x Value added to the X component.
    /// @param _y Value added to the Y component.
    /// @param _z Value added to the Z component.
    /// @return Reference to this point.
    inline_ Point& Add(float _x, float _y, float _z)
    {
        x += _x;
        y += _y;
        z += _z;
        return *this;
    }

    /// Adds the first three elements of an array to this point.
    ///
    /// @param f Array containing the values to add.
    /// @return Reference to this point.
    inline_ Point& Add(float f[3])
    {
        x += f[_X];
        y += f[_Y];
        z += f[_Z];
        return *this;
    }

    /// Sets this point to the component-wise sum of two points.
    ///
    /// @param p First point.
    /// @param q Second point.
    /// @return Reference to this point.
    inline_ Point& Add(const Point& p, const Point& q)
    {
        x = p.x + q.x;
        y = p.y + q.y;
        z = p.z + q.z;
        return *this;
    }

    /// Subtracts another point from this point.
    ///
    /// @param p Point to subtract.
    /// @return Reference to this point.
    inline_ Point& Sub(const Point& p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    /// Subtracts individual component values from this point.
    ///
    /// @param _x Value subtracted from the X component.
    /// @param _y Value subtracted from the Y component.
    /// @param _z Value subtracted from the Z component.
    /// @return Reference to this point.
    inline_ Point& Sub(float _x, float _y, float _z)
    {
        x -= _x;
        y -= _y;
        z -= _z;
        return *this;
    }

    /// Subtracts the first three elements of an array from this point.
    ///
    /// @param f Array containing the values to subtract.
    /// @return Reference to this point.
    inline_ Point& Sub(float f[3])
    {
        x -= f[_X];
        y -= f[_Y];
        z -= f[_Z];
        return *this;
    }

    /// Sets this point to the component-wise difference of two points.
    ///
    /// @param p Minuend point.
    /// @param q Subtrahend point.
    /// @return Reference to this point.
    inline_ Point& Sub(const Point& p, const Point& q)
    {
        x = p.x - q.x;
        y = p.y - q.y;
        z = p.z - q.z;
        return *this;
    }

    /// Negates all components of this point.
    ///
    /// @return Reference to this point.
    inline_ Point& Neg()
    {
        x = -x;
        y = -y;
        z = -z;
        return *this;
    }

    /// Sets this point to the negation of another point.
    ///
    /// @param a Point to negate.
    /// @return Reference to this point.
    inline_ Point& Neg(const Point& a)
    {
        x = -a.x;
        y = -a.y;
        z = -a.z;
        return *this;
    }

    /// Multiplies all components by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @return Reference to this point.
    inline_ Point& Mult(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    /// Sets this point to another point multiplied by a scalar.
    ///
    /// @param a Source point.
    /// @param scalar Scalar multiplier.
    /// @return Reference to this point.
    inline_ Point& Mult(const Point& a, float scalar)
    {
        x = a.x * scalar;
        y = a.y * scalar;
        z = a.z * scalar;
        return *this;
    }

    /// Sets this point to the sum of a point and a scaled point.
    ///
    /// @param a Base point.
    /// @param b Point to scale and add.
    /// @param scalar Scalar multiplier applied to @p b.
    /// @return Reference to this point.
    inline_ Point& Mac(const Point& a, const Point& b, float scalar)
    {
        x = a.x + b.x * scalar;
        y = a.y + b.y * scalar;
        z = a.z + b.z * scalar;
        return *this;
    }

    /// Adds a scaled point to this point.
    ///
    /// @param a Point to scale and add.
    /// @param scalar Scalar multiplier applied to @p a.
    /// @return Reference to this point.
    inline_ Point& Mac(const Point& a, float scalar)
    {
        x += a.x * scalar;
        y += a.y * scalar;
        z += a.z * scalar;
        return *this;
    }

    /// Sets this point to the difference between a point and a scaled point.
    ///
    /// @param a Base point.
    /// @param b Point to scale and subtract.
    /// @param scalar Scalar multiplier applied to @p b.
    /// @return Reference to this point.
    inline_ Point& Msc(const Point& a, const Point& b, float scalar)
    {
        x = a.x - b.x * scalar;
        y = a.y - b.y * scalar;
        z = a.z - b.z * scalar;
        return *this;
    }

    /// Subtracts a scaled point from this point.
    ///
    /// @param a Point to scale and subtract.
    /// @param scalar Scalar multiplier applied to @p a.
    /// @return Reference to this point.
    inline_ Point& Msc(const Point& a, float scalar)
    {
        x -= a.x * scalar;
        y -= a.y * scalar;
        z -= a.z * scalar;
        return *this;
    }

    /// Sets this point to the sum of a point and two scaled points.
    ///
    /// @param a Base point.
    /// @param b First point to scale and add.
    /// @param scalarb Scalar multiplier applied to @p b.
    /// @param c Second point to scale and add.
    /// @param scalarc Scalar multiplier applied to @p c.
    /// @return Reference to this point.
    inline_ Point& Mac2(const Point& a, const Point& b, float scalarb, const Point& c, float scalarc)
    {
        x = a.x + b.x * scalarb + c.x * scalarc;
        y = a.y + b.y * scalarb + c.y * scalarc;
        z = a.z + b.z * scalarb + c.z * scalarc;
        return *this;
    }

    /// Sets this point to a point minus two scaled points.
    ///
    /// @param a Base point.
    /// @param b First point to scale and subtract.
    /// @param scalarb Scalar multiplier applied to @p b.
    /// @param c Second point to scale and subtract.
    /// @param scalarc Scalar multiplier applied to @p c.
    /// @return Reference to this point.
    inline_ Point& Msc2(const Point& a, const Point& b, float scalarb, const Point& c, float scalarc)
    {
        x = a.x - b.x * scalarb - c.x * scalarc;
        y = a.y - b.y * scalarb - c.y * scalarc;
        z = a.z - b.z * scalarb - c.z * scalarc;
        return *this;
    }

    /// Multiplies a point by a 3×3 matrix.
    ///
    /// @param mat Matrix to multiply by.
    /// @param a Point to transform.
    /// @return Reference to this point.
    inline_ Point& Mult(const Matrix3x3& mat, const Point& a);

    /// Sets this point to the sum of two matrix-vector products.
    ///
    /// @param mat1 First transformation matrix.
    /// @param a1 First point.
    /// @param mat2 Second transformation matrix.
    /// @param a2 Second point.
    /// @return Reference to this point.
    inline_ Point& Mult2(const Matrix3x3& mat1, const Point& a1, const Matrix3x3& mat2, const Point& a2);

    /// Adds a matrix-vector product to this point.
    ///
    /// @param mat Transformation matrix.
    /// @param a Point to transform.
    /// @return Reference to this point.
    inline_ Point& Mac(const Matrix3x3& mat, const Point& a);

    /// Multiplies a point by the transpose of a 3×3 matrix.
    ///
    /// @param mat Transformation matrix.
    /// @param a Point to transform.
    /// @return Reference to this point.
    inline_ Point& TransMult(const Matrix3x3& mat, const Point& a);

    /// Linearly interpolates between two points.
    ///
    /// @param a Start point.
    /// @param b End point.
    /// @param t Interpolation factor, typically in the range [0, 1].
    /// @return Reference to this point.
    inline_ Point& Lerp(const Point& a, const Point& b, float t)
    {
        x = a.x + t * (b.x - a.x);
        y = a.y + t * (b.y - a.y);
        z = a.z + t * (b.z - a.z);
        return *this;
    }

	/// Performs Hermite interpolation between two points.
	/// this =    p0 * (2t^2 - t^3 - t)/2
    ///            + p1 * (3t^3 - 5t^2 + 2)/2
    ///            + p2 * (4t^2 - 3t^3 + t)/2
    ///            + p3 * (t^3 - t^2)/2
    ///
    /// @param p0 Control point preceding @p p1.
    /// @param p1 Starting point.
    /// @param p2 Ending point.
    /// @param p3 Control point following @p p2.
    /// @param t Interpolation factor, typically in the range [0, 1].
    /// @return Reference to this point.
    inline_ Point& Herp(const Point& p0, const Point& p1, const Point& p2, const Point& p3, float t)
    {
        float t2 = t * t;
        float t3 = t2 * t;
        float kp0 = (2.0f * t2 - t3 - t) * 0.5f;
        float kp1 = (3.0f * t3 - 5.0f * t2 + 2.0f) * 0.5f;
        float kp2 = (4.0f * t2 - 3.0f * t3 + t) * 0.5f;
        float kp3 = (t3 - t2) * 0.5f;
        x = p0.x * kp0 + p1.x * kp1 + p2.x * kp2 + p3.x * kp3;
        y = p0.y * kp0 + p1.y * kp1 + p2.y * kp2 + p3.y * kp3;
        z = p0.z * kp0 + p1.z * kp1 + p2.z * kp2 + p3.z * kp3;
        return *this;
    }

    /// Applies a rotation followed by a translation.
    ///
    /// @param r Point to transform.
    /// @param rotpos Rotation matrix.
    /// @param linpos Translation vector.
    /// @return Reference to this point.
    inline_ Point& Transform(const Point& r, const Matrix3x3& rotpos, const Point& linpos);

    /// Applies the inverse of a rotation and translation.
    ///
    /// @param r Point to transform.
    /// @param rotpos Rotation matrix.
    /// @param linpos Translation vector.
    /// @return Reference to this point.
    inline_ Point& InvTransform(const Point& r, const Matrix3x3& rotpos, const Point& linpos);

    /// Returns the smallest component.
    ///
    /// @return Minimum of the X, Y, and Z components.
    inline_ float Min() const { return _min(x, _min(y, z)); }

    /// Returns the largest component.
    ///
    /// @return Maximum of the X, Y, and Z components.
    inline_ float Max() const { return _max(x, _max(y, z)); }

    /// Replaces each component with the smaller of the two corresponding values.
    ///
    /// @param p Point to compare against.
    /// @return Reference to this point.
    inline_ Point& Min(const Point& p)
    {
        x = _min(x, p.x);
        y = _min(y, p.y);
        z = _min(z, p.z);
        return *this;
    }

    /// Replaces each component with the larger of the two corresponding values.
    ///
    /// @param p Point to compare against.
    /// @return Reference to this point.
    inline_ Point& Max(const Point& p)
    {
        x = _max(x, p.x);
        y = _max(y, p.y);
        z = _max(z, p.z);
        return *this;
    }

    /// Clamps each component to the specified range.
    ///
    /// @param min Lower bound.
    /// @param max Upper bound.
    /// @return Reference to this point.
    inline_ Point& Clamp(float min, float max)
    {
        if (x < min) x = min;
        if (x > max) x = max;
        if (y < min) y = min;
        if (y > max) y = max;
        if (z < min) z = min;
        if (z > max) z = max;
        return *this;
    }

    /// Computes the squared length of the vector.
    ///
    /// @return Squared magnitude of the vector.
    inline_ float SquareMagnitude() const { return x * x + y * y + z * z; }

    /// Computes the length of the vector.
    ///
    /// @return Magnitude of the vector.
    inline_ float Magnitude() const { return _sqrt(x * x + y * y + z * z); }

    /// Computes the product of all three components.
    ///
    /// @return Component-wise product.
    inline_ float Volume() const { return x * y * z; }

    /// Checks whether the vector is approximately zero.
    ///
    /// @return True if the squared magnitude is smaller than the zero tolerance; otherwise false.
    bool ApproxZero() const
    {
        return SquareMagnitude() < EPSILON2;
    }

    /// Perturbs selected components by modifying their bit representation.
    ///
    /// @param coordmask Bit mask selecting which components to modify.
    /// @param tweakmask Bit mask applied to the selected floating-point values.
    void Tweak(udword coordmask, udword tweakmask)
    {
        if (coordmask & 1)
        {
            udword Dummy = IR(x);
            Dummy ^= tweakmask;
            x = FR(Dummy);
        }
        if (coordmask & 2)
        {
            udword Dummy = IR(y);
            Dummy ^= tweakmask;
            y = FR(Dummy);
        }
        if (coordmask & 4)
        {
            udword Dummy = IR(z);
            Dummy ^= tweakmask;
            z = FR(Dummy);
        }
    }

	/// Bit mask applied when increasing or decreasing floating-point values during tweaking.
	#define TWEAKMASK        0x3fffff

	/// Inverse of ::TWEAKMASK, preserving the exponent and sign bits.
	#define TWEAKNOTMASK    ~TWEAKMASK

    /// Expands the point slightly by increasing the magnitude of non-negative components.
    inline_ void TweakBigger()
    {
        udword Dummy = (IR(x) & TWEAKNOTMASK);
        if (!IS_NEGATIVE_FLOAT(x)) Dummy += TWEAKMASK + 1;
        x = FR(Dummy);
        Dummy = (IR(y) & TWEAKNOTMASK);
        if (!IS_NEGATIVE_FLOAT(y)) Dummy += TWEAKMASK + 1;
        y = FR(Dummy);
        Dummy = (IR(z) & TWEAKNOTMASK);
        if (!IS_NEGATIVE_FLOAT(z)) Dummy += TWEAKMASK + 1;
        z = FR(Dummy);
    }

    /// Shrinks the point slightly by decreasing the magnitude of negative components.
    inline_ void TweakSmaller()
    {
        udword Dummy = (IR(x) & TWEAKNOTMASK);
        if (IS_NEGATIVE_FLOAT(x)) Dummy += TWEAKMASK + 1;
        x = FR(Dummy);
        Dummy = (IR(y) & TWEAKNOTMASK);
        if (IS_NEGATIVE_FLOAT(y)) Dummy += TWEAKMASK + 1;
        y = FR(Dummy);
        Dummy = (IR(z) & TWEAKNOTMASK);
        if (IS_NEGATIVE_FLOAT(z)) Dummy += TWEAKMASK + 1;
        z = FR(Dummy);
    }

    /// Normalizes the vector to unit length.
    ///
    /// @return Reference to this point.
    inline_ Point& Normalize()
    {
        float M = x * x + y * y + z * z;
        if (M)
        {
            M = 1.0f / _sqrt(M);
            x *= M;
            y *= M;
            z *= M;
        }
        return *this;
    }

    /// Sets the vector to the specified length.
    ///
    /// @param length Desired vector length.
    /// @return Reference to this point.
    inline_ Point& SetLength(float length)
    {
        float NewLength = length / Magnitude();
        x *= NewLength;
        y *= NewLength;
        z *= NewLength;
        return *this;
    }

    /// Computes the distance to another point.
    ///
    /// @param b Point to measure the distance to.
    /// @return Euclidean distance.
    inline_ float Distance(const Point& b) const
    {
        return _sqrt((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
    }

    /// Computes the squared distance to another point.
    ///
    /// @param b Point to measure the distance to.
    /// @return Squared Euclidean distance.
    inline_ float SquareDistance(const Point& b) const
    {
        return ((x - b.x) * (x - b.x) + (y - b.y) * (y - b.y) + (z - b.z) * (z - b.z));
    }

    /// Computes the dot product with another point.
    ///
    /// @param p Point to compute the dot product with.
    /// @return Dot product.
    inline_ float Dot(const Point& p) const { return p.x * x + p.y * y + p.z * z; }

    /// Sets this point to the cross product of two points.
    ///
    /// @param a First point.
    /// @param b Second point.
    /// @return Reference to this point.
    inline_ Point& Cross(const Point& a, const Point& b)
    {
        x = a.y * b.z - a.z * b.y;
        y = a.z * b.x - a.x * b.z;
        z = a.x * b.y - a.y * b.x;
        return *this;
    }

	/// Computes a three-bit sign code for the vector components.
    ///
    /// @return Bit mask encoding the signs of the X, Y, and Z components.
    inline_ udword VectorCode() const
    {
        return (IR(x) >> 31) | ((IR(y) & SIGN_BITMASK) >> 30) | ((IR(z) & SIGN_BITMASK) >> 29);
    }

    /// Returns the index of the largest component.
    ///
    /// @return Largest component axis.
    inline_ PointComponent LargestAxis() const
    {
        const float* Vals = &x;
        PointComponent m = _X;
        if (Vals[_Y] > Vals[m]) m = _Y;
        if (Vals[_Z] > Vals[m]) m = _Z;
        return m;
    }

    /// Returns the index of the component with the greatest absolute value.
    ///
    /// @return Closest axis.
    inline_ PointComponent ClosestAxis() const
    {
        const float* Vals = &x;
        PointComponent m = _X;
        if (AIR(Vals[_Y]) > AIR(Vals[m])) m = _Y;
        if (AIR(Vals[_Z]) > AIR(Vals[m])) m = _Z;
        return m;
    }

    /// Returns the index of the smallest component.
    ///
    /// @return Smallest component axis.
    inline_ PointComponent SmallestAxis() const
    {
        const float* Vals = &x;
        PointComponent m = _X;
        if (Vals[_Y] < Vals[m]) m = _Y;
        if (Vals[_Z] < Vals[m]) m = _Z;
        return m;
    }

    /// Computes the refraction of a vector through a surface.
    ///
    /// @param eye Incident vector.
    /// @param n Surface normal.
    /// @param refractindex Index of refraction.
    /// @param refracted Receives the refracted vector.
    /// @return Reference to @p refracted.
    Point& Refract(const Point& eye, const Point& n, float refractindex, Point& refracted);

    /// Projects this point onto a plane.
    ///
    /// @param p Plane to project onto.
    /// @return Reference to this point.
    Point& ProjectToPlane(const Plane& p);

    /// Projects this point into screen space.
    ///
    /// @param halfrenderwidth Half of the render target width.
    /// @param halfrenderheight Half of the render target height.
    /// @param mat Projection matrix.
    /// @param projected Receives the projected homogeneous point.
    void ProjectToScreen(float halfrenderwidth, float halfrenderheight, const Matrix4x4& mat, HPoint& projected) const;

    /// Unfolds this point onto a plane around the specified edge.
    ///
    /// @param p Plane used for unfolding.
    /// @param a First edge endpoint.
    /// @param b Second edge endpoint.
    /// @return Reference to this point.
    Point& Unfold(Plane& p, Point& a, Point& b);

    /// Computes a hash value for this point.
    ///
    /// @return Hash value.
    inline_ udword GetHashValue() const
    {
        const udword* h = (const udword*)(this);
        udword f = (h[0] + h[1] * 11 - (h[2] * 17)) & 0x7fffffff; // avoid problems with +-0
        return (f >> 22) ^ (f >> 12) ^ (f);
    }

    /// Returns the negation of this point.
    ///
    /// @return Negated point.
    inline_ Point operator-() const { return Point(-x, -y, -z); }

    /// Adds two points.
    ///
    /// @param p Point to add.
    /// @return Sum of the two points.
    inline_ Point operator+(const Point& p) const { return Point(x + p.x, y + p.y, z + p.z); }
	
    /// Subtracts one point from another.
    ///
    /// @param p Point to subtract.
    /// @return Difference of the two points.
    inline_ Point operator-(const Point& p) const { return Point(x - p.x, y - p.y, z - p.z); }

    /// Multiplies two points component-wise.
    ///
    /// @param p Point to multiply by.
    /// @return Component-wise product.
    inline_ Point operator*(const Point& p) const { return Point(x * p.x, y * p.y, z * p.z); }

    /// Multiplies this point by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @return Scaled point.
    inline_ Point operator*(float s) const { return Point(x * s, y * s, z * s); }

    /// Multiplies a point by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @param p Point to scale.
    /// @return Scaled point.
    inline_ friend Point operator*(float s, const Point& p) { return Point(s * p.x, s * p.y, s * p.z); }

    /// Divides this point component-wise by another point.
    ///
    /// @param p Divisor point.
    /// @return Component-wise quotient.
    inline_ Point operator/(const Point& p) const { return Point(x / p.x, y / p.y, z / p.z); }

    /// Divides this point by a scalar.
    ///
    /// @param s Scalar divisor.
    /// @return Scaled point.
    inline_ Point operator/(float s) const
    {
        s = 1.0f / s;
        return Point(x * s, y * s, z * s);
    }

    /// Divides a scalar by each component of a point.
    ///
    /// @param s Scalar dividend.
    /// @param p Divisor point.
    /// @return Component-wise quotient.
    inline_ friend Point operator/(float s, const Point& p) { return Point(s / p.x, s / p.y, s / p.z); }

    /// Computes the dot product of two points.
    ///
    /// @param p Point to compute the dot product with.
    /// @return Dot product.
    inline_ float operator|(const Point& p) const { return x * p.x + y * p.y + z * p.z; }

    /// Computes the cross product of two points.
    ///
    /// @param p Point to compute the cross product with.
    /// @return Cross product.
    ICF Point operator^(const Point& p) const
    {
        return Point(
            y * p.z - z * p.y,
            z * p.x - x * p.z,
            x * p.y - y * p.x);
    }

    /// Adds a point to this point.
    ///
    /// @param p Point to add.
    /// @return Reference to this point.
    inline_ Point& operator+=(const Point& p)
    {
        x += p.x;
        y += p.y;
        z += p.z;
        return *this;
    }

    /// Adds a scalar to each component.
    ///
    /// @param s Scalar value to add.
    /// @return Reference to this point.
    inline_ Point& operator+=(float s)
    {
        x += s;
        y += s;
        z += s;
        return *this;
    }

    /// Subtracts a point from this point.
    ///
    /// @param p Point to subtract.
    /// @return Reference to this point.
    inline_ Point& operator-=(const Point& p)
    {
        x -= p.x;
        y -= p.y;
        z -= p.z;
        return *this;
    }

    /// Subtracts a scalar from each component.
    ///
    /// @param s Scalar value to subtract.
    /// @return Reference to this point.
    inline_ Point& operator-=(float s)
    {
        x -= s;
        y -= s;
        z -= s;
        return *this;
    }

    /// Multiplies this point component-wise by another point.
    ///
    /// @param p Point to multiply by.
    /// @return Reference to this point.
    inline_ Point& operator*=(const Point& p)
    {
        x *= p.x;
        y *= p.y;
        z *= p.z;
        return *this;
    }

    /// Multiplies this point by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @return Reference to this point.
    inline_ Point& operator*=(float s)
    {
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    /// Divides this point component-wise by another point.
    ///
    /// @param p Divisor point.
    /// @return Reference to this point.
    inline_ Point& operator/=(const Point& p)
    {
        x /= p.x;
        y /= p.y;
        z /= p.z;
        return *this;
    }

    /// Divides this point by a scalar.
    ///
    /// @param s Scalar divisor.
    /// @return Reference to this point.
    inline_ Point& operator/=(float s)
    {
        s = 1.0f / s;
        x *= s;
        y *= s;
        z *= s;
        return *this;
    }

    /// Compares two points for exact equality.
    ///
    /// @param p Point to compare against.
    /// @return True if all components are bitwise equal; otherwise false.
    inline_ bool operator==(const Point& p) const
    {
        return ((IR(x) == IR(p.x)) && (IR(y) == IR(p.y)) && (IR(z) == IR(p.z)));
    }

    /// Compares two points for inequality.
    ///
    /// @param p Point to compare against.
    /// @return True if any component differs; otherwise false.
    inline_ bool operator!=(const Point& p) const
    {
        return ((IR(x) != IR(p.x)) || (IR(y) != IR(p.y)) || (IR(z) != IR(p.z)));
    }

    /// Transforms this point by a 3×3 matrix.
    ///
    /// @param mat Transformation matrix.
    /// @return Transformed point.
    inline_ Point operator*(const Matrix3x3& mat) const
    {
        class ShadowMatrix3x3
        {
        public:
            float m[3][3];
        }; // To allow inlining
        const ShadowMatrix3x3* Mat = (const ShadowMatrix3x3*)&mat;

        return Point(
            x * Mat->m[0][0] + y * Mat->m[1][0] + z * Mat->m[2][0],
            x * Mat->m[0][1] + y * Mat->m[1][1] + z * Mat->m[2][1],
            x * Mat->m[0][2] + y * Mat->m[1][2] + z * Mat->m[2][2]);
    }

    /// Transforms this point by a 4×4 matrix.
    ///
    /// @param mat Transformation matrix.
    /// @return Transformed point.
    inline_ Point operator*(const Matrix4x4& mat) const
    {
        class ShadowMatrix4x4
        {
        public:
            float m[4][4];
        }; // To allow inlining
        const ShadowMatrix4x4* Mat = (const ShadowMatrix4x4*)&mat;

        return Point(
            x * Mat->m[0][0] + y * Mat->m[1][0] + z * Mat->m[2][0] + Mat->m[3][0],
            x * Mat->m[0][1] + y * Mat->m[1][1] + z * Mat->m[2][1] + Mat->m[3][1],
            x * Mat->m[0][2] + y * Mat->m[1][2] + z * Mat->m[2][2] + Mat->m[3][2]);
    }

    /// Transforms this point in place by a 3×3 matrix.
    ///
    /// @param mat Transformation matrix.
    /// @return Reference to this point.
    inline_ Point& operator*=(const Matrix3x3& mat)
    {
        class ShadowMatrix3x3
        {
        public:
            float m[3][3];
        }; // To allow inlining
        const ShadowMatrix3x3* Mat = (const ShadowMatrix3x3*)&mat;

        float xp = x * Mat->m[0][0] + y * Mat->m[1][0] + z * Mat->m[2][0];
        float yp = x * Mat->m[0][1] + y * Mat->m[1][1] + z * Mat->m[2][1];
        float zp = x * Mat->m[0][2] + y * Mat->m[1][2] + z * Mat->m[2][2];

        x = xp;
        y = yp;
        z = zp;

        return *this;
    }

    /// Transforms this point in place by a 4×4 matrix.
    ///
    /// @param mat Transformation matrix.
    /// @return Reference to this point.
    inline_ Point& operator*=(const Matrix4x4& mat)
    {
        class ShadowMatrix4x4
        {
        public:
            float m[4][4];
        }; // To allow inlining
        const ShadowMatrix4x4* Mat = (const ShadowMatrix4x4*)&mat;

        float xp = x * Mat->m[0][0] + y * Mat->m[1][0] + z * Mat->m[2][0] + Mat->m[3][0];
        float yp = x * Mat->m[0][1] + y * Mat->m[1][1] + z * Mat->m[2][1] + Mat->m[3][1];
        float zp = x * Mat->m[0][2] + y * Mat->m[1][2] + z * Mat->m[2][2] + Mat->m[3][2];

        x = xp;
        y = yp;
        z = zp;

        return *this;
    }

    /// Converts this point to a homogeneous point.
    ///
    /// @return Homogeneous point with a zero W component.
    operator HPoint() const;

	/// Returns a pointer to the first component.
    ///
    /// @return Pointer to the X component.
    inline_ operator const float*() const { return &x; }

	/// Returns a mutable pointer to the first component.
    ///
    /// @return Pointer to the X component.
    inline_ operator float*() { return &x; }

public:
    float x; ///< X component.
	float y; ///< Y component.
	float z; ///< Z component.
};

/// Normalizes a point to unit length.
///
/// @param a Point to normalize.
FUNCTION ICEMATHS_API void Normalize1(Point& a);

/// Normalizes a point to unit length using an alternative implementation.
///
/// @param a Point to normalize.
FUNCTION ICEMATHS_API void Normalize2(Point& a);
