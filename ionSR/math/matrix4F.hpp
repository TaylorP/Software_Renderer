//
// Taylor Petrick
// 

#ifndef MATRIX_4F_HPP
#define MATRIX_4F_HPP

#include <math.h>
#include <Accelerate/Accelerate.h>
#include "mathUtils.hpp"
#include "types.hpp"
#include "vector4F.hpp"

/// Struct for containing a 4x4 transform matrix
struct Matrix4F 
{
	/// Column major matrix representation
	F32 mMatrix[16];

	/// Default constructor, returns the indentity matrix
	Matrix4F() 
	{
		mMatrix[ 0] = 1.0;	mMatrix[ 1] = 0.0;	mMatrix[ 2] = 0.0;	mMatrix[ 3] = 0.0;
		mMatrix[ 4] = 0.0;	mMatrix[ 5] = 1.0;	mMatrix[ 6] = 0.0;	mMatrix[ 7] = 0.0;
		mMatrix[ 8] = 0.0;	mMatrix[ 9] = 0.0;	mMatrix[10] = 1.0;	mMatrix[11] = 0.0;
		mMatrix[12] = 0.0;	mMatrix[13] = 0.0;	mMatrix[14] = 0.0;	mMatrix[15] = 1.0;
	}

	/// Constructs a translation matrix - note the matrix this is called on should be identity
	void translation(F32 pX, F32 pY, F32 pZ) 
	{
		mMatrix[ 3] = pX;
		mMatrix[ 7] = pY;
		mMatrix[11] = pZ;
	}

	/// Constructs a scaling matrix - ibid
	void scale(F32 pX, F32 pY, F32 pZ) 
	{
		mMatrix[ 0] = pX;
		mMatrix[ 5] = pY;
		mMatrix[10] = pZ;
	}

	void rotateX(F32 pAngle) 
	{
		pAngle = pAngle * PI / 180.0f;

		F32 cosTheta = cosf(pAngle);
		F32 sinTheta = sinf(pAngle);

		mMatrix[ 5] =  cosTheta;
        mMatrix[ 6] = -sinTheta;
		mMatrix[ 9] =  sinTheta;
		mMatrix[10] =  cosTheta;
	}

	void rotateY(F32 pAngle) 
	{
		pAngle = pAngle * PI / 180.0f;

		F32 cosTheta = cosf(pAngle);
		F32 sinTheta = sinf(pAngle);

		mMatrix[ 0] =  cosTheta;
		mMatrix[ 2] =  sinTheta;
		mMatrix[ 8] = -sinTheta;
		mMatrix[10] =  cosTheta;
	}

	void rotateZ(F32 pAngle) 
	{
		pAngle = pAngle * PI / 180.0f;

		F32 cosTheta = cosf(pAngle);
		F32 sinTheta = sinf(pAngle);

		mMatrix[ 0] =  cosTheta;
		mMatrix[ 1] = -sinTheta;
		mMatrix[ 4] =  sinTheta;
		mMatrix[ 5] =  cosTheta;
	}

	/// Multiplies this matrix by pMatrix in the order (this * pMatrix) and returns the result
	Matrix4F mult(const Matrix4F& pMatrix) const 
	{
		Matrix4F result;

		result.mMatrix[ 0] = (mMatrix[ 0] * pMatrix.mMatrix[ 0]) + (mMatrix[ 1] * pMatrix.mMatrix[ 4]) + (mMatrix[ 2] * pMatrix.mMatrix[ 8]) + (mMatrix[ 3] * pMatrix.mMatrix[12]);
		result.mMatrix[ 4] = (mMatrix[ 4] * pMatrix.mMatrix[ 0]) + (mMatrix[ 5] * pMatrix.mMatrix[ 4]) + (mMatrix[ 6] * pMatrix.mMatrix[ 8]) + (mMatrix[ 7] * pMatrix.mMatrix[12]);
		result.mMatrix[ 8] = (mMatrix[ 8] * pMatrix.mMatrix[ 0]) + (mMatrix[ 9] * pMatrix.mMatrix[ 4]) + (mMatrix[10] * pMatrix.mMatrix[ 8]) + (mMatrix[11] * pMatrix.mMatrix[12]);
		result.mMatrix[12] = (mMatrix[12] * pMatrix.mMatrix[ 0]) + (mMatrix[13] * pMatrix.mMatrix[ 4]) + (mMatrix[14] * pMatrix.mMatrix[ 8]) + (mMatrix[15] * pMatrix.mMatrix[12]);

		result.mMatrix[ 1] = (mMatrix[ 0] * pMatrix.mMatrix[ 1]) + (mMatrix[ 1] * pMatrix.mMatrix[ 5]) + (mMatrix[ 2] * pMatrix.mMatrix[ 9]) + (mMatrix[ 3] * pMatrix.mMatrix[13]);
		result.mMatrix[ 5] = (mMatrix[ 4] * pMatrix.mMatrix[ 1]) + (mMatrix[ 5] * pMatrix.mMatrix[ 5]) + (mMatrix[ 6] * pMatrix.mMatrix[ 9]) + (mMatrix[ 7] * pMatrix.mMatrix[13]);
		result.mMatrix[ 9] = (mMatrix[ 8] * pMatrix.mMatrix[ 1]) + (mMatrix[ 9] * pMatrix.mMatrix[ 5]) + (mMatrix[10] * pMatrix.mMatrix[ 9]) + (mMatrix[11] * pMatrix.mMatrix[13]);
		result.mMatrix[13] = (mMatrix[12] * pMatrix.mMatrix[ 1]) + (mMatrix[13] * pMatrix.mMatrix[ 5]) + (mMatrix[14] * pMatrix.mMatrix[ 9]) + (mMatrix[15] * pMatrix.mMatrix[13]);

		result.mMatrix[ 2] = (mMatrix[ 0] * pMatrix.mMatrix[ 2]) + (mMatrix[ 1] * pMatrix.mMatrix[ 6]) + (mMatrix[ 2] * pMatrix.mMatrix[10]) + (mMatrix[ 3] * pMatrix.mMatrix[14]);
		result.mMatrix[ 6] = (mMatrix[ 4] * pMatrix.mMatrix[ 2]) + (mMatrix[ 5] * pMatrix.mMatrix[ 6]) + (mMatrix[ 6] * pMatrix.mMatrix[10]) + (mMatrix[ 7] * pMatrix.mMatrix[14]);
		result.mMatrix[10] = (mMatrix[ 8] * pMatrix.mMatrix[ 2]) + (mMatrix[ 9] * pMatrix.mMatrix[ 6]) + (mMatrix[10] * pMatrix.mMatrix[10]) + (mMatrix[11] * pMatrix.mMatrix[14]);
		result.mMatrix[14] = (mMatrix[12] * pMatrix.mMatrix[ 2]) + (mMatrix[13] * pMatrix.mMatrix[ 6]) + (mMatrix[14] * pMatrix.mMatrix[10]) + (mMatrix[15] * pMatrix.mMatrix[14]);

		result.mMatrix[ 3] = (mMatrix[ 0] * pMatrix.mMatrix[ 3]) + (mMatrix[ 1] * pMatrix.mMatrix[ 7]) + (mMatrix[ 2] * pMatrix.mMatrix[11]) + (mMatrix[ 3] * pMatrix.mMatrix[15]);
		result.mMatrix[ 7] = (mMatrix[ 4] * pMatrix.mMatrix[ 3]) + (mMatrix[ 5] * pMatrix.mMatrix[ 7]) + (mMatrix[ 6] * pMatrix.mMatrix[11]) + (mMatrix[ 7] * pMatrix.mMatrix[15]);
		result.mMatrix[11] = (mMatrix[ 8] * pMatrix.mMatrix[ 3]) + (mMatrix[ 9] * pMatrix.mMatrix[ 7]) + (mMatrix[10] * pMatrix.mMatrix[11]) + (mMatrix[11] * pMatrix.mMatrix[15]);
		result.mMatrix[15] = (mMatrix[12] * pMatrix.mMatrix[ 3]) + (mMatrix[13] * pMatrix.mMatrix[ 7]) + (mMatrix[14] * pMatrix.mMatrix[11]) + (mMatrix[15] * pMatrix.mMatrix[15]);

		return result;
	}

    /// Multiplies a vector by this matrix and returns the resulting vector
	Vector4F mult(const Vector4F& pVector, bool pNormal = false) const
	{
		Vector4F result;
        
        /*result.mVector[0] = (mMatrix[ 0] * pVector.mVector[0]) + (mMatrix[ 1] * pVector.mVector[1]) + (mMatrix[ 2] * pVector.mVector[2]) + (mMatrix[ 3] * pVector.mVector[3]);
        result.mVector[1] = (mMatrix[ 4] * pVector.mVector[0]) + (mMatrix[ 5] * pVector.mVector[1]) + (mMatrix[ 6] * pVector.mVector[2]) + (mMatrix[ 7] * pVector.mVector[3]);
        result.mVector[2] = (mMatrix[ 8] * pVector.mVector[0]) + (mMatrix[ 9] * pVector.mVector[1]) + (mMatrix[10] * pVector.mVector[2]) + (mMatrix[11] * pVector.mVector[3]);
        result.mVector[3] = (mMatrix[12] * pVector.mVector[0]) + (mMatrix[13] * pVector.mVector[1]) + (mMatrix[14] * pVector.mVector[2]) + (mMatrix[15] * pVector.mVector[3]);
        */
        __m128 vec = _mm_loadu_ps(pVector.mVector);
        
        __m128 r1 = _mm_mul_ps(_mm_loadu_ps(mMatrix), vec);
        __m128 t = _mm_add_ps(r1, _mm_movehl_ps(r1, r1));
        __m128 sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
        _mm_store_ss(result.mVector, sum);
    
        r1 = _mm_mul_ps(_mm_loadu_ps(mMatrix+4), vec);
        t = _mm_add_ps(r1, _mm_movehl_ps(r1, r1));
        sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
        _mm_store_ss(result.mVector+1, sum);
        
        r1 = _mm_mul_ps(_mm_loadu_ps(mMatrix+8), vec);
        t = _mm_add_ps(r1, _mm_movehl_ps(r1, r1));
        sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
        _mm_store_ss(result.mVector+2, sum);
        
        r1 = _mm_mul_ps(_mm_loadu_ps(mMatrix+12), vec);
        t = _mm_add_ps(r1, _mm_movehl_ps(r1, r1));
        sum = _mm_add_ss(t, _mm_shuffle_ps(t, t, 1));
        _mm_store_ss(result.mVector+3, sum);

		return result;
	}
};

#endif