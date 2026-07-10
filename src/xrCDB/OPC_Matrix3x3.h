/// Contains code for 3×3 matrices.
///
/// @file IceMatrix3x3.h
/// @author Pierre Terdiman
/// @date April 4, 2000

#pragma once

class Quat;

/// Tolerance used for floating-point matrix comparisons.
#define MATRIX3X3_EPSILON (1.0e-7f)

/// Convenience macro used by deprecated arithmetic operators.
#define MATRIX3X3_ROW *(*this)

/// 3×3 matrix.
///
/// The matrix stores a linear transformation in row-major order. It is
/// primarily used to represent rotations, scaling, and other linear
/// transformations in three-dimensional space, and provides common matrix
/// operations such as construction, inversion, transposition, arithmetic, and
/// vector transformation.
class ICEMATHS_API Matrix3x3
{
public:
    /// Creates an uninitialized matrix.
    inline_ Matrix3x3()
    {
    }

    /// Creates a matrix from individual row-major elements.
    inline_ Matrix3x3(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
    }

    /// Copies the contents of another matrix.
    ///
    /// @param mat Matrix to copy.
    inline_ Matrix3x3(const Matrix3x3& mat)
    {
        CopyMemory(m, &mat.m, 9*sizeof(float));
    }

    /// Destroys the matrix.
    inline_ ~Matrix3x3()
    {
    }

    /// Replaces all matrix elements.
    ///
    /// Elements are specified in row-major order.
    ///
    /// @param m00 Row 0, column 0.
    /// @param m01 Row 0, column 1.
    /// @param m02 Row 0, column 2.
    /// @param m10 Row 1, column 0.
    /// @param m11 Row 1, column 1.
    /// @param m12 Row 1, column 2.
    /// @param m20 Row 2, column 0.
    /// @param m21 Row 2, column 1.
    /// @param m22 Row 2, column 2.
    inline_ void Set(float m00, float m01, float m02, float m10, float m11, float m12, float m20, float m21, float m22)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
    }

    /// Sets the diagonal elements from a vector.
    ///
    /// Off-diagonal elements are left unchanged.
    ///
    /// @param p Scale values for the X, Y, and Z axes.
    inline_ void SetScale(const Point& p)
    {
        m[0][0] = p.x;
        m[1][1] = p.y;
        m[2][2] = p.z;
    }

    /// Sets the diagonal elements from individual scale values.
    ///
    /// Off-diagonal elements are left unchanged.
    ///
    /// @param sx Scale along the X axis.
    /// @param sy Scale along the Y axis.
    /// @param sz Scale along the Z axis.
    inline_ void SetScale(float sx, float sy, float sz)
    {
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = sz;
    }

    /// Scales each matrix row by the corresponding vector component.
    ///
    /// @param p Scale factors for the X, Y, and Z rows.
    inline_ void Scale(const Point& p)
    {
        m[0][0] *= p.x;
        m[0][1] *= p.x;
        m[0][2] *= p.x;
        m[1][0] *= p.y;
        m[1][1] *= p.y;
        m[1][2] *= p.y;
        m[2][0] *= p.z;
        m[2][1] *= p.z;
        m[2][2] *= p.z;
    }

    /// Scales each matrix row by the corresponding scalar.
    ///
    /// @param sx Scale factor for the first row.
    /// @param sy Scale factor for the second row.
    /// @param sz Scale factor for the third row.
    inline_ void Scale(float sx, float sy, float sz)
    {
        m[0][0] *= sx;
        m[0][1] *= sx;
        m[0][2] *= sx;
        m[1][0] *= sy;
        m[1][1] *= sy;
        m[1][2] *= sy;
        m[2][0] *= sz;
        m[2][1] *= sz;
        m[2][2] *= sz;
    }

    /// Copies the contents of another matrix.
    ///
    /// @param source Matrix to copy.
    inline_ void Copy(const Matrix3x3& source)
    {
        CopyMemory(m, source.m, 9*sizeof(float));
    }

    /// Retrieves a matrix row.
    ///
    /// @param r Zero-based row index.
    /// @param p Receives the selected row.
    inline_ void GetRow(const udword r, Point& p) const
    {
        p.x = m[r][0];
        p.y = m[r][1];
        p.z = m[r][2];
    }

    /// Replaces a matrix row.
    ///
    /// @param r Zero-based row index.
    /// @param p Row values.
    inline_ void SetRow(const udword r, const Point& p)
    {
        m[r][0] = p.x;
        m[r][1] = p.y;
        m[r][2] = p.z;
    }

    /// Retrieves a matrix column.
    ///
    /// @param c Zero-based column index.
    /// @param p Receives the selected column.
    inline_ void GetCol(const udword c, Point& p) const
    {
        p.x = m[0][c];
        p.y = m[1][c];
        p.z = m[2][c];
    }

    /// Replaces a matrix column.
    ///
    /// @param c Zero-based column index.
    /// @param p Column values.
    inline_ void SetCol(const udword c, const Point& p)
    {
        m[0][c] = p.x;
        m[1][c] = p.y;
        m[2][c] = p.z;
    }

    /// Returns the sum of the diagonal elements.
    ///
    /// @return Matrix trace.
    inline_ float Trace() const { return m[0][0] + m[1][1] + m[2][2]; }

    /// Sets every matrix element to zero.
    inline_ void Zero()
    {
        ZeroMemory(&m, sizeof(m));
    }

    /// Sets the matrix to the identity matrix.
    inline_ void Identity()
    {
        Zero();
        m[0][0] = m[1][1] = m[2][2] = 1.0f;
    }

    /// Checks whether the matrix is exactly the identity matrix.
    ///
    /// The comparison is performed using the raw IEEE-754 bit pattern of each
    /// element rather than an epsilon.
    ///
    /// @return `true` if the matrix is the identity matrix, otherwise `false`.
    inline_ bool IsIdentity() const
    {
        if (IR(m[0][0]) != IEEE_1_0) return false;
        if (IR(m[0][1]) != 0) return false;
        if (IR(m[0][2]) != 0) return false;

        if (IR(m[1][0]) != 0) return false;
        if (IR(m[1][1]) != IEEE_1_0) return false;
        if (IR(m[1][2]) != 0) return false;

        if (IR(m[2][0]) != 0) return false;
        if (IR(m[2][1]) != 0) return false;
        if (IR(m[2][2]) != IEEE_1_0) return false;

        return true;
    }

	/// Builds a skew-symmetric matrix from a vector.
	///    [  0.0  -a.z   a.y ]
    ///    [  a.z   0.0  -a.x ]
    ///    [ -a.y   a.x   0.0 ]
    ///
    /// The resulting matrix represents the cross-product operation, such that
    /// `Skew(a) * b` is equivalent to `a × b`.
    ///
    /// @param a Source vector.
    inline_ void SkewSymmetric(const Point& a)
    {
        m[0][0] = 0.0f;
        m[0][1] = -a.z;
        m[0][2] = a.y;

        m[1][0] = a.z;
        m[1][1] = 0.0f;
        m[1][2] = -a.x;

        m[2][0] = -a.y;
        m[2][1] = a.x;
        m[2][2] = 0.0f;
    }

    /// Negates every matrix element.
    inline_ void Neg()
    {
        m[0][0] = -m[0][0];
        m[0][1] = -m[0][1];
        m[0][2] = -m[0][2];
        m[1][0] = -m[1][0];
        m[1][1] = -m[1][1];
        m[1][2] = -m[1][2];
        m[2][0] = -m[2][0];
        m[2][1] = -m[2][1];
        m[2][2] = -m[2][2];
    }

    /// Stores the negation of another matrix.
    ///
    /// @param mat Matrix to negate.
    inline_ void Neg(const Matrix3x3& mat)
    {
        m[0][0] = -mat.m[0][0];
        m[0][1] = -mat.m[0][1];
        m[0][2] = -mat.m[0][2];
        m[1][0] = -mat.m[1][0];
        m[1][1] = -mat.m[1][1];
        m[1][2] = -mat.m[1][2];
        m[2][0] = -mat.m[2][0];
        m[2][1] = -mat.m[2][1];
        m[2][2] = -mat.m[2][2];
    }

    /// Adds another matrix element-wise.
    ///
    /// @param mat Matrix to add.
    inline_ void Add(const Matrix3x3& mat)
    {
        m[0][0] += mat.m[0][0];
        m[0][1] += mat.m[0][1];
        m[0][2] += mat.m[0][2];
        m[1][0] += mat.m[1][0];
        m[1][1] += mat.m[1][1];
        m[1][2] += mat.m[1][2];
        m[2][0] += mat.m[2][0];
        m[2][1] += mat.m[2][1];
        m[2][2] += mat.m[2][2];
    }

    /// Subtracts another matrix element-wise.
    ///
    /// @param mat Matrix to subtract.
    inline_ void Sub(const Matrix3x3& mat)
    {
        m[0][0] -= mat.m[0][0];
        m[0][1] -= mat.m[0][1];
        m[0][2] -= mat.m[0][2];
        m[1][0] -= mat.m[1][0];
        m[1][1] -= mat.m[1][1];
        m[1][2] -= mat.m[1][2];
        m[2][0] -= mat.m[2][0];
        m[2][1] -= mat.m[2][1];
        m[2][2] -= mat.m[2][2];
    }

    /// Computes `a + b * s`.
    ///
    /// @param a Base matrix.
    /// @param b Matrix multiplied by the scalar.
    /// @param s Scalar multiplier.
    inline_ void Mac(const Matrix3x3& a, const Matrix3x3& b, float s)
    {
        m[0][0] = a.m[0][0] + b.m[0][0] * s;
        m[0][1] = a.m[0][1] + b.m[0][1] * s;
        m[0][2] = a.m[0][2] + b.m[0][2] * s;

        m[1][0] = a.m[1][0] + b.m[1][0] * s;
        m[1][1] = a.m[1][1] + b.m[1][1] * s;
        m[1][2] = a.m[1][2] + b.m[1][2] * s;

        m[2][0] = a.m[2][0] + b.m[2][0] * s;
        m[2][1] = a.m[2][1] + b.m[2][1] * s;
        m[2][2] = a.m[2][2] + b.m[2][2] * s;
    }

    /// Accumulates `a * s` into this matrix.
    ///
    /// @param a Matrix multiplied by the scalar.
    /// @param s Scalar multiplier.
    inline_ void Mac(const Matrix3x3& a, float s)
    {
        m[0][0] += a.m[0][0] * s;
        m[0][1] += a.m[0][1] * s;
        m[0][2] += a.m[0][2] * s;
        m[1][0] += a.m[1][0] * s;
        m[1][1] += a.m[1][1] * s;
        m[1][2] += a.m[1][2] * s;
        m[2][0] += a.m[2][0] * s;
        m[2][1] += a.m[2][1] * s;
        m[2][2] += a.m[2][2] * s;
    }

    /// Stores a matrix multiplied by a scalar.
    ///
    /// Computes `this = a * s`.
    ///
    /// @param a Source matrix.
    /// @param s Scalar multiplier.
    inline_ void Mult(const Matrix3x3& a, float s)
    {
        m[0][0] = a.m[0][0] * s;
        m[0][1] = a.m[0][1] * s;
        m[0][2] = a.m[0][2] * s;
        m[1][0] = a.m[1][0] * s;
        m[1][1] = a.m[1][1] * s;
        m[1][2] = a.m[1][2] * s;
        m[2][0] = a.m[2][0] * s;
        m[2][1] = a.m[2][1] * s;
        m[2][2] = a.m[2][2] * s;
    }

	/// Stores the element-wise sum of two matrices.
    ///
    /// Computes `this = a + b`.
    ///
    /// @param a First matrix.
    /// @param b Second matrix.
    inline_ void Add(const Matrix3x3& a, const Matrix3x3& b)
    {
        m[0][0] = a.m[0][0] + b.m[0][0];
        m[0][1] = a.m[0][1] + b.m[0][1];
        m[0][2] = a.m[0][2] + b.m[0][2];
        m[1][0] = a.m[1][0] + b.m[1][0];
        m[1][1] = a.m[1][1] + b.m[1][1];
        m[1][2] = a.m[1][2] + b.m[1][2];
        m[2][0] = a.m[2][0] + b.m[2][0];
        m[2][1] = a.m[2][1] + b.m[2][1];
        m[2][2] = a.m[2][2] + b.m[2][2];
    }

	/// Stores the element-wise difference of two matrices.
    ///
    /// Computes `this = a - b`.
    ///
    /// @param a Matrix to subtract from.
    /// @param b Matrix to subtract.
    inline_ void Sub(const Matrix3x3& a, const Matrix3x3& b)
    {
        m[0][0] = a.m[0][0] - b.m[0][0];
        m[0][1] = a.m[0][1] - b.m[0][1];
        m[0][2] = a.m[0][2] - b.m[0][2];
        m[1][0] = a.m[1][0] - b.m[1][0];
        m[1][1] = a.m[1][1] - b.m[1][1];
        m[1][2] = a.m[1][2] - b.m[1][2];
        m[2][0] = a.m[2][0] - b.m[2][0];
        m[2][1] = a.m[2][1] - b.m[2][1];
        m[2][2] = a.m[2][2] - b.m[2][2];
    }

    /// Stores the product of two matrices.
    ///
    /// Computes `this = a * b`.
    ///
    /// @param a Left-hand matrix.
    /// @param b Right-hand matrix.
    inline_ void Mult(const Matrix3x3& a, const Matrix3x3& b)
    {
        m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[1][0] + a.m[0][2] * b.m[2][0];
        m[0][1] = a.m[0][0] * b.m[0][1] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[2][1];
        m[0][2] = a.m[0][0] * b.m[0][2] + a.m[0][1] * b.m[1][2] + a.m[0][2] * b.m[2][2];
        m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[1][2] * b.m[2][0];
        m[1][1] = a.m[1][0] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[2][1];
        m[1][2] = a.m[1][0] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[1][2] * b.m[2][2];
        m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[1][0] + a.m[2][2] * b.m[2][0];
        m[2][1] = a.m[2][0] * b.m[0][1] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[2][1];
        m[2][2] = a.m[2][0] * b.m[0][2] + a.m[2][1] * b.m[1][2] + a.m[2][2] * b.m[2][2];
    }

    /// Stores the product of the transpose of the first matrix and the second matrix.
    ///
    /// Computes `this = transpose(a) * b`.
    ///
    /// @param a Matrix to transpose.
    /// @param b Right-hand matrix.
    inline_ void MultAtB(const Matrix3x3& a, const Matrix3x3& b)
    {
        m[0][0] = a.m[0][0] * b.m[0][0] + a.m[1][0] * b.m[1][0] + a.m[2][0] * b.m[2][0];
        m[0][1] = a.m[0][0] * b.m[0][1] + a.m[1][0] * b.m[1][1] + a.m[2][0] * b.m[2][1];
        m[0][2] = a.m[0][0] * b.m[0][2] + a.m[1][0] * b.m[1][2] + a.m[2][0] * b.m[2][2];
        m[1][0] = a.m[0][1] * b.m[0][0] + a.m[1][1] * b.m[1][0] + a.m[2][1] * b.m[2][0];
        m[1][1] = a.m[0][1] * b.m[0][1] + a.m[1][1] * b.m[1][1] + a.m[2][1] * b.m[2][1];
        m[1][2] = a.m[0][1] * b.m[0][2] + a.m[1][1] * b.m[1][2] + a.m[2][1] * b.m[2][2];
        m[2][0] = a.m[0][2] * b.m[0][0] + a.m[1][2] * b.m[1][0] + a.m[2][2] * b.m[2][0];
        m[2][1] = a.m[0][2] * b.m[0][1] + a.m[1][2] * b.m[1][1] + a.m[2][2] * b.m[2][1];
        m[2][2] = a.m[0][2] * b.m[0][2] + a.m[1][2] * b.m[1][2] + a.m[2][2] * b.m[2][2];
    }

    /// Stores the product of the first matrix and the transpose of the second matrix.
    ///
    /// Computes `this = a * transpose(b)`.
    ///
    /// @param a Left-hand matrix.
    /// @param b Matrix to transpose.
    inline_ void MultABt(const Matrix3x3& a, const Matrix3x3& b)
    {
        m[0][0] = a.m[0][0] * b.m[0][0] + a.m[0][1] * b.m[0][1] + a.m[0][2] * b.m[0][2];
        m[0][1] = a.m[0][0] * b.m[1][0] + a.m[0][1] * b.m[1][1] + a.m[0][2] * b.m[1][2];
        m[0][2] = a.m[0][0] * b.m[2][0] + a.m[0][1] * b.m[2][1] + a.m[0][2] * b.m[2][2];
        m[1][0] = a.m[1][0] * b.m[0][0] + a.m[1][1] * b.m[0][1] + a.m[1][2] * b.m[0][2];
        m[1][1] = a.m[1][0] * b.m[1][0] + a.m[1][1] * b.m[1][1] + a.m[1][2] * b.m[1][2];
        m[1][2] = a.m[1][0] * b.m[2][0] + a.m[1][1] * b.m[2][1] + a.m[1][2] * b.m[2][2];
        m[2][0] = a.m[2][0] * b.m[0][0] + a.m[2][1] * b.m[0][1] + a.m[2][2] * b.m[0][2];
        m[2][1] = a.m[2][0] * b.m[1][0] + a.m[2][1] * b.m[1][1] + a.m[2][2] * b.m[1][2];
        m[2][2] = a.m[2][0] * b.m[2][0] + a.m[2][1] * b.m[2][1] + a.m[2][2] * b.m[2][2];
    }

    /// Creates a rotation matrix that rotates one vector onto another.
    ///
    /// @param from Source direction.
    /// @param to Destination direction.
    /// @return Reference to this matrix.
    Matrix3x3& FromTo(const Point& from, const Point& to);

    /// Sets this matrix to a rotation about the X axis.
    ///
    /// @param angle Rotation angle in radians.
    void RotX(float angle)
    {
        float Cos = _cos(angle), Sin = _sin(angle);
        Identity();
        m[1][1] = m[2][2] = Cos;
        m[2][1] = -Sin;
        m[1][2] = Sin;
    }

    /// Sets this matrix to a rotation about the Y axis.
    ///
    /// @param angle Rotation angle in radians.
    void RotY(float angle)
    {
        float Cos = _cos(angle), Sin = _sin(angle);
        Identity();
        m[0][0] = m[2][2] = Cos;
        m[2][0] = Sin;
        m[0][2] = -Sin;
    }

    /// Sets this matrix to a rotation about the Z axis.
    ///
    /// @param angle Rotation angle in radians.
    void RotZ(float angle)
    {
        float Cos = _cos(angle), Sin = _sin(angle);
        Identity();
        m[0][0] = m[1][1] = Cos;
        m[1][0] = -Sin;
        m[0][1] = Sin;
    }

    /// Sets this matrix to a rotation about an arbitrary axis.
    ///
    /// @param angle Rotation angle in radians.
    /// @param axis Rotation axis.
    /// @return Reference to this matrix.
    Matrix3x3& Rot(float angle, const Point& axis);

    /// Transposes this matrix in place.
    void Transpose()
    {
        IR(m[1][0]) ^= IR(m[0][1]);
        IR(m[0][1]) ^= IR(m[1][0]);
        IR(m[1][0]) ^= IR(m[0][1]);
        IR(m[2][0]) ^= IR(m[0][2]);
        IR(m[0][2]) ^= IR(m[2][0]);
        IR(m[2][0]) ^= IR(m[0][2]);
        IR(m[2][1]) ^= IR(m[1][2]);
        IR(m[1][2]) ^= IR(m[2][1]);
        IR(m[2][1]) ^= IR(m[1][2]);
    }

    /// Stores the transpose of another matrix.
    ///
    /// @param a Matrix to transpose.
    void Transpose(const Matrix3x3& a)
    {
        m[0][0] = a.m[0][0];
        m[0][1] = a.m[1][0];
        m[0][2] = a.m[2][0];
        m[1][0] = a.m[0][1];
        m[1][1] = a.m[1][1];
        m[1][2] = a.m[2][1];
        m[2][0] = a.m[0][2];
        m[2][1] = a.m[1][2];
        m[2][2] = a.m[2][2];
    }

    /// Computes the determinant of the matrix.
    ///
    /// Uses the rule of Sarrus.
    ///
    /// @return Matrix determinant.
    float Determinant() const
    {
        return (m[0][0] * m[1][1] * m[2][2] + m[0][1] * m[1][2] * m[2][0] + m[0][2] * m[1][0] * m[2][1])
            - (m[2][0] * m[1][1] * m[0][2] + m[2][1] * m[1][2] * m[0][0] + m[2][2] * m[1][0] * m[0][1]);
    }

#if 0
	/// Compute a cofactor. Used for matrix inversion.
	float CoFactor(ubyte row, ubyte column) const
	{
		static sdword gIndex[3+2] = { 0, 1, 2, 0, 1 };
		return (m[gIndex[row+1]][gIndex[column+1]]*m[gIndex[row+2]][gIndex[column+2]] - m[gIndex[row+2]][gIndex[column+1]]*m[gIndex[row+1]][gIndex[column+2]]);
	}
#endif
						
    /// Inverts this matrix.
    ///
    /// The matrix must be invertible. No check is performed for a zero
    /// determinant.
    ///
    /// @return Reference to this matrix.
    Matrix3x3& Invert()
    {
        float Det = Determinant(); // Must be !=0
        Matrix3x3 Temp;

        float OneOverDet = 1.0f / Det;

        Temp.m[0][0] = +(m[1][1] * m[2][2] - m[2][1] * m[1][2]) * OneOverDet;
        Temp.m[1][0] = -(m[1][0] * m[2][2] - m[2][0] * m[1][2]) * OneOverDet;
        Temp.m[2][0] = +(m[1][0] * m[2][1] - m[2][0] * m[1][1]) * OneOverDet;
        Temp.m[0][1] = -(m[0][1] * m[2][2] - m[2][1] * m[0][2]) * OneOverDet;
        Temp.m[1][1] = +(m[0][0] * m[2][2] - m[2][0] * m[0][2]) * OneOverDet;
        Temp.m[2][1] = -(m[0][0] * m[2][1] - m[2][0] * m[0][1]) * OneOverDet;
        Temp.m[0][2] = +(m[0][1] * m[1][2] - m[1][1] * m[0][2]) * OneOverDet;
        Temp.m[1][2] = -(m[0][0] * m[1][2] - m[1][0] * m[0][2]) * OneOverDet;
        Temp.m[2][2] = +(m[0][0] * m[1][1] - m[1][0] * m[0][1]) * OneOverDet;

        *this = Temp;

        return *this;
    }

	/// Orthonormalizes the matrix basis vectors.
    ///
    /// @return Reference to this matrix.
    Matrix3x3& Normalize()
    {
        Point RowX, RowY, RowZ;
        GetRow(0, RowX);
        //                            GetRow(1, RowY);
        GetRow(2, RowZ);
        RowZ.Normalize();
        RowY = (RowZ ^ RowX).Normalize();
        RowX = RowY ^ RowZ;
        SetRow(0, RowX);
        SetRow(1, RowY);
        SetRow(2, RowZ);
        //                            this->eZ() = this->eZ().Unit();
        //                            this->eY() = (this->eZ() * this->eX()).Unit();
        //                            this->eX() = this->eY() * this->eZ();
        return *this;
    }

    /// Computes the matrix exponential.
    ///
    /// Uses a truncated power-series expansion.
    ///
    /// @param a Matrix exponent.
    /// @return Reference to this matrix.
    Matrix3x3& Exp(const Matrix3x3& a)
    {
        const int NbTerms = 100;
        Matrix3x3 Term; // next term in series
        Matrix3x3 Temp;

        Identity();
        Term.Identity();

        for (udword div = 1; div <= NbTerms; div++)
        {
            Temp.Mult(Term, a);
            Term.Mult(Temp, 1.0f / float(div));
            // find next Term = Term * a / div
            Add(Term);
        }
        return *this;
    }

	/// Builds a rotation matrix from a quaternion.
    ///
    /// @param q Source quaternion.
    void FromQuat(const Quat& q);

	/// Builds a rotation matrix from a quaternion with a precomputed squared length.
    ///
    /// @param q Source quaternion.
    /// @param l2 Squared quaternion length.
    void FromQuatL2(const Quat& q, float l2);

    /// Returns the element-wise sum of two matrices.
    ///
    /// @param mat Matrix to add.
    /// @return Resulting matrix.
    inline_ Matrix3x3 operator+(const Matrix3x3& mat) const
    {
        return Matrix3x3(
            m[0][0] + mat.m[0][0], m[0][1] + mat.m[0][1], m[0][2] + mat.m[0][2],
            m[1][0] + mat.m[1][0], m[1][1] + mat.m[1][1], m[1][2] + mat.m[1][2],
            m[2][0] + mat.m[2][0], m[2][1] + mat.m[2][1], m[2][2] + mat.m[2][2]);
    }

    /// Returns the element-wise difference of two matrices.
    ///
    /// @param mat Matrix to subtract.
    /// @return Resulting matrix.
    inline_ Matrix3x3 operator-(const Matrix3x3& mat) const
    {
        return Matrix3x3(
            m[0][0] - mat.m[0][0], m[0][1] - mat.m[0][1], m[0][2] - mat.m[0][2],
            m[1][0] - mat.m[1][0], m[1][1] - mat.m[1][1], m[1][2] - mat.m[1][2],
            m[2][0] - mat.m[2][0], m[2][1] - mat.m[2][1], m[2][2] - mat.m[2][2]);
    }

    /// Returns the product of two matrices.
    ///
    /// @param mat Right-hand matrix.
    /// @return Product matrix.
    inline_ Matrix3x3 operator*(const Matrix3x3& mat) const
    {
        return Matrix3x3(
            m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0],
            m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1],
            m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2],

            m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0],
            m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1],
            m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2],

            m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0],
            m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1],
            m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2]);
    }

    /// Transforms a vector by this matrix.
    ///
    /// @param v Vector to transform.
    /// @return Transformed vector.
    inline_ Point operator*(const Point& v) const { return Point(MATRIX3X3_ROW[0] | v, MATRIX3X3_ROW[1] | v, MATRIX3X3_ROW[2] | v); }

    /// Returns this matrix multiplied by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @return Scaled matrix.
    inline_ Matrix3x3 operator*(float s) const
    {
        return Matrix3x3(
            m[0][0] * s, m[0][1] * s, m[0][2] * s,
            m[1][0] * s, m[1][1] * s, m[1][2] * s,
            m[2][0] * s, m[2][1] * s, m[2][2] * s);
    }

    /// Returns a matrix multiplied by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @param mat Matrix to scale.
    /// @return Scaled matrix.
    inline_ friend Matrix3x3 operator*(float s, const Matrix3x3& mat)
    {
        return Matrix3x3(
            s * mat.m[0][0], s * mat.m[0][1], s * mat.m[0][2],
            s * mat.m[1][0], s * mat.m[1][1], s * mat.m[1][2],
            s * mat.m[2][0], s * mat.m[2][1], s * mat.m[2][2]);
    }

    /// Returns this matrix divided by a scalar.
    ///
    /// If the scalar is zero, the resulting matrix contains all zeros.
    ///
    /// @param s Scalar divisor.
    /// @return Scaled matrix.
    inline_ Matrix3x3 operator/(float s) const
    {
        if (s) s = 1.0f / s;
        return Matrix3x3(
            m[0][0] * s, m[0][1] * s, m[0][2] * s,
            m[1][0] * s, m[1][1] * s, m[1][2] * s,
            m[2][0] * s, m[2][1] * s, m[2][2] * s);
    }

    /// Returns a matrix whose elements are the scalar divided by the
    /// corresponding matrix elements.
    ///
    /// @param s Scalar numerator.
    /// @param mat Matrix denominator.
    /// @return Resulting matrix.
    inline_ friend Matrix3x3 operator/(float s, const Matrix3x3& mat)
    {
        return Matrix3x3(
            s / mat.m[0][0], s / mat.m[0][1], s / mat.m[0][2],
            s / mat.m[1][0], s / mat.m[1][1], s / mat.m[1][2],
            s / mat.m[2][0], s / mat.m[2][1], s / mat.m[2][2]);
    }

    /// Adds another matrix to this matrix.
    ///
    /// @param mat Matrix to add.
    /// @return Reference to this matrix.
    inline_ Matrix3x3& operator+=(const Matrix3x3& mat)
    {
        m[0][0] += mat.m[0][0];
        m[0][1] += mat.m[0][1];
        m[0][2] += mat.m[0][2];
        m[1][0] += mat.m[1][0];
        m[1][1] += mat.m[1][1];
        m[1][2] += mat.m[1][2];
        m[2][0] += mat.m[2][0];
        m[2][1] += mat.m[2][1];
        m[2][2] += mat.m[2][2];
        return *this;
    }

    /// Subtracts another matrix from this matrix.
    ///
    /// @param mat Matrix to subtract.
    /// @return Reference to this matrix.
    inline_ Matrix3x3& operator-=(const Matrix3x3& mat)
    {
        m[0][0] -= mat.m[0][0];
        m[0][1] -= mat.m[0][1];
        m[0][2] -= mat.m[0][2];
        m[1][0] -= mat.m[1][0];
        m[1][1] -= mat.m[1][1];
        m[1][2] -= mat.m[1][2];
        m[2][0] -= mat.m[2][0];
        m[2][1] -= mat.m[2][1];
        m[2][2] -= mat.m[2][2];
        return *this;
    }

    /// Multiplies this matrix by another matrix.
    ///
    /// Computes `this = this * mat`.
    ///
    /// @param mat Right-hand matrix.
    /// @return Reference to this matrix.
    inline_ Matrix3x3& operator*=(const Matrix3x3& mat)
    {
        Point TempRow;

        GetRow(0, TempRow);
        m[0][0] = TempRow.x * mat.m[0][0] + TempRow.y * mat.m[1][0] + TempRow.z * mat.m[2][0];
        m[0][1] = TempRow.x * mat.m[0][1] + TempRow.y * mat.m[1][1] + TempRow.z * mat.m[2][1];
        m[0][2] = TempRow.x * mat.m[0][2] + TempRow.y * mat.m[1][2] + TempRow.z * mat.m[2][2];

        GetRow(1, TempRow);
        m[1][0] = TempRow.x * mat.m[0][0] + TempRow.y * mat.m[1][0] + TempRow.z * mat.m[2][0];
        m[1][1] = TempRow.x * mat.m[0][1] + TempRow.y * mat.m[1][1] + TempRow.z * mat.m[2][1];
        m[1][2] = TempRow.x * mat.m[0][2] + TempRow.y * mat.m[1][2] + TempRow.z * mat.m[2][2];

        GetRow(2, TempRow);
        m[2][0] = TempRow.x * mat.m[0][0] + TempRow.y * mat.m[1][0] + TempRow.z * mat.m[2][0];
        m[2][1] = TempRow.x * mat.m[0][1] + TempRow.y * mat.m[1][1] + TempRow.z * mat.m[2][1];
        m[2][2] = TempRow.x * mat.m[0][2] + TempRow.y * mat.m[1][2] + TempRow.z * mat.m[2][2];
        return *this;
    }

    /// Multiplies every matrix element by a scalar.
    ///
    /// @param s Scalar multiplier.
    /// @return Reference to this matrix.
    inline_ Matrix3x3& operator*=(float s)
    {
        m[0][0] *= s;
        m[0][1] *= s;
        m[0][2] *= s;
        m[1][0] *= s;
        m[1][1] *= s;
        m[1][2] *= s;
        m[2][0] *= s;
        m[2][1] *= s;
        m[2][2] *= s;
        return *this;
    }

    /// Divides every matrix element by a scalar.
    ///
    /// If the scalar is zero, all matrix elements become zero.
    ///
    /// @param s Scalar divisor.
    /// @return Reference to this matrix.
    inline_ Matrix3x3& operator/=(float s)
    {
        if (s) s = 1.0f / s;
        m[0][0] *= s;
        m[0][1] *= s;
        m[0][2] *= s;
        m[1][0] *= s;
        m[1][1] *= s;
        m[1][2] *= s;
        m[2][0] *= s;
        m[2][1] *= s;
        m[2][2] *= s;
        return *this;
    }

    /// Converts this matrix to a 4×4 matrix.
    ///
    /// @return Equivalent 4×4 matrix.
    operator Matrix4x4() const;

    /// Converts this matrix to a quaternion.
    ///
    /// @return Equivalent quaternion.
    operator Quat() const;

	/// Returns a read-only view of a matrix row.
    ///
    /// @param nRow Zero-based row index.
    /// @return Pointer to the requested row.
    inline_ const Point* operator[](int nRow) const { return (const Point*)&m[nRow][0]; }

	/// Returns a writable view of a matrix row.
    ///
    /// @param nRow Zero-based row index.
    /// @return Pointer to the requested row.
    inline_ Point* operator[](int nRow) { return (Point*)&m[nRow][0]; }

public:
    float m[3][3]; ///< Matrix elements stored in row-major order.
};
