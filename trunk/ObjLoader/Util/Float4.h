#pragma once

#include "MathDefine.h"
#include <assert.h>
class matrix44;
class float4
{
public:
	float4( );
	/// construct from values
	float4( scalar x, scalar y, scalar z, scalar w );
	/// copy constructor
	float4(const float4& rhs);
	/// assignment operator
	void operator=(const float4& rhs);
	/// flip sign
	float4 operator-() const;
	/// inplace add
	float4& operator+=(const float4& rhs);
	/// inplace sub
	float4& operator-=(const float4& rhs);
	/// inplace scalar multiply
	float4& operator*=(scalar s);
	/// add 2 vectors
	float4 operator+(const float4& rhs) const;
	/// subtract 2 vectors
	float4 operator-(const float4& rhs) const;
	/// multiply with scalar
	float4 operator*(scalar s) const;

	/// equality operator
	bool operator==(const float4& rhs) const;
	/// inequality operator
	bool operator!=(const float4& rhs) const;
	/// larger operator
	bool operator > (const float4& rhs) const;
	/// smaller operator
	bool operator < (const float4& rhs) const;
	
	scalar operator [] ( const size_t i ) const;

	scalar& operator [] ( const size_t i );


	/// return cross product
	static float4 cross3(const float4& v0, const float4& v1);
	/// return dot product of vectors
	static scalar dot3(const float4& v0, const float4& v1);
	/// return normalized version of 4d vector
	static float4 normalize(const float4& v);

	/// return length of vector
	scalar length() const;

	scalar X() const;
	scalar Y() const;
	scalar Z() const;
	scalar W() const;

	scalar& X();
	scalar& Y();
	scalar& Z();
	scalar& W();
private:
	scalar mx;
	scalar my;
	scalar mz;
	scalar mw;
};

inline float4::float4()
	:mx(0.0f)
	,my(0.0f)
	,mz(0.0f)
	,mw(0.0f)
{

}

inline float4::float4( scalar x, scalar y, scalar z, scalar w )
	:mx(x)
	,my(y)
	,mz(z)
	,mw(w)
{

}

inline float4::float4( const float4& rhs )
	:mx(rhs.mx)
	,my(rhs.my)
	,mz(rhs.mz)
	,mw(rhs.mw)
{

}

inline void float4::operator=( const float4& rhs )
{
	mx = rhs.mx;
	my = rhs.my;
	mz = rhs.mz;
	mw = rhs.mw;
}

inline float4 float4::operator-() const
{
	 return float4(-this->mx,-this->my,-this->mz,-this->mw);
}

inline float4& float4::operator+=( const float4& rhs )
{
	mx+=rhs.mx;
	my+=rhs.my;
	mz+=rhs.mz;
	mw+=rhs.mw;
	return *this;
}

inline float4& float4::operator-=( const float4& rhs )
{
	mx-=rhs.mx;
	my-=rhs.my;
	mz-=rhs.mz;
	mw-=rhs.mw;
	return *this;
}

inline float4 float4::operator+( const float4& rhs ) const
{
	 return float4(this->mx + rhs.mx,this->my + rhs.my,this->mz + rhs.mz,this->mw + rhs.mw);
}


inline float4 float4::operator-( const float4& rhs ) const
{
	 return float4(this->mx - rhs.mx,this->my - rhs.my,this->mz - rhs.mz,this->mw - rhs.mw);
}


inline float4 float4::operator*( scalar s ) const
{
	return float4(this->mx * s, this->my * s, this->mz * s, this->mw * s);
}

inline float4& float4::operator*=( scalar s )
{
	mx*=s;
	my*=s;
	mz*=s;
	mw*=s;
	return *this;
}

inline bool float4::operator==( const float4& rhs ) const
{
	return (mx==rhs.mx)&&(my==rhs.my)&&(mz==rhs.mz)&&(mw==rhs.mw);
}

inline bool float4::operator!=( const float4& rhs ) const
{
	return (mx!=rhs.mx)||(my!=rhs.my)||(mz!=rhs.mz)||(mw!=rhs.mw);
}

inline bool float4::operator>( const float4& rhs ) const
{
	return (mx>rhs.mx)&&(my>rhs.my)&&(mz>rhs.mz)&&(mw>rhs.mw);
}

inline bool float4::operator<( const float4& rhs ) const
{
	return (mx<rhs.mx)&&(my<rhs.my)&&(mz<rhs.mz)&&(mw<rhs.mw);
}

inline scalar float4::operator[]( const size_t i ) const
{
	assert( i < 4 );

	return *(&mx+i);
}

inline scalar& float4::operator[]( const size_t i )
{
	assert( i < 4 );

	return *(&mx+i);
}

inline float4 float4::cross3( const float4& v0, const float4& v1 )
{
	return float4( v0.my*v1.mz - v0.mz*v1.my, v0.mz*v1.mx - v0.mx*v1.mz, v0.mx*v1.my - v0.my*v1.mx, 0 );
}

inline scalar float4::dot3( const float4& v0, const float4& v1 )
{
	return v0.mx*v1.mx+ v0.my*v1.my+ v0.mz*v1.mz;
}

inline scalar float4::length() const
{
	return o_sqrt(this->mx * this->mx + this->my * this->my + this->mz * this->mz + this->mw * this->mw );
}

inline float4 float4::normalize( const float4& v )
{
	scalar l = v.length();
	if (l > 0.0f)
	{
		return float4(v.mx / l, v.my / l,v.mz / l, v.mw / l);
	}
	else
	{
		return float4(1.0f, 0.0f, 0.0f, 0.0f);
	}
}

inline scalar float4::X() const
{
	return mx;
}

inline scalar& float4::X()
{
	return mx;
}

inline scalar float4::Y() const
{
	return my;
}

inline scalar& float4::Y()
{
	return my;
}

inline scalar float4::Z() const
{
	return mz;
}

inline scalar& float4::Z() 
{
	return mz;
}

inline scalar float4::W() const
{
	return mw;
}

inline scalar& float4::W()
{
	return mw;
}
//------------------------------------------------------------------------------
