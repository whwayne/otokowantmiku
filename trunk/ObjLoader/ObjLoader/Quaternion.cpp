#include "Quaternion.h"

const scalar Quaternion::ms_fEpsilon = 1e-03;
const Quaternion Quaternion::ZERO(0.0,0.0,0.0,0.0);
const Quaternion Quaternion::IDENTITY(1.0,0.0,0.0,0.0);

void Quaternion::FromAngleAxis( const Radian& rfAngle,const float3& rkAxis )
{
	// assert:  axis[] is unit length
	//
	// The quaternion representing the rotation is
	//   q = cos(A/2)+sin(A/2)*(x*i+y*j+z*k)

	Radian fHalfAngle ( 0.5f*rfAngle );
	scalar fSin = SinR(fHalfAngle);
	w = CosR(fHalfAngle);
	x = fSin*rkAxis.X();
	y = fSin*rkAxis.Y();
	z = fSin*rkAxis.Z();
}

void Quaternion::FromAxes( const float3& xaxis, const float3& yaxis, const float3& zaxis )
{
	matrix44 kRot;

	kRot[0][0] = xaxis.X();
	kRot[1][0] = xaxis.Y();
	kRot[2][0] = xaxis.Z();

	kRot[0][1] = yaxis.X();
	kRot[1][1] = yaxis.Y();
	kRot[2][1] = yaxis.Z();

	kRot[0][2] = zaxis.X();
	kRot[1][2] = zaxis.Y();
	kRot[2][2] = zaxis.Z();

	FromRotationMatrix(kRot);

}

void Quaternion::FromAxes( const float3* akAxis )
{
	matrix44 kRot;

	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		kRot[0][iCol] = akAxis[iCol].X();
		kRot[1][iCol] = akAxis[iCol].Y();
		kRot[2][iCol] = akAxis[iCol].Z();
	}

	FromRotationMatrix(kRot);
}

void Quaternion::FromRotationMatrix( const matrix44& kRot )
{
	// Algorithm in Ken Shoemake's article in 1987 SIGGRAPH course notes
	// article "Quaternion Calculus and Fast Animation".

	scalar fTrace = kRot[0][0]+kRot[1][1]+kRot[2][2];
	scalar fRoot;

	if ( fTrace > 0.0 )
	{
		// |w| > 1/2, may as well choose w > 1/2
		fRoot = o_sqrt(fTrace + 1.0f);  // 2w
		w = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;  // 1/(4w)
		x = (kRot[2][1]-kRot[1][2])*fRoot;
		y = (kRot[0][2]-kRot[2][0])*fRoot;
		z = (kRot[1][0]-kRot[0][1])*fRoot;
	}
	else
	{
		// |w| <= 1/2
		static size_t s_iNext[3] = { 1, 2, 0 };
		size_t i = 0;
		if ( kRot[1][1] > kRot[0][0] )
			i = 1;
		if ( kRot[2][2] > kRot[i][i] )
			i = 2;
		size_t j = s_iNext[i];
		size_t k = s_iNext[j];

		fRoot =o_sqrt(kRot[i][i]-kRot[j][j]-kRot[k][k] + 1.0f);
		scalar* apkQuat[3] = { &x, &y, &z };
		*apkQuat[i] = 0.5f*fRoot;
		fRoot = 0.5f/fRoot;
		w = (kRot[k][j]-kRot[j][k])*fRoot;
		*apkQuat[j] = (kRot[j][i]+kRot[i][j])*fRoot;
		*apkQuat[k] = (kRot[k][i]+kRot[i][k])*fRoot;
	}
}

float3 Quaternion::xAxis( void ) const
{
	//Real fTx  = 2.0*x;
	scalar fTy  = 2.0f*y;
	scalar fTz  = 2.0f*z;
	scalar fTwy = fTy*w;
	scalar fTwz = fTz*w;
	scalar fTxy = fTy*x;
	scalar fTxz = fTz*x;
	scalar fTyy = fTy*y;
	scalar fTzz = fTz*z;

	return float3(1.0f-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);
}

float3 Quaternion::yAxis( void ) const
{
	scalar fTx  = 2.0f*x;
	scalar fTy  = 2.0f*y;
	scalar fTz  = 2.0f*z;
	scalar fTwx = fTx*w;
	scalar fTwz = fTz*w;
	scalar fTxx = fTx*x;
	scalar fTxy = fTy*x;
	scalar fTyz = fTz*y;
	scalar fTzz = fTz*z;

	return float3(fTxy-fTwz, 1.0f-(fTxx+fTzz), fTyz+fTwx);
}

float3 Quaternion::zAxis( void ) const
{
	scalar fTx  = 2.0f*x;
	scalar fTy  = 2.0f*y;
	scalar fTz  = 2.0f*z;
	scalar fTwx = fTx*w;
	scalar fTwy = fTy*w;
	scalar fTxx = fTx*x;
	scalar fTxz = fTz*x;
	scalar fTyy = fTy*y;
	scalar fTyz = fTz*y;

	return float3(fTxz+fTwy, fTyz-fTwx, 1.0f-(fTxx+fTyy));
}

void Quaternion::ToAxes( float3* akAxis ) const
{

	matrix44 kRot;

	ToRotationMatrix(kRot);

	for (size_t iCol = 0; iCol < 3; iCol++)
	{
		akAxis[iCol].X() = kRot[0][iCol];
		akAxis[iCol].Y() = kRot[1][iCol];
		akAxis[iCol].Z() = kRot[2][iCol];
	}

}

void Quaternion::ToAxes( float3& xaxis, float3& yaxis, float3& zaxis ) const
{
	matrix44 kRot;

	ToRotationMatrix(kRot);

	xaxis.X() = kRot[0][0];
	xaxis.Y() = kRot[1][0];
	xaxis.Z() = kRot[2][0];

	yaxis.X() = kRot[0][1];
	yaxis.Y() = kRot[1][1];
	yaxis.Z() = kRot[2][1];

	zaxis.X() = kRot[0][2];
	zaxis.Y() = kRot[1][2];
	zaxis.Z() = kRot[2][2];
}

void Quaternion::ToRotationMatrix( matrix44& kRot ) const
{
	scalar fTx  = x+x;
	scalar fTy  = y+y;
	scalar fTz  = z+z;
	scalar fTwx = fTx*w;
	scalar fTwy = fTy*w;
	scalar fTwz = fTz*w;
	scalar fTxx = fTx*x;
	scalar fTxy = fTy*x;
	scalar fTxz = fTz*x;
	scalar fTyy = fTy*y;
	scalar fTyz = fTz*y;
	scalar fTzz = fTz*z;

	kRot[0][0] = 1.0f-(fTyy+fTzz);
	kRot[0][1] = fTxy-fTwz;
	kRot[0][2] = fTxz+fTwy;
	kRot[1][0] = fTxy+fTwz;
	kRot[1][1] = 1.0f-(fTxx+fTzz);
	kRot[1][2] = fTyz-fTwx;
	kRot[2][0] = fTxz-fTwy;
	kRot[2][1] = fTyz+fTwx;
	kRot[2][2] = 1.0f-(fTxx+fTyy);
}

Quaternion Quaternion::operator+( const Quaternion& rkQ ) const
{
	 return Quaternion(w+rkQ.w,x+rkQ.x,y+rkQ.y,z+rkQ.z);
}

Quaternion Quaternion::operator-( const Quaternion& rkQ ) const
{
	 return Quaternion(w-rkQ.w,x-rkQ.x,y-rkQ.y,z-rkQ.z);
}

Quaternion Quaternion::operator*( const Quaternion& rkQ ) const
{
	// NOTE:  Multiplication is not generally commutative, so in most
	// cases p*q != q*p.

	return Quaternion
		(
		w * rkQ.w - x * rkQ.x - y * rkQ.y - z * rkQ.z,
		w * rkQ.x + x * rkQ.w + y * rkQ.z - z * rkQ.y,
		w * rkQ.y + y * rkQ.w + z * rkQ.x - x * rkQ.z,
		w * rkQ.z + z * rkQ.w + x * rkQ.y - y * rkQ.x
		);
}

Quaternion Quaternion::operator*( scalar fScalar ) const
{
	 return Quaternion(fScalar*w,fScalar*x,fScalar*y,fScalar*z);
}

Quaternion operator*( scalar fScalar,const Quaternion& rkQ )
{
	return Quaternion(fScalar*rkQ.w,fScalar*rkQ.x,fScalar*rkQ.y,
		fScalar*rkQ.z);
}

Quaternion Quaternion::operator-() const
{
	return Quaternion(-w,-x,-y,-z);
}

scalar Quaternion::Dot( const Quaternion& rkQ ) const
{
	return w*rkQ.w+x*rkQ.x+y*rkQ.y+z*rkQ.z;
}

scalar Quaternion::Norm() const
{
	return w*w+x*x+y*y+z*z;
}

scalar Quaternion::normalise( void )
{
	scalar len = Norm();
	scalar factor = 1.0f / o_sqrt(len);
	*this = *this * factor;
	return len;
}

Quaternion Quaternion::Inverse() const
{
	scalar fNorm = w*w+x*x+y*y+z*z;
	if ( fNorm > 0.0 )
	{
		scalar fInvNorm = 1.0f/fNorm;
		return Quaternion(w*fInvNorm,-x*fInvNorm,-y*fInvNorm,-z*fInvNorm);
	}
	else
	{
		// return an invalid result to flag the error
		return ZERO;
	}
}

Quaternion Quaternion::UnitInverse() const
{
	// assert:  'this' is unit length
	return Quaternion(w,-x,-y,-z);
}

Quaternion Quaternion::Exp() const
{
	// If q = A*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// exp(q) = cos(A)+sin(A)*(x*i+y*j+z*k).  If sin(A) is near zero,
	// use exp(q) = cos(A)+A*(x*i+y*j+z*k) since A/sin(A) has limit 1.

	Radian fAngle ( o_sqrt(x*x+y*y+z*z) );
	scalar fSin = SinR(fAngle);

	Quaternion kResult;
	kResult.w = CosR(fAngle);

	if ( Abs(fSin) >= ms_fEpsilon )
	{
		scalar fCoeff = fSin/(fAngle.valueRadians());
		kResult.x = fCoeff*x;
		kResult.y = fCoeff*y;
		kResult.z = fCoeff*z;
	}
	else
	{
		kResult.x = x;
		kResult.y = y;
		kResult.z = z;
	}

	return kResult;
}

Quaternion Quaternion::Log() const
{
	// If q = cos(A)+sin(A)*(x*i+y*j+z*k) where (x,y,z) is unit length, then
	// log(q) = A*(x*i+y*j+z*k).  If sin(A) is near zero, use log(q) =
	// sin(A)*(x*i+y*j+z*k) since sin(A)/A has limit 1.

	Quaternion kResult;
	kResult.w = 0.0;

	if ( Abs(w) < 1.0 )
	{
		Radian fAngle ( ACos(w) );
		scalar fSin = SinR(fAngle);
		if ( Abs(fSin) >= ms_fEpsilon )
		{
			scalar fCoeff = fAngle.valueRadians()/fSin;
			kResult.x = fCoeff*x;
			kResult.y = fCoeff*y;
			kResult.z = fCoeff*z;
			return kResult;
		}
	}

	kResult.x = x;
	kResult.y = y;
	kResult.z = z;

	return kResult;
}


float3 Quaternion::operator*( const float3& rkVector ) const
{
	// nVidia SDK implementation
	float3 uv, uuv;
	float3 qvec(x, y, z);
	uv = float3::cross(qvec,rkVector);
	uuv = float3::cross(qvec,uv);
	uv *= (2.0f * w);
	uuv *= 2.0f;

	return rkVector + uv + uuv;
}

Radian Quaternion::getRoll( bool reprojectAxis /*= true*/ ) const
{
	if (reprojectAxis)
	{
		// roll = atan2(localx.y, localx.x)
		// pick parts of xAxis() implementation that we need
		//			Real fTx  = 2.0*x;
		scalar fTy  = 2.0f*y;
		scalar fTz  = 2.0f*z;
		scalar fTwz = fTz*w;
		scalar fTxy = fTy*x;
		scalar fTyy = fTy*y;
		scalar fTzz = fTz*z;

		// Vector3(1.0-(fTyy+fTzz), fTxy+fTwz, fTxz-fTwy);

		return Radian(ATan2(fTxy+fTwz, 1.0f-(fTyy+fTzz)));

	}
	else
	{
		return Radian(ATan2(2*(x*y + w*z), w*w + x*x - y*y - z*z));
	}
}	

Radian Quaternion::getPitch( bool reprojectAxis /*= true*/ ) const
{
	if (reprojectAxis)
	{
		// pitch = atan2(localy.z, localy.y)
		// pick parts of yAxis() implementation that we need
		scalar fTx  = 2.0f*x;
		//			Real fTy  = 2.0f*y;
		scalar fTz  = 2.0f*z;
		scalar fTwx = fTx*w;
		scalar fTxx = fTx*x;
		scalar fTyz = fTz*y;
		scalar fTzz = fTz*z;

		// Vector3(fTxy-fTwz, 1.0-(fTxx+fTzz), fTyz+fTwx);
		return Radian(ATan2(fTyz+fTwx, 1.0f-(fTxx+fTzz)));
	}
	else
	{
		// internal version
		return Radian(ATan2(2*(y*z + w*x), w*w - x*x - y*y + z*z));
	}
}

Radian Quaternion::getYaw( bool reprojectAxis /*= true*/ ) const
{
	if (reprojectAxis)
	{
		// yaw = atan2(localz.x, localz.z)
		// pick parts of zAxis() implementation that we need
		scalar fTx  = 2.0f*x;
		scalar fTy  = 2.0f*y;
		scalar fTz  = 2.0f*z;
		scalar fTwy = fTy*w;
		scalar fTxx = fTx*x;
		scalar fTxz = fTz*x;
		scalar fTyy = fTy*y;

		// Vector3(fTxz+fTwy, fTyz-fTwx, 1.0-(fTxx+fTyy));

		return Radian(ATan2(fTxz+fTwy, 1.0f-(fTxx+fTyy)));

	}
	else
	{
		// internal version
		return Radian(ASin(-2*(x*z - w*y)));
	}
}

bool Quaternion::equals( const Quaternion& rhs, const Radian& tolerance ) const
{
	scalar fCos = Dot(rhs);
	Radian angle = ACos(fCos);

	return (Abs(angle.valueRadians()) <= tolerance.valueRadians())
		|| scalarEqual(angle.valueRadians(),PI, tolerance.valueRadians());


}

Quaternion Quaternion::Slerp( scalar fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath /*= false*/ )
{
	scalar fCos = rkP.Dot(rkQ);
	Quaternion rkT;

	// Do we need to invert rotation?
	if (fCos < 0.0f && shortestPath)
	{
		fCos = -fCos;
		rkT = -rkQ;
	}
	else
	{
		rkT = rkQ;
	}

	if (Abs(fCos) < 1 - ms_fEpsilon)
	{
		// Standard case (slerp)
		scalar fSin = o_sqrt(1 - fCos*fCos);
		Radian fAngle = ATan2(fSin, fCos);
		scalar fInvSin = 1.0f / fSin;
		scalar fCoeff0 = SinR((1.0f - fT) * fAngle) * fInvSin;
		scalar fCoeff1 = SinR(fT * fAngle) * fInvSin;
		return fCoeff0 * rkP + fCoeff1 * rkT;
	}
	else
	{
		// There are two situations:
		// 1. "rkP" and "rkQ" are very close (fCos ~= +1), so we can do a linear
		//    interpolation safely.
		// 2. "rkP" and "rkQ" are almost inverse of each other (fCos ~= -1), there
		//    are an infinite number of possibilities interpolation. but we haven't
		//    have method to fix this case, so just use linear interpolation here.
		Quaternion t = (1.0f - fT) * rkP + fT * rkT;
		// taking the complement requires renormalisation
		t.normalise();
		return t;
	}
}

Quaternion Quaternion::SlerpExtraSpins( scalar fT, const Quaternion& rkP, const Quaternion& rkQ, int iExtraSpins )
{
	scalar fCos = rkP.Dot(rkQ);
	Radian fAngle ( ACos(fCos) );

	if ( Abs(fAngle.valueRadians()) < ms_fEpsilon )
		return rkP;

	scalar fSin = SinR(fAngle);
	Radian fPhase ( PI*iExtraSpins*fT );
	scalar fInvSin = 1.0f/fSin;
	scalar fCoeff0 = SinR((1.0f-fT)*fAngle - fPhase)*fInvSin;
	scalar fCoeff1 = SinR(fT*fAngle + fPhase)*fInvSin;
	return fCoeff0*rkP + fCoeff1*rkQ;
}

void Quaternion::Intermediate( const Quaternion& rkQ0, const Quaternion& rkQ1, const Quaternion& rkQ2, Quaternion& rkA, Quaternion& rkB )
{
	// assert:  q0, q1, q2 are unit quaternions

	Quaternion kQ0inv = rkQ0.UnitInverse();
	Quaternion kQ1inv = rkQ1.UnitInverse();
	Quaternion rkP0 = kQ0inv*rkQ1;
	Quaternion rkP1 = kQ1inv*rkQ2;
	Quaternion kArg = 0.25*(rkP0.Log()-rkP1.Log());
	Quaternion kMinusArg = -kArg;

	rkA = rkQ1*kArg.Exp();
	rkB = rkQ1*kMinusArg.Exp();
}

Quaternion Quaternion::Squad( scalar fT, const Quaternion& rkP, const Quaternion& rkA, const Quaternion& rkB, const Quaternion& rkQ, bool shortestPath /*= false*/ )
{
	scalar fSlerpT = 2.0f*fT*(1.0f-fT);
	Quaternion kSlerpP = Slerp(fT, rkP, rkQ, shortestPath);
	Quaternion kSlerpQ = Slerp(fT, rkA, rkB);
	return Slerp(fSlerpT, kSlerpP ,kSlerpQ);
}

Quaternion Quaternion::nlerp( scalar fT, const Quaternion& rkP, const Quaternion& rkQ, bool shortestPath /*= false*/ )
{
	Quaternion result;
	scalar fCos = rkP.Dot(rkQ);
	if (fCos < 0.0f && shortestPath)
	{
		result = rkP + fT * ((-rkQ) - rkP);
	}
	else
	{
		result = rkP + fT * (rkQ - rkP);
	}
	result.normalise();
	return result;
}
