/// Contains code for 4×4 matrices.
///
/// @file IceMatrix4x4.h
/// @author Pierre Terdiman
/// @date April 4, 2000

#pragma once

class PRS;
class PR;

/// Tolerance used for floating-point matrix comparisons.
#define MATRIX4X4_EPSILON (1.0e-7f)

/// Convenience macro used by deprecated arithmetic operators.
#define MATRIX4X4_ROW *(*this)

/// 4×4 transformation matrix.
///
/// The matrix stores rotation, translation, and optional scaling in row-major
/// order. It provides operations for constructing and manipulating affine
/// transformations, as well as general-purpose matrix arithmetic.
class ICEMATHS_API Matrix4x4
{
#if 0
    void LUBackwardSubstitution( sdword *indx, float* b );
    void LUDecomposition( sdword* indx, float* d );
#endif

public:
    /// Constructs an uninitialized matrix.
    inline_ Matrix4x4()
    {
    }

    /// Constructs a matrix from its sixteen components.
	///
	/// Components are specified in row-major order.
	///
	/// @param m00 Row 0, column 0.
	/// @param m01 Row 0, column 1.
	/// @param m02 Row 0, column 2.
	/// @param m03 Row 0, column 3.
	/// @param m10 Row 1, column 0.
	/// @param m11 Row 1, column 1.
	/// @param m12 Row 1, column 2.
	/// @param m13 Row 1, column 3.
	/// @param m20 Row 2, column 0.
	/// @param m21 Row 2, column 1.
	/// @param m22 Row 2, column 2.
	/// @param m23 Row 2, column 3.
	/// @param m30 Row 3, column 0.
	/// @param m31 Row 3, column 1.
	/// @param m32 Row 3, column 2.
	/// @param m33 Row 3, column 3.
    inline_ Matrix4x4(float m00, float m01, float m02, float m03,
                      float m10, float m11, float m12, float m13,
                      float m20, float m21, float m22, float m23,
                      float m30, float m31, float m32, float m33)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
    }

    /// Constructs a copy of another matrix.
	///
	/// @param mat Matrix to copy.
    inline_ Matrix4x4(const Matrix4x4& mat)
    {
        CopyMemory(m, &mat.m, 16*sizeof(float));
    }

    /// Destroys the matrix.
    inline_ ~Matrix4x4()
    {
    }

    /// Sets the upper-left 3×3 portion of the matrix.
	///
	/// This is typically used to assign the rotation component of an affine
	/// transformation. The remaining elements are left unchanged.
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
	/// @return Reference to this matrix.
    inline_ Matrix4x4& Set(float m00, float m01, float m02,
                           float m10, float m11, float m12,
                           float m20, float m21, float m22)
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
        return *this;
    }

    /// Sets all sixteen matrix components.
	///
	/// Components are specified in row-major order.
	///
	/// @param m00 Row 0, column 0.
	/// @param m01 Row 0, column 1.
	/// @param m02 Row 0, column 2.
	/// @param m03 Row 0, column 3.
	/// @param m10 Row 1, column 0.
	/// @param m11 Row 1, column 1.
	/// @param m12 Row 1, column 2.
	/// @param m13 Row 1, column 3.
	/// @param m20 Row 2, column 0.
	/// @param m21 Row 2, column 1.
	/// @param m22 Row 2, column 2.
	/// @param m23 Row 2, column 3.
	/// @param m30 Row 3, column 0.
	/// @param m31 Row 3, column 1.
	/// @param m32 Row 3, column 2.
	/// @param m33 Row 3, column 3.
	/// @return Reference to this matrix.
    inline_ Matrix4x4& Set(float m00, float m01, float m02, float m03,
                           float m10, float m11, float m12, float m13,
                           float m20, float m21, float m22, float m23,
                           float m30, float m31, float m32, float m33)
    {
        m[0][0] = m00;
        m[0][1] = m01;
        m[0][2] = m02;
        m[0][3] = m03;
        m[1][0] = m10;
        m[1][1] = m11;
        m[1][2] = m12;
        m[1][3] = m13;
        m[2][0] = m20;
        m[2][1] = m21;
        m[2][2] = m22;
        m[2][3] = m23;
        m[3][0] = m30;
        m[3][1] = m31;
        m[3][2] = m32;
        m[3][3] = m33;
        return *this;
    }

    /// Returns the translation component of the matrix.
	///
	/// @return Pointer to the translation row.
    inline_ const HPoint* GetTrans() const
    {
        return (*this)[3];/*(Point*) &mTrans;*/
    }

    /// Returns the translation component of the matrix.
	///
	/// @param p Receives the translation vector.
    inline_ void GetTrans(Point& p) const
    {
        p.x = m[3][0];
        p.y = m[3][1];
        p.z = m[3][2];
    }

    /// Sets the translation component of the matrix.
	///
	/// @param p Translation vector.
    inline_ void SetTrans(const Point& p)
    {
        m[3][0] = p.x;
        m[3][1] = p.y;
        m[3][2] = p.z;
    }

#if 0
    /// Sets the translation part of the matrix, from a HPoint.
    inline_ void SetTrans(const HPoint& p)
	{
		m[3][0] = p.x;
		m[3][1] = p.y;
		m[3][2] = p.z;
		m[3][3] = p.w;
	}
#endif

    /// Sets the translation component of the matrix.
	///
	/// @param tx Translation along the X axis.
	/// @param ty Translation along the Y axis.
	/// @param tz Translation along the Z axis.
    inline_ void SetTrans(float tx, float ty, float tz)
    {
        m[3][0] = tx;
        m[3][1] = ty;
        m[3][2] = tz;
    }

    /// Sets the scale factors.
	///
	/// The components of the supplied vector are written to the diagonal of the
	/// upper-left 3×3 matrix.
	///
	/// @param p Scale factors along each axis.
    inline_ void SetScale(const Point& p)
    {
        m[0][0] = p.x;
        m[1][1] = p.y;
        m[2][2] = p.z;
    }

    /// Sets the scale factors.
	///
	/// The supplied values are written to the diagonal of the upper-left 3×3
	/// matrix.
	///
	/// @param sx Scale factor along the X axis.
	/// @param sy Scale factor along the Y axis.
	/// @param sz Scale factor along the Z axis.
    inline_ void SetScale(float sx, float sy, float sz)
    {
        m[0][0] = sx;
        m[1][1] = sy;
        m[2][2] = sz;
    }

    /// Applies a non-uniform scale to the existing matrix.
	///
	/// Each basis vector is multiplied by the corresponding component of the
	/// supplied scale vector.
	///
	/// @param p Scale factors along each axis.
    void Scale(const Point& p)
    {
        m[0][0] *= p.x;
        m[1][0] *= p.y;
        m[2][0] *= p.z;
        m[0][1] *= p.x;
        m[1][1] *= p.y;
        m[2][1] *= p.z;
        m[0][2] *= p.x;
        m[1][2] *= p.y;
        m[2][2] *= p.z;
    }

    /// Applies a non-uniform scale to the existing matrix.
	///
	/// Each basis vector is multiplied by the corresponding scale factor.
	///
	/// @param sx Scale factor along the X axis.
	/// @param sy Scale factor along the Y axis.
	/// @param sz Scale factor along the Z axis.
    void Scale(float sx, float sy, float sz)
    {
        m[0][0] *= sx;
        m[1][0] *= sy;
        m[2][0] *= sz;
        m[0][1] *= sx;
        m[1][1] *= sy;
        m[2][1] *= sz;
        m[0][2] *= sx;
        m[1][2] *= sy;
        m[2][2] *= sz;
    }

    /// Copies the contents of another matrix.
	///
	/// @param source Matrix to copy.
    inline_ void Copy(const Matrix4x4& source)
    {
        CopyMemory(m, source.m, 16*sizeof(float));
    }

#if 0
    /// Returns a row.
    inline_ void GetRow(const udword r, HPoint& p) const { p.x=m[r][0]; p.y=m[r][1]; p.z=m[r][2]; p.w=m[r][3]; }
#endif

    /// Returns the specified row.
	///
	/// @param r Row index.
	/// @param p Receives the row's first three components.
    inline_ void GetRow(const udword r, Point& p) const
    {
        p.x = m[r][0];
        p.y = m[r][1];
        p.z = m[r][2];
    }

#if 0
    /// Sets a row.
    inline_ void SetRow(const udword r, const HPoint& p) { m[r][0]=p.x; m[r][1]=p.y; m[r][2]=p.z; m[r][3]=p.w; }
#endif

    /// Sets the specified row.
	///
	/// The first three components are taken from @p p. The fourth component is
	/// set to 0 for rows 0–2 and to 1 for row 3.
	///
	/// @param r Row index.
	/// @param p Row value.
    inline_ void SetRow(const udword r, const Point& p)
    {
        m[r][0] = p.x;
        m[r][1] = p.y;
        m[r][2] = p.z;
        m[r][3] = (r != 3) ? 0.0f : 1.0f;
    }

#if 0
    /// Returns a column.
    inline_ void GetCol(const udword c, HPoint& p) const { p.x=m[0][c]; p.y=m[1][c]; p.z=m[2][c]; p.w=m[3][c]; }
#endif

    /// Returns the specified column.
	///
	/// @param c Column index.
	/// @param p Receives the column's first three components.
    inline_ void GetCol(const udword c, Point& p) const
    {
        p.x = m[0][c];
        p.y = m[1][c];
        p.z = m[2][c];
    }

#if 0
    /// Sets a column.
    inline_ void SetCol(const udword c, const HPoint& p) { m[0][c]=p.x; m[1][c]=p.y; m[2][c]=p.z; m[3][c]=p.w; }
#endif

    /// Sets the specified column.
	///
	/// The first three components are taken from @p p. The fourth component is
	/// set to 0 for columns 0–2 and to 1 for column 3.
	///
	/// @param c Column index.
	/// @param p Column value.
    inline_ void SetCol(const udword c, const Point& p)
    {
        m[0][c] = p.x;
        m[1][c] = p.y;
        m[2][c] = p.z;
        m[3][c] = (c != 3) ? 0.0f : 1.0f;
    }

#if 0
            /// Returns a row.
            inline_ HPoint GetRow(const udword row) const { return mRow[row]; }

            /// Sets a row.
            inline_ Matrix4x4& SetRow(const udword row, const HPoint& p) { mRow[row] = p; return *this; }

            /// Sets a row.
			Matrix4x4&    SetRow(const udword row, const Point& p)
			{
				m[row][0] = p.x;
				m[row][1] = p.y;
				m[row][2] = p.z;
				m[row][3] = (row != 3) ? 0.0f : 1.0f;
				return    *this;
			}

            /// Returns a column.
			HPoint GetCol(const udword col) const
			{
				HPoint    Res;
				Res.x = m[0][col];
				Res.y = m[1][col];
				Res.z = m[2][col];
				Res.w = m[3][col];
				return    Res;
			}
			
            /// Sets a column.
			Matrix4x4& SetCol(const udword col, const HPoint& p)
			{
				m[0][col] = p.x;
				m[1][col] = p.y;
				m[2][col] = p.z;
				m[3][col] = p.w;
				return    *this;
			}

            /// Sets a column.
			Matrix4x4& SetCol(const udword col, const Point& p)
			{
				m[0][col] = p.x;
				m[1][col] = p.y;
				m[2][col] = p.z;
				m[3][col] = (col != 3) ? 0.0f : 1.0f;
				return    *this;
			}
#endif

    /// Computes the trace of the matrix.
	///
	/// The trace is the sum of the four diagonal elements.
	///
	/// @return Matrix trace.
    inline_ float Trace() const { return m[0][0] + m[1][1] + m[2][2] + m[3][3]; }

    /// Computes the trace of the upper-left 3×3 submatrix.
	///
	/// @return Trace of the rotation portion of the matrix.
    inline_ float Trace3x3() const { return m[0][0] + m[1][1] + m[2][2]; }

    /// Sets all matrix elements to zero.
    inline_ void Zero()
    {
        ZeroMemory(&m, sizeof(m));
    }

    /// Sets the matrix to the identity matrix.
    inline_ void Identity()
    {
        Zero();
        m[0][0] = m[1][1] = m[2][2] = m[3][3] = 1.0f;
    }

    /// Tests whether the matrix is an identity matrix.
	///
	/// The comparison is performed using exact IEEE floating-point bit patterns.
	///
	/// @return true if the matrix is an identity matrix.
    inline_ bool IsIdentity() const
    {
        if (IR(m[0][0]) != IEEE_1_0) return false;
        if (IR(m[0][1]) != 0) return false;
        if (IR(m[0][2]) != 0) return false;
        if (IR(m[0][3]) != 0) return false;

        if (IR(m[1][0]) != 0) return false;
        if (IR(m[1][1]) != IEEE_1_0) return false;
        if (IR(m[1][2]) != 0) return false;
        if (IR(m[1][3]) != 0) return false;

        if (IR(m[2][0]) != 0) return false;
        if (IR(m[2][1]) != 0) return false;
        if (IR(m[2][2]) != IEEE_1_0) return false;
        if (IR(m[2][3]) != 0) return false;

        if (IR(m[3][0]) != 0) return false;
        if (IR(m[3][1]) != 0) return false;
        if (IR(m[3][2]) != 0) return false;
        if (IR(m[3][3]) != IEEE_1_0) return false;
        return true;
    }

    /// Builds a world transformation matrix.
	///
	/// @param prs Position, rotation, and scale.
	/// @return Reference to this matrix.
    Matrix4x4& World(const PRS& prs);

	/// Builds a world transformation matrix.
	///
	/// @param pr Position and rotation.
	/// @return Reference to this matrix.
    Matrix4x4& World(const PR& pr);

    /// Builds a planar shadow projection matrix.
	///
	/// @param light Light position.
	/// @param p0 First point on the projection plane.
	/// @param p1 Second point on the projection plane.
	/// @param p2 Third point on the projection plane.
	/// @return Reference to this matrix.
    Matrix4x4& Shadow(const Point& light, const Point& p0, const Point& p1, const Point& p2);

    /// Builds a sphere-mapping texture matrix.
	///
	/// @param scale Sphere-map scale factor.
	/// @return Reference to this matrix.
    Matrix4x4& SphereMap(float scale = 0.5f);

    /// Builds a self-shadowing projection matrix.
	///
	/// @param light Light position.
	/// @return Reference to this matrix.
    Matrix4x4& SelfShadow(const Point& light);

    /// Builds a 2D rotozoom transformation matrix.
	///
	/// @param angle Rotation angle.
	/// @param zoom Zoom factor.
	/// @param posx Translation along the X axis.
	/// @param posy Translation along the Y axis.
	/// @return Reference to this matrix.
    Matrix4x4& Rotozoom(float angle, float zoom, float posx, float posy);

    /// Sets the matrix to a rotation about the X axis.
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

    /// Sets the matrix to a rotation about the Y axis.
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

    /// Sets the matrix to a rotation about the Z axis.
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

    /// Sets the matrix to a rotation about an arbitrary axis.
	///
	/// @param angle Rotation angle in radians.
	/// @param p1 First point defining the rotation axis.
	/// @param p2 Second point defining the rotation axis.
	/// @return Reference to this matrix.
    Matrix4x4& Rot(float angle, Point& p1, Point& p2);

    /// Transposes the matrix in place.
    void Transpose()
    {
        IR(m[1][0]) ^= IR(m[0][1]);
        IR(m[0][1]) ^= IR(m[1][0]);
        IR(m[1][0]) ^= IR(m[0][1]);
        IR(m[2][0]) ^= IR(m[0][2]);
        IR(m[0][2]) ^= IR(m[2][0]);
        IR(m[2][0]) ^= IR(m[0][2]);
        IR(m[3][0]) ^= IR(m[0][3]);
        IR(m[0][3]) ^= IR(m[3][0]);
        IR(m[3][0]) ^= IR(m[0][3]);
        IR(m[1][2]) ^= IR(m[2][1]);
        IR(m[2][1]) ^= IR(m[1][2]);
        IR(m[1][2]) ^= IR(m[2][1]);
        IR(m[1][3]) ^= IR(m[3][1]);
        IR(m[3][1]) ^= IR(m[1][3]);
        IR(m[1][3]) ^= IR(m[3][1]);
        IR(m[2][3]) ^= IR(m[3][2]);
        IR(m[3][2]) ^= IR(m[2][3]);
        IR(m[2][3]) ^= IR(m[3][2]);
    }

    /// Computes the specified cofactor.
	///
	/// Used internally during matrix inversion.
	///
	/// @param row Cofactor row.
	/// @param col Cofactor column.
	/// @return Cofactor value.
    float CoFactor(udword row, udword col) const;

    /// Computes the determinant of the matrix.
	///
	/// @return Matrix determinant.
    float Determinant() const;

    /// Replaces the matrix with its inverse.
	///
	/// The matrix must be nonsingular.
	///
	/// @return Reference to this matrix.
    Matrix4x4& Invert();

#if 0
    Matrix& ComputeAxisMatrix(Point& axis, float angle);
#endif

    /// Converts the matrix to its upper-left 3×3 submatrix.
	///
	/// Translation and the last row are discarded.
	///
	/// @return The extracted 3×3 matrix.
    inline_ operator Matrix3x3() const
    {
        return Matrix3x3(
            m[0][0], m[0][1], m[0][2],
            m[1][0], m[1][1], m[1][2],
            m[2][0], m[2][1], m[2][2]);
    }

    /// Converts the matrix to a quaternion.
	///
	/// The quaternion is constructed from the rotation component.
	///
	/// @return Equivalent quaternion.
    operator Quat() const;

    /// Converts the matrix to a position/rotation transform.
	///
	/// @return Equivalent position/rotation representation.
    operator PR() const;

    // Arithmetic operators
#if 0
    /// Operator for Matrix4x4 Plus = Matrix4x4 + Matrix4x4;
    inline_ Matrix4x4 operator+(const Matrix4x4& mat) const
	{
		Matrix4x4 Ret;
		Ret.SetRow(0, MATRIX4X4_ROW[0] + *mat[0]);
		Ret.SetRow(1, MATRIX4X4_ROW[1] + *mat[1]);
		Ret.SetRow(2, MATRIX4X4_ROW[2] + *mat[2]);
		Ret.SetRow(3, MATRIX4X4_ROW[3] + *mat[3]);
		return Ret;
	}

	/// Operator for Matrix4x4 Minus = Matrix4x4 - Matrix4x4;
	inline_ Matrix4x4 operator-(const Matrix4x4& mat) const
	{
		Matrix4x4 Ret;
		Ret.SetRow(0, MATRIX4X4_ROW[0] - *mat[0]);
		Ret.SetRow(1, MATRIX4X4_ROW[1] - *mat[1]);
		Ret.SetRow(2, MATRIX4X4_ROW[2] - *mat[2]);
		Ret.SetRow(3, MATRIX4X4_ROW[3] - *mat[3]);
		return Ret;
	}
#endif
					
    /// Multiplies two matrices.
	///
	/// @param mat Matrix to multiply by.
	/// @return Product of this matrix and @p mat.
    inline_ Matrix4x4 operator*(const Matrix4x4& mat) const
    {
        return Matrix4x4(
            m[0][0] * mat.m[0][0] + m[0][1] * mat.m[1][0] + m[0][2] * mat.m[2][0] + m[0][3] * mat.m[3][0],
            m[0][0] * mat.m[0][1] + m[0][1] * mat.m[1][1] + m[0][2] * mat.m[2][1] + m[0][3] * mat.m[3][1],
            m[0][0] * mat.m[0][2] + m[0][1] * mat.m[1][2] + m[0][2] * mat.m[2][2] + m[0][3] * mat.m[3][2],
            m[0][0] * mat.m[0][3] + m[0][1] * mat.m[1][3] + m[0][2] * mat.m[2][3] + m[0][3] * mat.m[3][3],

            m[1][0] * mat.m[0][0] + m[1][1] * mat.m[1][0] + m[1][2] * mat.m[2][0] + m[1][3] * mat.m[3][0],
            m[1][0] * mat.m[0][1] + m[1][1] * mat.m[1][1] + m[1][2] * mat.m[2][1] + m[1][3] * mat.m[3][1],
            m[1][0] * mat.m[0][2] + m[1][1] * mat.m[1][2] + m[1][2] * mat.m[2][2] + m[1][3] * mat.m[3][2],
            m[1][0] * mat.m[0][3] + m[1][1] * mat.m[1][3] + m[1][2] * mat.m[2][3] + m[1][3] * mat.m[3][3],

            m[2][0] * mat.m[0][0] + m[2][1] * mat.m[1][0] + m[2][2] * mat.m[2][0] + m[2][3] * mat.m[3][0],
            m[2][0] * mat.m[0][1] + m[2][1] * mat.m[1][1] + m[2][2] * mat.m[2][1] + m[2][3] * mat.m[3][1],
            m[2][0] * mat.m[0][2] + m[2][1] * mat.m[1][2] + m[2][2] * mat.m[2][2] + m[2][3] * mat.m[3][2],
            m[2][0] * mat.m[0][3] + m[2][1] * mat.m[1][3] + m[2][2] * mat.m[2][3] + m[2][3] * mat.m[3][3],

            m[3][0] * mat.m[0][0] + m[3][1] * mat.m[1][0] + m[3][2] * mat.m[2][0] + m[3][3] * mat.m[3][0],
            m[3][0] * mat.m[0][1] + m[3][1] * mat.m[1][1] + m[3][2] * mat.m[2][1] + m[3][3] * mat.m[3][1],
            m[3][0] * mat.m[0][2] + m[3][1] * mat.m[1][2] + m[3][2] * mat.m[2][2] + m[3][3] * mat.m[3][2],
            m[3][0] * mat.m[0][3] + m[3][1] * mat.m[1][3] + m[3][2] * mat.m[2][3] + m[3][3] * mat.m[3][3]);
    }

#if 0
    /// Operator for HPoint Mul = Matrix4x4 * HPoint;
    inline_ HPoint operator*(const HPoint& v) const { return HPoint(MATRIX4X4_ROW[0]|v, MATRIX4X4_ROW[1]|v, MATRIX4X4_ROW[2]|v, MATRIX4X4_ROW[3]|v); }
#endif

    /// Transforms a point.
	///
	/// The point is treated as having an implicit homogeneous coordinate of 1,
	/// so both rotation and translation are applied.
	///
	/// @param v Point to transform.
	/// @return Transformed point.
    inline_ Point operator*(const Point& v) const
    {
        return Point(m[0][0] * v.x + m[0][1] * v.y + m[0][2] * v.z + m[0][3],
                     m[1][0] * v.x + m[1][1] * v.y + m[1][2] * v.z + m[1][3],
                     m[2][0] * v.x + m[2][1] * v.y + m[2][2] * v.z + m[2][3]);
    }

    /// Multiplies every matrix element by a scalar.
	///
	/// @param s Scalar value.
	/// @return Scaled matrix.
    inline_ Matrix4x4 operator*(float s) const
    {
        return Matrix4x4(
            m[0][0] * s, m[0][1] * s, m[0][2] * s, m[0][3] * s,
            m[1][0] * s, m[1][1] * s, m[1][2] * s, m[1][3] * s,
            m[2][0] * s, m[2][1] * s, m[2][2] * s, m[2][3] * s,
            m[3][0] * s, m[3][1] * s, m[3][2] * s, m[3][3] * s);
    }

    /// Multiplies every matrix element by a scalar.
	///
	/// @param s Scalar value.
	/// @param mat Matrix to scale.
	/// @return Scaled matrix.
    inline_ friend Matrix4x4 operator*(float s, const Matrix4x4& mat)
    {
        return Matrix4x4(
            s * mat.m[0][0], s * mat.m[0][1], s * mat.m[0][2], s * mat.m[0][3],
            s * mat.m[1][0], s * mat.m[1][1], s * mat.m[1][2], s * mat.m[1][3],
            s * mat.m[2][0], s * mat.m[2][1], s * mat.m[2][2], s * mat.m[2][3],
            s * mat.m[3][0], s * mat.m[3][1], s * mat.m[3][2], s * mat.m[3][3]);
    }

    /// Divides every matrix element by a scalar.
	///
	/// @param s Scalar divisor.
	/// @return Scaled matrix.
    inline_ Matrix4x4 operator/(float s) const
    {
        if (s) s = 1.0f / s;

        return Matrix4x4(
            m[0][0] * s, m[0][1] * s, m[0][2] * s, m[0][3] * s,
            m[1][0] * s, m[1][1] * s, m[1][2] * s, m[1][3] * s,
            m[2][0] * s, m[2][1] * s, m[2][2] * s, m[2][3] * s,
            m[3][0] * s, m[3][1] * s, m[3][2] * s, m[3][3] * s);
    }

    /// Divides a scalar by every matrix element.
	///
	/// @param s Scalar numerator.
	/// @param mat Matrix denominator.
	/// @return Matrix containing the element-wise quotients.
    inline_ friend Matrix4x4 operator/(float s, const Matrix4x4& mat)
    {
        return Matrix4x4(
            s / mat.m[0][0], s / mat.m[0][1], s / mat.m[0][2], s / mat.m[0][3],
            s / mat.m[1][0], s / mat.m[1][1], s / mat.m[1][2], s / mat.m[1][3],
            s / mat.m[2][0], s / mat.m[2][1], s / mat.m[2][2], s / mat.m[2][3],
            s / mat.m[3][0], s / mat.m[3][1], s / mat.m[3][2], s / mat.m[3][3]);
    }

    /// Adds another matrix to this one.
	///
	/// @param mat Matrix to add.
	/// @return Reference to this matrix.
    inline_ Matrix4x4& operator+=(const Matrix4x4& mat)
    {
        m[0][0] += mat.m[0][0];
        m[0][1] += mat.m[0][1];
        m[0][2] += mat.m[0][2];
        m[0][3] += mat.m[0][3];
        m[1][0] += mat.m[1][0];
        m[1][1] += mat.m[1][1];
        m[1][2] += mat.m[1][2];
        m[1][3] += mat.m[1][3];
        m[2][0] += mat.m[2][0];
        m[2][1] += mat.m[2][1];
        m[2][2] += mat.m[2][2];
        m[2][3] += mat.m[2][3];
        m[3][0] += mat.m[3][0];
        m[3][1] += mat.m[3][1];
        m[3][2] += mat.m[3][2];
        m[3][3] += mat.m[3][3];
        return *this;
    }

    /// Subtracts another matrix from this one.
	///
	/// @param mat Matrix to subtract.
	/// @return Reference to this matrix.
    inline_ Matrix4x4& operator-=(const Matrix4x4& mat)
    {
        m[0][0] -= mat.m[0][0];
        m[0][1] -= mat.m[0][1];
        m[0][2] -= mat.m[0][2];
        m[0][3] -= mat.m[0][3];
        m[1][0] -= mat.m[1][0];
        m[1][1] -= mat.m[1][1];
        m[1][2] -= mat.m[1][2];
        m[1][3] -= mat.m[1][3];
        m[2][0] -= mat.m[2][0];
        m[2][1] -= mat.m[2][1];
        m[2][2] -= mat.m[2][2];
        m[2][3] -= mat.m[2][3];
        m[3][0] -= mat.m[3][0];
        m[3][1] -= mat.m[3][1];
        m[3][2] -= mat.m[3][2];
        m[3][3] -= mat.m[3][3];
        return *this;
    }

#if 0
    /// Operator for Matrix4x4 *= Matrix4x4;
	Matrix4x4& operator*=(const Matrix4x4& mat)
	{
		HPoint TempRow;

		GetRow(0, TempRow);
		m[0][0] = TempRow.x*mat.m[0][0] + TempRow.y*mat.m[1][0] + TempRow.z*mat.m[2][0] + TempRow.w*mat.m[3][0];
		m[0][1] = TempRow.x*mat.m[0][1] + TempRow.y*mat.m[1][1] + TempRow.z*mat.m[2][1] + TempRow.w*mat.m[3][1];
		m[0][2] = TempRow.x*mat.m[0][2] + TempRow.y*mat.m[1][2] + TempRow.z*mat.m[2][2] + TempRow.w*mat.m[3][2];
		m[0][3] = TempRow.x*mat.m[0][3] + TempRow.y*mat.m[1][3] + TempRow.z*mat.m[2][3] + TempRow.w*mat.m[3][3];

		GetRow(1, TempRow);
		m[1][0] = TempRow.x*mat.m[0][0] + TempRow.y*mat.m[1][0] + TempRow.z*mat.m[2][0] + TempRow.w*mat.m[3][0];
		m[1][1] = TempRow.x*mat.m[0][1] + TempRow.y*mat.m[1][1] + TempRow.z*mat.m[2][1] + TempRow.w*mat.m[3][1];
		m[1][2] = TempRow.x*mat.m[0][2] + TempRow.y*mat.m[1][2] + TempRow.z*mat.m[2][2] + TempRow.w*mat.m[3][2];
		m[1][3] = TempRow.x*mat.m[0][3] + TempRow.y*mat.m[1][3] + TempRow.z*mat.m[2][3] + TempRow.w*mat.m[3][3];

		GetRow(2, TempRow);
		m[2][0] = TempRow.x*mat.m[0][0] + TempRow.y*mat.m[1][0] + TempRow.z*mat.m[2][0] + TempRow.w*mat.m[3][0];
		m[2][1] = TempRow.x*mat.m[0][1] + TempRow.y*mat.m[1][1] + TempRow.z*mat.m[2][1] + TempRow.w*mat.m[3][1];
		m[2][2] = TempRow.x*mat.m[0][2] + TempRow.y*mat.m[1][2] + TempRow.z*mat.m[2][2] + TempRow.w*mat.m[3][2];
		m[2][3] = TempRow.x*mat.m[0][3] + TempRow.y*mat.m[1][3] + TempRow.z*mat.m[2][3] + TempRow.w*mat.m[3][3];

		GetRow(3, TempRow);
		m[3][0] = TempRow.x*mat.m[0][0] + TempRow.y*mat.m[1][0] + TempRow.z*mat.m[2][0] + TempRow.w*mat.m[3][0];
		m[3][1] = TempRow.x*mat.m[0][1] + TempRow.y*mat.m[1][1] + TempRow.z*mat.m[2][1] + TempRow.w*mat.m[3][1];
		m[3][2] = TempRow.x*mat.m[0][2] + TempRow.y*mat.m[1][2] + TempRow.z*mat.m[2][2] + TempRow.w*mat.m[3][2];
		m[3][3] = TempRow.x*mat.m[0][3] + TempRow.y*mat.m[1][3] + TempRow.z*mat.m[2][3] + TempRow.w*mat.m[3][3];

		return *this;
	}
#endif

    /// Multiplies every matrix element by a scalar.
	///
	/// @param s Scalar value.
	/// @return Reference to this matrix.
    inline_ Matrix4x4& operator*=(float s)
    {
        m[0][0] *= s;
        m[0][1] *= s;
        m[0][2] *= s;
        m[0][3] *= s;
        m[1][0] *= s;
        m[1][1] *= s;
        m[1][2] *= s;
        m[1][3] *= s;
        m[2][0] *= s;
        m[2][1] *= s;
        m[2][2] *= s;
        m[2][3] *= s;
        m[3][0] *= s;
        m[3][1] *= s;
        m[3][2] *= s;
        m[3][3] *= s;
        return *this;
    }

    /// Divides every matrix element by a scalar.
	///
	/// @param s Scalar divisor.
	/// @return Reference to this matrix.
    inline_ Matrix4x4& operator/=(float s)
    {
        if (s) s = 1.0f / s;
        m[0][0] *= s;
        m[0][1] *= s;
        m[0][2] *= s;
        m[0][3] *= s;
        m[1][0] *= s;
        m[1][1] *= s;
        m[1][2] *= s;
        m[1][3] *= s;
        m[2][0] *= s;
        m[2][1] *= s;
        m[2][2] *= s;
        m[2][3] *= s;
        m[3][0] *= s;
        m[3][1] *= s;
        m[3][2] *= s;
        m[3][3] *= s;
        return *this;
    }

	/// Returns the specified matrix row.
	///
	/// @param nRow Zero-based row index.
	/// @return Pointer to the requested row.
    inline_ const HPoint* operator[](int nRow) const { return (const HPoint*)&m[nRow][0]; }

	/// Returns the specified matrix row.
	///
	/// @param nRow Zero-based row index.
	/// @return Pointer to the requested row.
    inline_ HPoint* operator[](int nRow) { return (HPoint*)&m[nRow][0]; }

public:
	/// Matrix elements stored in row-major order.
	///
	/// The upper-left 3×3 submatrix stores the linear transformation
	/// (typically rotation and scale), while the fourth row stores the
	/// translation for affine transforms.
    float m[4][4];
};

/// Transforms a point using the upper 4×3 portion of a 4×4 matrix.
///
/// Applies rotation and translation while assuming the input point has an
/// implicit homogeneous coordinate of 1.
///
/// @param dest Receives the transformed point.
/// @param source Point to transform.
/// @param rot Transformation matrix.
inline_ void TransformPoint4x3(Point& dest, const Point& source, const Matrix4x4& rot)
{
    dest.x = rot.m[3][0] + source.x * rot.m[0][0] + source.y * rot.m[1][0] + source.z * rot.m[2][0];
    dest.y = rot.m[3][1] + source.x * rot.m[0][1] + source.y * rot.m[1][1] + source.z * rot.m[2][1];
    dest.z = rot.m[3][2] + source.x * rot.m[0][2] + source.y * rot.m[1][2] + source.z * rot.m[2][2];
}

/// Transforms a point using only the upper 3×3 portion of a 4×4 matrix.
///
/// Applies rotation (and any embedded scaling or shearing) without
/// translation.
///
/// @param dest Receives the transformed point.
/// @param source Point to transform.
/// @param rot Transformation matrix.
inline_ void TransformPoint3x3(Point& dest, const Point& source, const Matrix4x4& rot)
{
    dest.x = source.x * rot.m[0][0] + source.y * rot.m[1][0] + source.z * rot.m[2][0];
    dest.y = source.x * rot.m[0][1] + source.y * rot.m[1][1] + source.z * rot.m[2][1];
    dest.z = source.x * rot.m[0][2] + source.y * rot.m[1][2] + source.z * rot.m[2][2];
}

/// Computes the inverse of a matrix containing only position and rotation.
///
/// This is faster than a general 4×4 matrix inversion because it assumes the
/// source matrix contains no scaling, shearing, or perspective components.
///
/// @param dest Receives the inverted matrix.
/// @param src Source matrix.
ICEMATHS_API void InvertPRMatrix(Matrix4x4& dest, const Matrix4x4& src);
