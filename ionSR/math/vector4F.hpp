//
// Taylor Petrick
//

#ifndef VECTOR_4F_HPP
#define VECTOR_4F_HPP

#include "types.hpp"

/// A four component vector structure
struct Vector4F 
{
    F32 mVector[4];
    
    /// Constructs a vector with all 3 components 0 and the w component at 1
	Vector4F() 
	{
		mVector[0] = 0.0f;
		mVector[1] = 0.0f;
		mVector[2] = 0.0f;
		mVector[3] = 1.0f;
	}
    
    /// Constructs a vector from three floats
	Vector4F(F32 pX, F32 pY, F32 pZ)
	{
		mVector[0] = pX;
		mVector[1] = pY;
		mVector[2] = pZ;
		mVector[3] = 1.0f;
	}
    
    /// Constructs a vector from four floats
	Vector4F(F32 pX, F32 pY, F32 pZ, F32 pW)
	{
		mVector[0] = pX;
		mVector[1] = pY;
		mVector[2] = pZ;
		mVector[3] = pW;
	}
    
};

#endif