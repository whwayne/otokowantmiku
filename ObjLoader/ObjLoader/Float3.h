#pragma once

#include "MathDefine.h"

class float3
{
public:
	float3( );
	/// construct from values
	float3( scalar x, scalar y, scalar z);
	/// copy constructor
	float3(const float3& rhs);
	/// assignment operator
	void operator=(const float3& rhs);
	/// flip sign
	float3 operator-() const;
	/// inplace add
	void operator+=(const float3& rhs);
	/// inplace sub
	void operator-=(const float3& rhs);
	/// inplace scalar multiply
	void operator*=(scalar s);
	/// add 2 vectors
	float3 operator+(const float3& rhs) const;
	/// subtract 2 vectors
	float3 operator-(const float3& rhs) const;
	/// multiply with scalar
	float3 operator*(scalar s) const;
	/// equality operator
	bool operator==(const float3& rhs) const;
	/// inequality operator
	bool operator!=(const float3& rhs) const;

	/// return cross product
	static float3 cross(const float3& v0, const float3& v1);
	/// return dot product of vectors
	static scalar dot(const float3& v0, const float3& v1);
	/// return normalized version of 4d vector
	static float3 normalize(const float3& v);

	/// return length of vector
	scalar length() const;

	scalar X() const;
	scalar Y() const;
	scalar Z() const;


	scalar& X();
	scalar& Y();
	scalar& Z();

private:
	scalar mx;
	scalar my;
	scalar mz;
};

inline float3::float3()
:mx(0.0f)
,my(0.0f)
,mz(0.0f)
{

}

inline float3::float3( scalar x, scalar y, scalar z)
:mx(x)
,my(y)
,mz(z)
{

}

inline float3::float3( const float3& rhs )
:mx(rhs.mx)
,my(rhs.my)
,mz(rhs.mz)
{

}

inline void float3::operator=( const float3& rhs )
{
	mx = rhs.mx;
	my = rhs.my;
	mz = rhs.mz;
}

inline float3 float3::operator-() const
{
	return float3(-this->mx,-this->my,-this->mz);
}

inline void float3::operator+=( const float3& rhs )
{
	mx+=rhs.mx;
	my+=rhs.my;
	mz+=rhs.mz;
}

inline void float3::operator-=( const float3& rhs )
{
	mx-=rhs.mx;
	my-=rhs.my;
	mz-=rhs.mz;
}

inline float3 float3::operator+( const float3& rhs ) const
{
	return float3(this->mx + rhs.mx,this->my + rhs.my,this->mz + rhs.mz);
}

inline float3 float3::operator*( scalar s ) const
{
	return float3(this->mx * s, this->my * s, this->mz * s);
}

inline void float3::operator*=( scalar s )
{
	mx*=s;
	my*=s;
	mz*=s;
}

inline bool float3::operator==( const float3& rhs ) const
{
	return (mx==rhs.mx)&&(my==rhs.my)&&(mz==rhs.mz);
}

inline bool float3::operator!=( const float3& rhs ) const
{
	return (mx!=rhs.mx)||(my!=rhs.my)||(mz!=rhs.mz);
}

inline float3 float3::cross( const float3& v0, const float3& v1 )
{
	return float3( v0.my*v1.mz - v0.mz*v1.my, v0.mz*v1.mx - v0.mx*v1.mz, v0.mx*v1.my - v0.my*v1.mx );
}

inline scalar float3::dot( const float3& v0, const float3& v1 )
{
	return v0.mx*v1.mx+ v0.my*v1.my+ v0.mz*v1.mz;
}

inline scalar float3::length() const
{
	return o_sqrt(this->mx * this->mx + this->my * this->my + this->mz * this->mz );
}

inline float3 float3::normalize( const float3& v )
{
	scalar l = v.length();
	if (l > 0.0f)
	{
		return float3(v.mx / l, v.my / l,v.mz / l);
	}
	else
	{
		return float3(1.0f, 0.0f, 0.0f);
	}
}

inline scalar float3::X() const
{
	return mx;
}

inline scalar& float3::X()
{
	return mx;
}

inline scalar float3::Y() const
{
	return my;
}

inline scalar& float3::Y()
{
	return my;
}

inline scalar float3::Z() const
{
	return mz;
}

inline scalar& float3::Z() 
{
	return mz;
}

//------------------------------------------------------------------------------
