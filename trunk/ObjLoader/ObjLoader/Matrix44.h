#pragma once
#include "MathDefine.h"
#include "float4.h"
#include "Quaternion.h"
#include <assert.h>

class matrix44
{
public:
	matrix44();
	matrix44(
		scalar m00,scalar m01,scalar m02,scalar m03,
		scalar m10,scalar m11,scalar m12,scalar m13,	 
		scalar m20,scalar m21,scalar m22,scalar m23,
		scalar m30,scalar m31,scalar m32,scalar m33
			);
	matrix44(const matrix44& m44);

    /** Check whether or not the matrix is affine matrix.
    @remarks
        An affine matrix is a 4x4 matrix with row 3 equal to (0, 0, 0, 1),
        e.g. no projective coefficients.
    */
    inline bool isAffine(void) const
    {
        return m[3][0] == 0 && m[3][1] == 0 && m[3][2] == 0 && m[3][3] == 1;
    }

	/// assignment operator
	matrix44& operator=(const matrix44& rhs);
	/// equality operator
	bool operator==(const matrix44& rhs) const;
	/// inequality operator
	bool operator!=(const matrix44& rhs) const;



	matrix44 concatenate(const matrix44 &m2) const;
	

     /** Matrix concatenation using '*'.
    */
    matrix44 operator * ( const matrix44 &m2 ) const;
  

	float4 operator * (const float4& v) const;


    /** Matrix addition.
    */
    matrix44 operator + ( const matrix44 &m2 ) const;
 
	
    /** Matrix subtraction.
    */
    matrix44 operator - ( const matrix44 &m2 ) const;


	inline scalar* operator [] ( size_t iRow );

	inline const scalar *operator [] ( size_t iRow ) const;




	matrix44 transpose() const;
	
       /*
    -----------------------------------------------------------------------
    Translation Transformation
    -----------------------------------------------------------------------
    */
    /** Sets the translation transformation part of the matrix.
    */
    void setTransRH( const float4& v );

    /** Builds a translation matrix
    */
    void makeTransRH( const float4& v );



    /*
    -----------------------------------------------------------------------
    Scale Transformation
    -----------------------------------------------------------------------
    */
    /** Sets the scale part of the matrix.
    */
    void setScale( const float4& v );
   

    /** Gets a scale matrix.
    */
    static matrix44 getScale( const float4& v );



	/** Determines if this matrix involves a scaling. */
	bool hasScale() const;

   
	matrix44 inverse() const;

	//-----------------------------------------------------------------------
	matrix44 inverseAffine(void) const;

	void decomposition(float4& position, float4& scale, Quaternion& orientation) const;

	void QDUDecomposition (matrix44& kQ,float4& kD, float4& kU) const;

	static matrix44 Projection(const float near_plane, /*Distance to near clipping  plane*/	const float far_plane,  /* Distance to far clipping  plane*/const float fov_horiz,  /* Horizontal field of view angle, in radians */const float fov_vert);

    static const matrix44 ZERO;
    static const matrix44 IDENTITY;
    /** Useful little matrix which takes 2D clipspace {-1, 1} to {0,1}
        and inverts the Y. */
    static const matrix44 CLIPSPACE2DTOIMAGESPACE;

protected:
	union {
		
		
		scalar _m[16];
		scalar m[4][4];
	};

private:

};

inline matrix44::matrix44()
{
	m[0][0] = 1.0f;
	m[0][1] = 0.0f;
	m[0][2] = 0.0f;
	m[0][3] = 0.0f;
	m[1][0] = 0.0f;
	m[1][1] = 1.0f;
	m[1][2] = 0.0f;
	m[1][3] = 0.0f;
	m[2][0] = 0.0f;
	m[2][1] = 0.0f;
	m[2][2] = 1.0f;
	m[2][3] = 0.0f;
	m[3][0] = 0.0f;
	m[3][1] = 0.0f;
	m[3][2] = 0.0f;
	m[3][3] = 1.0f;
}

inline matrix44::matrix44( scalar m00,scalar m01,scalar m02,scalar m03, 
				   scalar m10,scalar m11,scalar m12,scalar m13, 
				   scalar m20,scalar m21,scalar m22,scalar m23, 
				   scalar m30,scalar m31,scalar m32,scalar m33 )
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


inline matrix44::matrix44(const matrix44& m44 )
{
	m[0][0] = m44[0][0];
	m[0][1] = m44[0][1];
	m[0][2] = m44[0][2];
	m[0][3] = m44[0][3];
	m[1][0] = m44[1][0];
	m[1][1] = m44[1][1];
	m[1][2] = m44[1][2];
	m[1][3] = m44[1][3];
	m[2][0] = m44[2][0];
	m[2][1] = m44[2][1];
	m[2][2] = m44[2][2];
	m[2][3] = m44[2][3];
	m[3][0] = m44[3][0];
	m[3][1] = m44[3][1];
	m[3][2] = m44[3][2];
	m[3][3] = m44[3][3];
}

__forceinline
matrix44& matrix44::operator=( const matrix44& m44 )
{
	m[0][0] = m44[0][0];
	m[0][1] = m44[0][1];
	m[0][2] = m44[0][2];
	m[0][3] = m44[0][3];
	m[1][0] = m44[1][0];
	m[1][1] = m44[1][1];
	m[1][2] = m44[1][2];
	m[1][3] = m44[1][3];
	m[2][0] = m44[2][0];
	m[2][1] = m44[2][1];
	m[2][2] = m44[2][2];
	m[2][3] = m44[2][3];
	m[3][0] = m44[3][0];
	m[3][1] = m44[3][1];
	m[3][2] = m44[3][2];
	m[3][3] = m44[3][3];
	return *this;
}

//------------------------------------------------------------------------------
/**
*/
__forceinline bool
matrix44::operator==(const matrix44& m2) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
		m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
		return false;
	return true;
}
//------------------------------------------------------------------------------
/**
*/
__forceinline bool
matrix44::operator!=(const matrix44& m2) const
{
	if( 
		m[0][0] != m2.m[0][0] || m[0][1] != m2.m[0][1] || m[0][2] != m2.m[0][2] || m[0][3] != m2.m[0][3] ||
		m[1][0] != m2.m[1][0] || m[1][1] != m2.m[1][1] || m[1][2] != m2.m[1][2] || m[1][3] != m2.m[1][3] ||
		m[2][0] != m2.m[2][0] || m[2][1] != m2.m[2][1] || m[2][2] != m2.m[2][2] || m[2][3] != m2.m[2][3] ||
		m[3][0] != m2.m[3][0] || m[3][1] != m2.m[3][1] || m[3][2] != m2.m[3][2] || m[3][3] != m2.m[3][3] )
		return true;
	return false;
}

__forceinline matrix44
matrix44::concatenate( const matrix44 &m2 ) const
{
	matrix44 r;
	r.m[0][0] = m[0][0] * m2.m[0][0] + m[0][1] * m2.m[1][0] + m[0][2] * m2.m[2][0] + m[0][3] * m2.m[3][0];
	r.m[0][1] = m[0][0] * m2.m[0][1] + m[0][1] * m2.m[1][1] + m[0][2] * m2.m[2][1] + m[0][3] * m2.m[3][1];
	r.m[0][2] = m[0][0] * m2.m[0][2] + m[0][1] * m2.m[1][2] + m[0][2] * m2.m[2][2] + m[0][3] * m2.m[3][2];
	r.m[0][3] = m[0][0] * m2.m[0][3] + m[0][1] * m2.m[1][3] + m[0][2] * m2.m[2][3] + m[0][3] * m2.m[3][3];

	r.m[1][0] = m[1][0] * m2.m[0][0] + m[1][1] * m2.m[1][0] + m[1][2] * m2.m[2][0] + m[1][3] * m2.m[3][0];
	r.m[1][1] = m[1][0] * m2.m[0][1] + m[1][1] * m2.m[1][1] + m[1][2] * m2.m[2][1] + m[1][3] * m2.m[3][1];
	r.m[1][2] = m[1][0] * m2.m[0][2] + m[1][1] * m2.m[1][2] + m[1][2] * m2.m[2][2] + m[1][3] * m2.m[3][2];
	r.m[1][3] = m[1][0] * m2.m[0][3] + m[1][1] * m2.m[1][3] + m[1][2] * m2.m[2][3] + m[1][3] * m2.m[3][3];

	r.m[2][0] = m[2][0] * m2.m[0][0] + m[2][1] * m2.m[1][0] + m[2][2] * m2.m[2][0] + m[2][3] * m2.m[3][0];
	r.m[2][1] = m[2][0] * m2.m[0][1] + m[2][1] * m2.m[1][1] + m[2][2] * m2.m[2][1] + m[2][3] * m2.m[3][1];
	r.m[2][2] = m[2][0] * m2.m[0][2] + m[2][1] * m2.m[1][2] + m[2][2] * m2.m[2][2] + m[2][3] * m2.m[3][2];
	r.m[2][3] = m[2][0] * m2.m[0][3] + m[2][1] * m2.m[1][3] + m[2][2] * m2.m[2][3] + m[2][3] * m2.m[3][3];

	r.m[3][0] = m[3][0] * m2.m[0][0] + m[3][1] * m2.m[1][0] + m[3][2] * m2.m[2][0] + m[3][3] * m2.m[3][0];
	r.m[3][1] = m[3][0] * m2.m[0][1] + m[3][1] * m2.m[1][1] + m[3][2] * m2.m[2][1] + m[3][3] * m2.m[3][1];
	r.m[3][2] = m[3][0] * m2.m[0][2] + m[3][1] * m2.m[1][2] + m[3][2] * m2.m[2][2] + m[3][3] * m2.m[3][2];
	r.m[3][3] = m[3][0] * m2.m[0][3] + m[3][1] * m2.m[1][3] + m[3][2] * m2.m[2][3] + m[3][3] * m2.m[3][3];

	return r;
}

inline matrix44 matrix44::operator*( const matrix44 &m2 ) const
{
	return concatenate( m2 );
}

inline float4 matrix44::operator*( const float4& v ) const
{
	return float4(
		m[0][0] * v.X() + m[0][1] * v.Y() + m[0][2] * v.Z() + m[0][3] * v.W(), 
		m[1][0] * v.X() + m[1][1] * v.Y() + m[1][2] * v.Z() + m[1][3] * v.W(),
		m[2][0] * v.X() + m[2][1] * v.Y() + m[2][2] * v.Z() + m[2][3] * v.W(),
		m[3][0] * v.X() + m[3][1] * v.Y() + m[3][2] * v.Z() + m[3][3] * v.W()
		);
}

inline matrix44 matrix44::operator+( const matrix44 &m2 ) const
{
	matrix44 r;

	r.m[0][0] = m[0][0] + m2.m[0][0];
	r.m[0][1] = m[0][1] + m2.m[0][1];
	r.m[0][2] = m[0][2] + m2.m[0][2];
	r.m[0][3] = m[0][3] + m2.m[0][3];

	r.m[1][0] = m[1][0] + m2.m[1][0];
	r.m[1][1] = m[1][1] + m2.m[1][1];
	r.m[1][2] = m[1][2] + m2.m[1][2];
	r.m[1][3] = m[1][3] + m2.m[1][3];

	r.m[2][0] = m[2][0] + m2.m[2][0];
	r.m[2][1] = m[2][1] + m2.m[2][1];
	r.m[2][2] = m[2][2] + m2.m[2][2];
	r.m[2][3] = m[2][3] + m2.m[2][3];

	r.m[3][0] = m[3][0] + m2.m[3][0];
	r.m[3][1] = m[3][1] + m2.m[3][1];
	r.m[3][2] = m[3][2] + m2.m[3][2];
	r.m[3][3] = m[3][3] + m2.m[3][3];

	return r;
}

inline matrix44 matrix44::operator-( const matrix44 &m2 ) const
{
	matrix44 r;
	r.m[0][0] = m[0][0] - m2.m[0][0];
	r.m[0][1] = m[0][1] - m2.m[0][1];
	r.m[0][2] = m[0][2] - m2.m[0][2];
	r.m[0][3] = m[0][3] - m2.m[0][3];

	r.m[1][0] = m[1][0] - m2.m[1][0];
	r.m[1][1] = m[1][1] - m2.m[1][1];
	r.m[1][2] = m[1][2] - m2.m[1][2];
	r.m[1][3] = m[1][3] - m2.m[1][3];

	r.m[2][0] = m[2][0] - m2.m[2][0];
	r.m[2][1] = m[2][1] - m2.m[2][1];
	r.m[2][2] = m[2][2] - m2.m[2][2];
	r.m[2][3] = m[2][3] - m2.m[2][3];

	r.m[3][0] = m[3][0] - m2.m[3][0];
	r.m[3][1] = m[3][1] - m2.m[3][1];
	r.m[3][2] = m[3][2] - m2.m[3][2];
	r.m[3][3] = m[3][3] - m2.m[3][3];

	return r;
}

inline matrix44 matrix44::transpose() const
{
	return matrix44(m[0][0], m[1][0], m[2][0], m[3][0],
		m[0][1], m[1][1], m[2][1], m[3][1],
		m[0][2], m[1][2], m[2][2], m[3][2],
		m[0][3], m[1][3], m[2][3], m[3][3]);
}

inline void matrix44::setTransRH( const float4& v )
{
	assert(v.W()==0.0f);
	m[0][3] = v.X();
	m[1][3] = v.Y();
	m[2][3] = v.Z();
}

inline void matrix44::makeTransRH( const float4& v )
{
	assert(v.W()==0.0f);
	m[0][0] = 1.0; m[0][1] = 0.0; m[0][2] = 0.0; m[0][3] = v.X();
	m[1][0] = 0.0; m[1][1] = 1.0; m[1][2] = 0.0; m[1][3] = v.Y();
	m[2][0] = 0.0; m[2][1] = 0.0; m[2][2] = 1.0; m[2][3] = v.Z();
	m[3][0] = 0.0; m[3][1] = 0.0; m[3][2] = 0.0; m[3][3] = 1.0f;
}

inline void matrix44::setScale( const float4& v )
{
	assert(v.W()==0.0f);
	
	m[0][0] = v.X();
	m[1][1] = v.Y();
	m[2][2] = v.Z();
}

inline matrix44 matrix44::getScale( const float4& v )
{
	assert(v.W()==0.0f);
	matrix44 r;
	r.m[0][0] = v.X(); r.m[0][1] = 0.0; r.m[0][2] = 0.0; r.m[0][3] = 0.0;
	r.m[1][0] = 0.0; r.m[1][1] = v.Y(); r.m[1][2] = 0.0; r.m[1][3] = 0.0;
	r.m[2][0] = 0.0; r.m[2][1] = 0.0; r.m[2][2] = v.Z(); r.m[2][3] = 0.0;
	r.m[3][0] = 0.0; r.m[3][1] = 0.0; r.m[3][2] = 0.0; r.m[3][3] = 1.0f;

	return r;
}

inline bool matrix44::hasScale() const
{
	// check magnitude of column vectors (==local axes)
	scalar t = m[0][0] * m[0][0] + m[1][0] * m[1][0] + m[2][0] * m[2][0];
	if (!scalarEqual(t, 1.0, (scalar)1e-04))
		return true;
	t = m[0][1] * m[0][1] + m[1][1] * m[1][1] + m[2][1] * m[2][1];
	if (!scalarEqual(t, 1.0, (scalar)1e-04))
		return true;
	t = m[0][2] * m[0][2] + m[1][2] * m[1][2] + m[2][2] * m[2][2];
	if (!scalarEqual(t, 1.0, (scalar)1e-04))
		return true;

	return false;
}

inline matrix44 matrix44::inverse() const
{
	scalar m00 = m[0][0], m01 = m[0][1], m02 = m[0][2], m03 = m[0][3];
	scalar m10 = m[1][0], m11 = m[1][1], m12 = m[1][2], m13 = m[1][3];
	scalar m20 = m[2][0], m21 = m[2][1], m22 = m[2][2], m23 = m[2][3];
	scalar m30 = m[3][0], m31 = m[3][1], m32 = m[3][2], m33 = m[3][3];

	scalar v0 = m20 * m31 - m21 * m30;
	scalar v1 = m20 * m32 - m22 * m30;
	scalar v2 = m20 * m33 - m23 * m30;
	scalar v3 = m21 * m32 - m22 * m31;
	scalar v4 = m21 * m33 - m23 * m31;
	scalar v5 = m22 * m33 - m23 * m32;

	scalar t00 = + (v5 * m11 - v4 * m12 + v3 * m13);
	scalar t10 = - (v5 * m10 - v2 * m12 + v1 * m13);
	scalar t20 = + (v4 * m10 - v2 * m11 + v0 * m13);
	scalar t30 = - (v3 * m10 - v1 * m11 + v0 * m12);

	scalar invDet = 1 / (t00 * m00 + t10 * m01 + t20 * m02 + t30 * m03);

	scalar d00 = t00 * invDet;
	scalar d10 = t10 * invDet;
	scalar d20 = t20 * invDet;
	scalar d30 = t30 * invDet;

	scalar d01 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	scalar d11 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	scalar d21 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	scalar d31 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m10 * m31 - m11 * m30;
	v1 = m10 * m32 - m12 * m30;
	v2 = m10 * m33 - m13 * m30;
	v3 = m11 * m32 - m12 * m31;
	v4 = m11 * m33 - m13 * m31;
	v5 = m12 * m33 - m13 * m32;

	scalar d02 = + (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	scalar d12 = - (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	scalar d22 = + (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	scalar d32 = - (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	v0 = m21 * m10 - m20 * m11;
	v1 = m22 * m10 - m20 * m12;
	v2 = m23 * m10 - m20 * m13;
	v3 = m22 * m11 - m21 * m12;
	v4 = m23 * m11 - m21 * m13;
	v5 = m23 * m12 - m22 * m13;

	scalar d03 = - (v5 * m01 - v4 * m02 + v3 * m03) * invDet;
	scalar d13 = + (v5 * m00 - v2 * m02 + v1 * m03) * invDet;
	scalar d23 = - (v4 * m00 - v2 * m01 + v0 * m03) * invDet;
	scalar d33 = + (v3 * m00 - v1 * m01 + v0 * m02) * invDet;

	return matrix44(
		d00, d01, d02, d03,
		d10, d11, d12, d13,
		d20, d21, d22, d23,
		d30, d31, d32, d33);
}

inline matrix44 matrix44::inverseAffine( void ) const
{
	assert(isAffine());

	scalar m10 = m[1][0], m11 = m[1][1], m12 = m[1][2];
	scalar m20 = m[2][0], m21 = m[2][1], m22 = m[2][2];

	scalar t00 = m22 * m11 - m21 * m12;
	scalar t10 = m20 * m12 - m22 * m10;
	scalar t20 = m21 * m10 - m20 * m11;

	scalar m00 = m[0][0], m01 = m[0][1], m02 = m[0][2];

	scalar invDet = 1 / (m00 * t00 + m01 * t10 + m02 * t20);

	t00 *= invDet; t10 *= invDet; t20 *= invDet;

	m00 *= invDet; m01 *= invDet; m02 *= invDet;

	scalar r00 = t00;
	scalar r01 = m02 * m21 - m01 * m22;
	scalar r02 = m01 * m12 - m02 * m11;

	scalar r10 = t10;
	scalar r11 = m00 * m22 - m02 * m20;
	scalar r12 = m02 * m10 - m00 * m12;

	scalar r20 = t20;
	scalar r21 = m01 * m20 - m00 * m21;
	scalar r22 = m00 * m11 - m01 * m10;

	scalar m03 = m[0][3], m13 = m[1][3], m23 = m[2][3];

	scalar r03 = - (r00 * m03 + r01 * m13 + r02 * m23);
	scalar r13 = - (r10 * m03 + r11 * m13 + r12 * m23);
	scalar r23 = - (r20 * m03 + r21 * m13 + r22 * m23);

	return matrix44(
		r00, r01, r02, r03,
		r10, r11, r12, r13,
		r20, r21, r22, r23,
		0,   0,   0,   1);
}

inline scalar* matrix44::operator[]( size_t iRow )
{
	assert( iRow < 4 );
	return m[iRow];
}


inline const scalar * matrix44::operator[]( size_t iRow ) const
{
	assert( iRow < 4 );
	return m[iRow];
}

