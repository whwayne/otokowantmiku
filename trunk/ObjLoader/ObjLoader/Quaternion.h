#pragma once
#include "MathDefine.h"
#include "Float3.h"
#include "Matrix44.h"
#include <assert.h>

class Quaternion
{
public:
	Quaternion (scalar fW = 1.0,scalar fX = 0.0, scalar fY = 0.0, scalar fZ = 0.0);
	
	Quaternion(const Radian& rfAngle, const float3& rkAxis);
	
	
	/// Construct a quaternion from 3 orthonormal local axes
	Quaternion(const float3& xaxis, const float3& yaxis, const float3& zaxis);

	/// Construct a quaternion from 3 orthonormal local axes
	inline Quaternion(const float3* akAxis)
	{
		this->FromAxes(akAxis);
	}
	
	/// Array accessor operator
	scalar operator [] ( const size_t i ) const;

	/// Array accessor operator
	scalar& operator [] ( const size_t i );


	Quaternion& operator= (const Quaternion& rkQ);

	Quaternion operator+ (const Quaternion& rkQ) const;
	Quaternion operator- (const Quaternion& rkQ) const;
	Quaternion operator* (const Quaternion& rkQ) const;
	Quaternion operator* (scalar fScalar) const;
	friend Quaternion operator* (scalar fScalar,const Quaternion& rkQ);

	Quaternion operator- () const;
	inline bool operator== (const Quaternion& rhs) const;
	inline bool operator!= (const Quaternion& rhs) const;

	// functions of a quaternion
	scalar Dot (const Quaternion& rkQ) const;  // dot product
	scalar Norm () const;  // squared-length
	/// Normalises this quaternion, and returns the previous length
	scalar normalise(void); 
	Quaternion Inverse () const;  // apply to non-zero quaternion
	Quaternion UnitInverse () const;  // apply to unit-length quaternion
	Quaternion Exp () const;
	Quaternion Log () const;

	/// Pointer accessor for direct copying
	scalar* ptr();

	/// Pointer accessor for direct copying
	const scalar* ptr() const;



	/// Get the local x-axis
	float3 xAxis(void) const;
	/// Get the local y-axis
	float3 yAxis(void) const;
	/// Get the local z-axis
	float3 zAxis(void) const;

	void ToAxes (float3* akAxis) const;

	void ToAxes (float3& xAxis, float3& yAxis, float3& zAxis) const;

	void FromRotationMatrix (const matrix44& kRot);

	void FromAxes (const float3& xaxis, const float3& yaxis, const float3& zaxis);

	void FromAxes (const float3* akAxis);

	void FromAngleAxis (const Radian& rfAngle,const float3& rkAxis);

	void ToRotationMatrix (matrix44& kRot) const;



     // rotation of a vector by a quaternion
    float3 operator* (const float3& rkVector) const;

	/** Calculate the local roll element of this quaternion.
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Y of the quaternion onto the X and
		Y axes, the angle between them is returned. If set to false though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
		may involve less axial rotation. 
	*/
	Radian getRoll(bool reprojectAxis = true) const;
	/** Calculate the local pitch element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Z of the quaternion onto the X and
		Y axes, the angle between them is returned. If set to true though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
		may involve less axial rotation. 
	*/
	Radian getPitch(bool reprojectAxis = true) const;
	/** Calculate the local yaw element of this quaternion
	@param reprojectAxis By default the method returns the 'intuitive' result
		that is, if you projected the local Z of the quaternion onto the X and
		Z axes, the angle between them is returned. If set to true though, the
		result is the actual yaw that will be used to implement the quaternion,
		which is the shortest possible path to get to the same orientation and 
		may involve less axial rotation. 
	*/
	Radian getYaw(bool reprojectAxis = true) const;		
	/// Equality with tolerance (tolerance is max angle difference)
	bool equals(const Quaternion& rhs, const Radian& tolerance) const;
	
    // spherical linear interpolation
    static Quaternion Slerp (scalar fT, const Quaternion& rkP,
        const Quaternion& rkQ, bool shortestPath = false);

    static Quaternion SlerpExtraSpins (scalar fT,
        const Quaternion& rkP, const Quaternion& rkQ,
        int iExtraSpins);

    // setup for spherical quadratic interpolation
    static void Intermediate (const Quaternion& rkQ0,
        const Quaternion& rkQ1, const Quaternion& rkQ2,
        Quaternion& rka, Quaternion& rkB);

    // spherical quadratic interpolation
    static Quaternion Squad (scalar fT, const Quaternion& rkP,
        const Quaternion& rkA, const Quaternion& rkB,
        const Quaternion& rkQ, bool shortestPath = false);

    // normalised linear interpolation - faster but less accurate (non-constant rotation velocity)
    static Quaternion nlerp(scalar fT, const Quaternion& rkP, 
        const Quaternion& rkQ, bool shortestPath = false);

protected:
	// cutoff for sine near zero
	static const scalar ms_fEpsilon;

	// special values
	static const Quaternion ZERO;
	static const Quaternion IDENTITY;

	scalar w, x, y, z;
};


inline Quaternion::Quaternion( scalar fW /*= 1.0*/,scalar fX /*= 0.0*/, scalar fY /*= 0.0*/, scalar fZ /*= 0.0*/ )
:w(fW)
,x(fX)
,y(fY)
,z(fZ)
{

}

inline Quaternion::Quaternion( const Radian& rfAngle, const float3& rkAxis )
{
	this->FromAngleAxis(rfAngle, rkAxis);
}


inline Quaternion::Quaternion( const float3& xaxis, const float3& yaxis, const float3& zaxis )
{
	this->FromAxes(xaxis, yaxis, zaxis);
}


inline scalar Quaternion::operator[]( const size_t i ) const
{
	assert( i < 4 );

	return *(&w+i);
}


inline scalar& Quaternion::operator[]( const size_t i )
{
	assert( i < 4 );

	return *(&w+i);
}

inline scalar* Quaternion::ptr()
{
	return &w;
}


inline const scalar* Quaternion::ptr() const
{
	return &w;
}

inline Quaternion& Quaternion::operator=( const Quaternion& rkQ )
{
	w = rkQ.w;
	x = rkQ.x;
	y = rkQ.y;
	z = rkQ.z;
	return *this;
}


bool Quaternion::operator==( const Quaternion& rhs ) const
{
	return (rhs.x == x) && (rhs.y == y) && (rhs.z == z) && (rhs.w == w);
}

bool Quaternion::operator!=( const Quaternion& rhs ) const
{
	return !operator==(rhs);
}
