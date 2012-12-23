#pragma once
#include <Windows.h>
#include <math.h>
#include <stdio.h>

enum InterSectResult
{
	INTERSECTOUT = 0,
	INTERSECTPART,
	INTERSECTIN
};

typedef float scalar;

#define o_abs(t) std::abs(t)

#define o_sqrt(t) sqrt(t)

#define  o_sinR(t) sinf(t)

#define  o_cosR(t) cosf(t)


static const scalar PI = scalar( 4.0 * atan( 1.0 ) );
static const scalar TWO_PI = scalar( 2.0 * PI );
static const scalar HALF_PI = scalar( 0.5 * PI );
static const scalar fDeg2Rad = PI / scalar(180.0);
static const scalar fRad2Deg = scalar(180.0) / PI;
static const scalar LOG2 = log(scalar(2.0));

inline bool scalarEqual( scalar a, scalar b, scalar tolerance )
{
	if (fabs(b-a) <= tolerance)
		return true;
	else
		return false;
};

class Degree;
class Radian;




	/** \addtogroup Core
	*  @{
	*/
	/** \addtogroup Math
	*  @{
	*/
	/** Wrapper class which indicates a given angle value is in Radians.
    @remarks
        Radian values are interchangeable with Degree values, and conversions
        will be done automatically between them.
    */
	class Radian
	{
		scalar mRad;

	public:
		explicit Radian ( scalar r=0 ) : mRad(r) {}
		Radian ( const Degree& d );
		Radian& operator = ( const scalar& f ) { mRad = f; return *this; }
		Radian& operator = ( const Radian& r ) { mRad = r.mRad; return *this; }
		Radian& operator = ( const Degree& d );

		scalar valueDegrees() const; // see bottom of this file
		scalar valueRadians() const { return mRad; }
		scalar valueAngleUnits() const;

        const Radian& operator + () const { return *this; }
		Radian operator + ( const Radian& r ) const { return Radian ( mRad + r.mRad ); }
		Radian operator + ( const Degree& d ) const;
		Radian& operator += ( const Radian& r ) { mRad += r.mRad; return *this; }
		Radian& operator += ( const Degree& d );
		Radian operator - () const { return Radian(-mRad); }
		Radian operator - ( const Radian& r ) const { return Radian ( mRad - r.mRad ); }
		Radian operator - ( const Degree& d ) const;
		Radian& operator -= ( const Radian& r ) { mRad -= r.mRad; return *this; }
		Radian& operator -= ( const Degree& d );
		Radian operator * ( scalar f ) const { return Radian ( mRad * f ); }
        Radian operator * ( const Radian& f ) const { return Radian ( mRad * f.mRad ); }
		Radian& operator *= ( scalar f ) { mRad *= f; return *this; }
		Radian operator / ( scalar f ) const { return Radian ( mRad / f ); }
		Radian& operator /= ( scalar f ) { mRad /= f; return *this; }

		bool operator <  ( const Radian& r ) const { return mRad <  r.mRad; }
		bool operator <= ( const Radian& r ) const { return mRad <= r.mRad; }
		bool operator == ( const Radian& r ) const { return mRad == r.mRad; }
		bool operator != ( const Radian& r ) const { return mRad != r.mRad; }
		bool operator >= ( const Radian& r ) const { return mRad >= r.mRad; }
		bool operator >  ( const Radian& r ) const { return mRad >  r.mRad; }

	};


	   /** Wrapper class which indicates a given angle value is in Degrees.
    @remarks
        Degree values are interchangeable with Radian values, and conversions
        will be done automatically between them.
    */
	class Degree
	{
		scalar mDeg; // if you get an error here - make sure to define/typedef 'scalar' first

	public:
		explicit Degree ( scalar d=0 ) : mDeg(d) {}
		Degree ( const Radian& r ) : mDeg(r.valueDegrees()) {}
		Degree& operator = ( const scalar& f ) { mDeg = f; return *this; }
		Degree& operator = ( const Degree& d ) { mDeg = d.mDeg; return *this; }
		Degree& operator = ( const Radian& r ) { mDeg = r.valueDegrees(); return *this; }

		scalar valueDegrees() const { return mDeg; }
		scalar valueRadians() const; // see bottom of this file
		scalar valueAngleUnits() const;

		const Degree& operator + () const { return *this; }
		Degree operator + ( const Degree& d ) const { return Degree ( mDeg + d.mDeg ); }
		Degree operator + ( const Radian& r ) const { return Degree ( mDeg + r.valueDegrees() ); }
		Degree& operator += ( const Degree& d ) { mDeg += d.mDeg; return *this; }
		Degree& operator += ( const Radian& r ) { mDeg += r.valueDegrees(); return *this; }
		Degree operator - () const { return Degree(-mDeg); }
		Degree operator - ( const Degree& d ) const { return Degree ( mDeg - d.mDeg ); }
		Degree operator - ( const Radian& r ) const { return Degree ( mDeg - r.valueDegrees() ); }
		Degree& operator -= ( const Degree& d ) { mDeg -= d.mDeg; return *this; }
		Degree& operator -= ( const Radian& r ) { mDeg -= r.valueDegrees(); return *this; }
		Degree operator * ( scalar f ) const { return Degree ( mDeg * f ); }
        Degree operator * ( const Degree& f ) const { return Degree ( mDeg * f.mDeg ); }
		Degree& operator *= ( scalar f ) { mDeg *= f; return *this; }
		Degree operator / ( scalar f ) const { return Degree ( mDeg / f ); }
		Degree& operator /= ( scalar f ) { mDeg /= f; return *this; }

		bool operator <  ( const Degree& d ) const { return mDeg <  d.mDeg; }
		bool operator <= ( const Degree& d ) const { return mDeg <= d.mDeg; }
		bool operator == ( const Degree& d ) const { return mDeg == d.mDeg; }
		bool operator != ( const Degree& d ) const { return mDeg != d.mDeg; }
		bool operator >= ( const Degree& d ) const { return mDeg >= d.mDeg; }
		bool operator >  ( const Degree& d ) const { return mDeg >  d.mDeg; }

	};
    /** Wrapper class which identifies a value as the currently default angle 
        type, as defined by Math::setAngleUnit.
    @remarks
        Angle values will be automatically converted between radians and degrees,
        as appropriate.
    */
	class Angle
	{
		scalar mAngle;
	public:
		explicit Angle ( scalar angle ) : mAngle(angle) {}
		operator Radian() const;
		operator Degree() const;
	};

	// these functions could not be defined within the class definition of class
	// Radian because they required class Degree to be defined
	inline Radian::Radian ( const Degree& d ) : mRad(d.valueRadians()) {
	}
	inline Radian& Radian::operator = ( const Degree& d ) {
		mRad = d.valueRadians(); return *this;
	}
	inline Radian Radian::operator + ( const Degree& d ) const {
		return Radian ( mRad + d.valueRadians() );
	}
	inline Radian& Radian::operator += ( const Degree& d ) {
		mRad += d.valueRadians();
		return *this;
	}
	inline Radian Radian::operator - ( const Degree& d ) const {
		return Radian ( mRad - d.valueRadians() );
	}
	inline Radian& Radian::operator -= ( const Degree& d ) {
		mRad -= d.valueRadians();
		return *this;
	}



static inline scalar Abs (scalar fValue) { return scalar(fabs(fValue)); }
static inline Degree Abs (const Degree& dValue) { return Degree(fabs(dValue.valueDegrees())); }
static inline Radian Abs (const Radian& rValue) { return Radian(fabs(rValue.valueRadians())); }

static inline Radian ATan (scalar fValue) { return Radian(atan(fValue)); }
static inline Radian ATan2 (scalar fY, scalar fX) { return Radian(atan2(fY,fX)); }
static inline scalar Ceil (scalar fValue) { return scalar(ceil(fValue)); }

 Radian ACos (scalar fValue);
 Radian ASin (scalar fValue);

static inline scalar DegreesToRadians(scalar degrees) { return degrees * fDeg2Rad; }
static inline scalar RadiansToDegrees(scalar radians) { return radians * fRad2Deg; }

static scalar AngleUnitsToRadians( scalar units )
{
	return units*fRad2Deg;
}

static scalar RadiansToAngleUnits( scalar radians )
{
	return radians * fRad2Deg;
}

static scalar AngleUnitsToDegrees( scalar units )
{
	return units * fRad2Deg;
}

static scalar DegreesToAngleUnits( scalar degrees )
{
	return degrees * fDeg2Rad;
}



// these functions must be defined down here, because they rely on the
// angle unit conversion functions in class Math:

inline scalar Radian::valueDegrees() const
{
	return RadiansToDegrees ( mRad );
}

inline scalar Radian::valueAngleUnits() const
{
	return RadiansToAngleUnits ( mRad );
}

inline scalar Degree::valueRadians() const
{
	return DegreesToRadians ( mDeg );
}

inline scalar Degree::valueAngleUnits() const
{
	return DegreesToAngleUnits ( mDeg );
}

inline Angle::operator Radian() const
{
	return Radian(AngleUnitsToRadians(mAngle));
}

inline Angle::operator Degree() const
{
	return Degree(AngleUnitsToDegrees(mAngle));
}

inline Radian operator * ( scalar a, const Radian& b )
{
	return Radian ( a * b.valueRadians() );
}

inline Radian operator / ( scalar a, const Radian& b )
{
	return Radian ( a / b.valueRadians() );
}

inline Degree operator * ( scalar a, const Degree& b )
{
	return Degree ( a * b.valueDegrees() );
}

inline Degree operator / ( scalar a, const Degree& b )
{
	return Degree ( a / b.valueDegrees() );
}

inline static scalar SinF(scalar t)
{
	return sinf(t);
}

inline static scalar SinR(const Radian& fValue)
{
	return sinf(fValue.valueRadians());
}

inline static scalar CosF(scalar t)
{
	return cosf(t);
}

inline static scalar CosR(const Radian& fValue)
{
	return cosf(fValue.valueRadians());
}

