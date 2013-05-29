//
// Taylor Petrick
//

#ifndef FRAME_RATE_HPP
#define FRAME_RATE_HPP

#include <SDL/SDL.h>
#include "types.hpp"

#define kFrameSamples 10

/// A utility for measuring frame rate of an SDL application
class FrameRate
{
    
private:
    /// The frames in the current sample
    U32 mFrameTimes[kFrameSamples];
    
    /// The last rendered frame
    U32 mFrameLast;
    
    /// The total rendered frames
    U32 mFrameCount;
    
    /// The actual frame rate
    F32 mFrameRate;
    
public:
    
    /// Constructor
    FrameRate()
    {
        memset(mFrameTimes, 0, sizeof(mFrameTimes));
        
        mFrameCount = 0;
        mFrameRate  = 0.0f;
        mFrameLast  = SDL_GetTicks();
    }
    
    /// Tick the current frame rate, called once per frame
    void tickRate()
    {
        U32 frameIndex = mFrameCount % kFrameSamples;
        U32 ticks = SDL_GetTicks();
        
        mFrameTimes[frameIndex] = ticks - mFrameLast;
        mFrameLast = ticks;
        mFrameCount++;
        
        U32 count;
        
        if (mFrameCount < kFrameSamples)
        {
            count = mFrameCount;
        }
        else
        {
            count = kFrameSamples;
        }

        mFrameRate = 0.0f;
        for (U32 i = 0; i < count; i++)
        {
            mFrameRate += mFrameTimes[i];
        }
        
        mFrameRate /= count;
        mFrameRate  = 1000.f / mFrameRate;
    }
    
    /// Returns the current calculated framerate
    F32 getRate()
    {
        return mFrameRate;
    }
};

#endif