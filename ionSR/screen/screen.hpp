//
// Taylor Petrick
//

#ifndef SCREEN_HPP
#define SCREEN_HPP

#include <SDL/SDL.h>
#include "types.hpp"

/// A simple screen handler, for passing buffered pixel data to an SDL surface
class Screen
{
    
private:
    
    /// The buffer containing pixels to be pushed on the next diplay call
    U32*            mBuffer;
    
    /// The SDL surface to display to
    SDL_Surface*    mSurface;
    
    /// The screen width
    U32             mWidth;
    
    /// The screen height
    U32             mHeight;
    
public:
    
    /// Default constructor, which creates a screen of size 512x512
    Screen();
    
    /// Constructor that creates a screen of a given size
    Screen(U32 pWidth, U32 pHeight);
    
    /// Destructor
    ~Screen();
    
    
    /// Returns the buffer pointer
    U32* getBuffer() const;
    
    /// Displays the buffer to the SDL surface
    void display() const;
};

#endif 
