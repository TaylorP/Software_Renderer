//
//  main.cpp
//  ionSR
//
//  Created by Taylor Petrick on 2013-03-07.
//  Copyright (c) 2013 Orange Bytes. All rights reserved.
//

#include <SDL/SDL.h>
#include "SDLMain.h"

#include "frame.hpp"
#include "frameRate.hpp"
#include "render.hpp"
#include "screen.hpp"

#include "color4I.hpp"
#include "mathUtils.hpp"
#include "matrixStack.hpp"
#include "vector4F.hpp"


/// A holder for SDL events
SDL_Event event;

/// A screen instance for rendering
Screen* gScreen;

/// A frame rate measurer instance
FrameRate* gFrameRate;

/// A frame describing the view port
Frame gViewPort(512, 512, 0.0f, 512.0f);

/// The main renderer
Render* gRender;

/// The main loop
int main(int argc, char *argv[])
{
    SDL_Init(SDL_INIT_VIDEO);
    
    gScreen     = new Screen(gViewPort.mWidth, gViewPort.mHeight);
    gRender     = new Render(gScreen, gViewPort);
    gFrameRate  = new FrameRate();
    
    SDL_WM_SetCaption("ionSR version 0.2", "ionSR version 0.2");

    const int vertCount = 36;

    Vector4F verts[vertCount] = {
        {-100.0f,-100.0f,100.0f}, {100.0f,-100.0f,100.0f}, {-100.0f,100.0f,100.0f}, {100.0f,-100.0f,100.0f}, {-100.0f,100.0f,100.0f}, {100.0f,100.0f,100.0f},
        {100.0f,-100.0f,100.0f}, {100.0f,-100.0f,-100.0f}, {100.0f,100.0f,100.0f}, {100.0f,-100.0f,-100.0f}, {100.0f,100.0f,100.0f}, {100.0f,100.0f,-100.0f},
        {100.0f,-100.0f,-100.0f}, {-100.0f,-100.0f,-100.0f}, {100.0f,100.0f,-100.0f}, {-100.0f,-100.0f,-100.0f}, {100.0f,100.0f,-100.0f}, {-100.0f,100.0f,-100.0f},
        {-100.0f,-100.0f,-100.0f}, {-100.0f,-100.0f,100.0f}, {-100.0f,100.0f,-100.0f}, {-100.0f,-100.0f,100.0f}, {-100.0f,100.0f,-100.0f}, {-100.0f,100.0f,100.0f},
        {-100.0f,-100.0f,-100.0f}, {100.0f,-100.0f,-100.0f}, {-100.0f,-100.0f,100.0f}, {100.0f,-100.0f,-100.0f}, {-100.0f,-100.0f,100.0f}, {100.0f,-100.0f,100.0f},
        {-100.0f,100.0f,100.0f}, {100.0f,100.0f,100.0f}, {-100.0f,100.0f,-100.0f}, {100.0f,100.0f,100.0f}, {-100.0f,100.0f,-100.0f}, {100.0f,100.0f,-100.0f}
    };
    
    Vector4F norms[vertCount] = {
        {-0.57735f,-0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,0.57735f,0.0f}, {0.57735f,0.57735f,0.57735f,0.0f},
        {0.57735f,-0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,0.57735f,0.0f}, {0.57735f,0.57735f,-0.57735f,0.0f},
        {0.57735f,-0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,-0.57735f,0.0f}, {-0.57735f,0.57735f,-0.57735f,0.0f},
        {-0.57735f,-0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,-0.57735f,0.0f}, {-0.57735f,0.57735f,0.57735f,0.0f},
        {-0.57735f,-0.57735f,-0.57735f,0.0f}, {0.57735f,-0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,-0.57735f,0.0f}, {-0.57735f,-0.57735f,0.57735f,0.0f}, {0.57735f,-0.57735f,0.57735f,0.0f},
        {-0.57735f,0.57735f,0.57735f,0.0f}, {0.57735f,0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,0.57735f,0.0f}, {-0.57735f,0.57735f,-0.57735f,0.0f}, {0.57735f,0.57735f,-0.57735f,0.0f}
    };
    
    Color4I colors[vertCount] = {
        {0xFF, 0x99, 0x00}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33},
        {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x88, 0x33, 0x88},
        {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x88, 0x33, 0x88}, {0x33, 0x33, 0x33}, {0x88, 0x33, 0x88}, {0x33, 0x33, 0x33},
        {0x33, 0x33, 0x33}, {0xFF, 0x99, 0x00}, {0x33, 0x33, 0x33}, {0xFF, 0x99, 0x00}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33},
        {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0xFF, 0x99, 0x00}, {0x33, 0x33, 0x33}, {0xFF, 0x99, 0x00}, {0x33, 0x33, 0x33},
        {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x33, 0x33, 0x33}, {0x88, 0x33, 0x88}
    };
    
    MatrixStack* mMatrixStack = new MatrixStack();

    bool done=false;
    bool down = false;
    int x = 0;
    int y = 0;
    
    while(!done)
    {
        while(SDL_PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
            {
                done=true;
            }
            
            else if (event.type == SDL_MOUSEMOTION && down)
            {
                y += event.motion.yrel;
                x += event.motion.xrel;
            }
            else if (event.type == SDL_MOUSEBUTTONDOWN)
            {
                down = true;
            }
            else if (event.type == SDL_MOUSEBUTTONUP)
            {
                down = false;
            }
        }
        
        gRender->preRender();
        
        mMatrixStack->push();
        mMatrixStack->translation(250, 250, 10);
        mMatrixStack->rotateY(x);
        mMatrixStack->rotateX(y);
        
        gRender->setVertexArray(verts, vertCount, mMatrixStack);
        gRender->setColorArray(colors, vertCount);
        gRender->setNormalArray(norms, vertCount, mMatrixStack);
        gRender->renderArray();
        
        gRender->postRender();
        gFrameRate->tickRate();
        
        printf("%f\n", gFrameRate->getRate());
        mMatrixStack->pop();
    }

    SDL_Quit();
    
    return 0;
}
