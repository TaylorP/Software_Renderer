//
// Taylor Petrick
//

#include "screen.hpp"

Screen::Screen()
{
    mWidth  = 512;
    mHeight = 512;
    
    mBuffer = (U32*)malloc(sizeof(U32) * 512 * 512);
    
    mSurface = SDL_SetVideoMode(512, 512, 32, SDL_SWSURFACE);
}

Screen::Screen(U32 pWidth, U32 pHeight)
{
    mWidth  = pWidth;
    mHeight = pHeight;
    
    mBuffer = (U32*)malloc(sizeof(U32) * mWidth * mHeight);
    
    mSurface = SDL_SetVideoMode(mWidth, mHeight, 32, SDL_SWSURFACE);
}
    
Screen::~Screen()
{
    if(mBuffer)
    {
        free(mBuffer);
    }
}

U32* Screen::getBuffer() const
{
    return mBuffer;
}
    
void Screen::display() const
{
    if(SDL_MUSTLOCK(mSurface))
    {
        SDL_LockSurface(mSurface);
    }
    
    memcpy(mSurface->pixels, mBuffer, mWidth*mHeight*sizeof(U32));
    
    if(SDL_MUSTLOCK(mSurface))
    {
        SDL_UnlockSurface(mSurface);
    }
    
    SDL_Flip(mSurface);
}