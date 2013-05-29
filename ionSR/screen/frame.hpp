//
// Taylor Petrick
//

#ifndef FRAME_HPP
#define FRAME_HPP

#include <assert.h>

#include "types.hpp"

/// A simple frame structure for describing the view bounds of a screen
struct Frame
{
    /// The width
    U32 mWidth;
    
    /// The half width
    U32 mHalfWidth;
    
    
    /// The height
    U32 mHeight;
    
    /// The half height
    U32 mHalfHeight;
    
    
    /// The near plane
    F32 mNear;
    
    /// The far plane
    F32 mFar;
    
    
    /// The half depth
    F32 mHalfDepth;
    
    
    /// Constructs a default frame
    Frame()
    {
        mWidth      = 100;
        mHalfWidth  = 50;
        mHeight     = 100;
        mHalfHeight = 50;
        
        mNear       = 0.0f;
        mFar        = 100.0f;
        mHalfDepth  = 50.0f;
    }
    
    /// Constructs a frame of a given size and depth
    Frame(S32 pWidth, S32 pHeight, F32 pNear, F32 pFar)
    {
        mWidth      = pWidth;
        mHalfWidth  = pWidth/2;
        mHeight     = pHeight;
        mHalfHeight = pHeight/2;
        
        mNear       = pNear;
        mFar        = pFar;
        mHalfDepth  = (pFar - pNear)/2.0f;
    }
    
    /// The total pixel count
    S32 pixCount() const
    {
        return mWidth * mHeight;
    }
    
    /// Scales a vertex into view port space coordinates (window coordinates)
    F32 scaleVert(F32 pVert, int pFlag) const
    {
        switch(pFlag)
        {
            case 0:
            {
                return (pVert + 1.0f) * mHalfWidth;
            }
            case 1:
            {
                return (pVert + 1.0f) * mHalfHeight;
            }
            case 2:
            {
                return (pVert + 1.0f) * mHalfDepth;
            }
            default:
            {
                assert(false);
                return 0.0f;
            }
        }
    }
};

#endif