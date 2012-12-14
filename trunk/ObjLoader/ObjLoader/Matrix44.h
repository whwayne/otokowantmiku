#pragma once
#include "MathDefine.h"

class matrix44
{
public:
	matrix44();
	matrix44(
		scalar m00,scalar m01,scalar m02,scalar m03,
		scalar m10,scalar m11,scalar m12,scalar m13,	 
		scalar m20,scalar m21,scalar m22,scalar m23,
		scalar m30,scalar m31,scalar m32,scalar m33,
			);
	matrix44(float4[4]& row);
	matrix44(matrix44& m44);



protected:
private:
	float4[4] mRow;
};

matrix44::matrix44()
	:mRow[0](float4(1.0f,0.0f,0.0f,0.0f))
	,mRow[1](float4(0.0f,1.0f,0.0f,0.0f))
	,mRow[2](float4(0.0f,0.0f,1.0f,0.0f))
	,mRow[3](float4(0.0f,0.0f,0.0f,1.0f))
{

}

matrix44::matrix44( scalar m00,scalar m01,scalar m02,scalar m03, 
				   scalar m10,scalar m11,scalar m12,scalar m13, 
				   scalar m20,scalar m21,scalar m22,scalar m23, 
				   scalar m30,scalar m31,scalar m32,scalar m33, )
				   :mRow[0](float4(m00,m01,m02,m03))
				   ,mRow[1](float4(m10,m11,m12,m13))
				   ,mRow[2](float4(m20,m21,m22,m23))
				   ,mRow[3](float4(m30,m31,m32,m33))
{

}

matrix44::matrix44( float4[4]& row )
				:mRow[0](row[0])
				,mRow[1](row[0])
				,mRow[2](row[0])
				,mRow[3](row[0])
{

}

matrix44::matrix44( matrix44& m44 )
				:mRow(m44.mRow)
{

}
