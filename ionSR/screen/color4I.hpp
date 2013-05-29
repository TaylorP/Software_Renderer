//
// Taylor Petrick
//

#ifndef COLOR_4I_HPP
#define COLOR_4I_HPP

#include "types.hpp"

/// A color consistening of a four unsigned 8 bit values
struct Color4I
{
    /// The red value
    U8  mRed;
    
    /// The green value
    U8  mGreen;
    
    /// The blue value
    U8  mBlue;
    
    /// The alpha value
    U8  mAlpha;
    
    
    /// Default constructor, creates a black color
    Color4I()
    {
        mRed    = 0x00;
        mGreen  = 0x00;
        mBlue   = 0x00;
        mAlpha  = 0xFF;
    }
    
    /// Constructs a color from three 8 bit values, assumes alpha is 0xFF
    Color4I(U8 pRed, U8 pGreen, U8 pBlue)
    {
        mRed    = pRed;
        mGreen  = pGreen;
        mBlue   = pBlue;
        mAlpha  = 0xFF;
    }
    
    /// Constructs a color from four 8 bit values
    Color4I(U8 pRed, U8 pGreen, U8 pBlue, U8 pAlpha)
    {
        mRed    = pRed;
        mGreen  = pGreen;
        mBlue   = pBlue;
        mAlpha  = pAlpha;
    }

    /// Returns the 32 bit representation of this color
    U32 toInteger()
    {
        return ((U32)mAlpha) + ((U32)mRed << 8) + ((U32)mGreen << 16) + ((U32)mBlue << 24);
    }
};

#endif
