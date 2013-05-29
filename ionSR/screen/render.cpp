
#include "frame.hpp"
#include "matrixUtils.hpp"
#include "render.hpp"


Render::Render(Screen* pScreen, const Frame& pViewPort)
{
    mScreenInst = pScreen;
    mProjection = orthoProjMatrix(pViewPort);
    mViewPort   = pViewPort;
    
    mRenderState.mVertexArray = 0;
    mRenderState.mColorArray  = 0;
    mRenderState.mNormalArray = 0;
    mRenderState.mPixelBuffer = pScreen->getBuffer();
    mRenderState.mZBuffer     = (F32*)malloc(sizeof(F32) * pViewPort.pixCount());
}

Render::~Render()
{
    
}
    
void Render::preRender()
{
    U32 pixelCount = mViewPort.pixCount();
    
    memset(mRenderState.mPixelBuffer, 0, sizeof(U32) * pixelCount);
    for(int i = 0; i<pixelCount; i++)
    {
        mRenderState.mZBuffer[i] = mViewPort.mFar;
    }
}

void Render::postRender()
{
    mScreenInst->display();
}

void Render::setVertexArray(const Vector4F* pArray, U32 pCount, MatrixStack* pStack)
{
    if (mRenderState.mVertexArray == 0)
    {
    
        mRenderState.mVertexArray = (Vector4F*)malloc(sizeof(Vector4F) * pCount);
        mRenderState.mVertexCount = pCount;
    }
    
    for(int i = 0; i<pCount; i++)
    {
        mRenderState.mVertexArray[i] = mProjection.mult(pStack->mult(pArray[i]));
        
        F32 W = mRenderState.mVertexArray[i].mVector[3];
        mRenderState.mVertexArray[i].mVector[0] /= W;
        mRenderState.mVertexArray[i].mVector[1] /= W;
        mRenderState.mVertexArray[i].mVector[2] /= W;
        
        mRenderState.mVertexArray[i].mVector[0] = mViewPort.scaleVert(mRenderState.mVertexArray[i].mVector[0], 0);
        mRenderState.mVertexArray[i].mVector[1] = mViewPort.scaleVert(mRenderState.mVertexArray[i].mVector[1], 1);
        mRenderState.mVertexArray[i].mVector[2] = mViewPort.scaleVert(mRenderState.mVertexArray[i].mVector[2], 2);
    }
}

void Render::setColorArray(Color4I* pArray, U32 pCount)
{
    mRenderState.mColorArray = pArray;
}

void Render::setNormalArray(const Vector4F* pArray, U32 pCount, MatrixStack* pStack)
{
    if(mRenderState.mNormalArray == 0)
    {
        mRenderState.mNormalArray = (Vector4F*)malloc(sizeof(Vector4F) * pCount);
    }
    
    for (int i = 0; i<pCount; i++)
    {
        mRenderState.mNormalArray[i] = pStack->mult(pArray[i], true);
    }
}

F32 Render::triLerp(F32 pW1, F32 pW2, F32 pValue0, F32 pValue1, F32 pValue2)
{
    return pValue0 + pW1*(pValue1 - pValue0) + pW2*(pValue2 - pValue0);
}

Color4I Render::triLerp(F32 pW1, F32 pW2, Color4I pValue0, Color4I pValue1, Color4I pValue2)
{
    U8 red      = pValue0.mRed + pW1*(pValue1.mRed  - pValue0.mRed ) + pW2*(pValue2.mRed  - pValue0.mRed);
    U8 green    = pValue0.mGreen + pW1*(pValue1.mGreen  - pValue0.mGreen ) + pW2*(pValue2.mGreen  - pValue0.mGreen);
    U8 blue     = pValue0.mBlue  + pW1*(pValue1.mBlue  - pValue0.mBlue ) + pW2*(pValue2.mBlue  - pValue0.mBlue);

    return Color4I(red,green,blue);
}


void Render::renderArray()
{
    for(int i = 0; i<mRenderState.mVertexCount; i+=3)
    {
        Vector4F v0 = mRenderState.mVertexArray[i+0];
        Vector4F v1 = mRenderState.mVertexArray[i+1];
        Vector4F v2 = mRenderState.mVertexArray[i+2];
        
        Vector4F n0 = mRenderState.mNormalArray[i+0];
        Vector4F n1 = mRenderState.mNormalArray[i+1];
        Vector4F n2 = mRenderState.mNormalArray[i+2];
        
        F32 l0 = n0.mVector[0] * -1 + n0.mVector[1] * -0.0 + n0.mVector[2] * -0.5;
        F32 l1 = n1.mVector[0] * -1 + n1.mVector[1] * -0.0 + n1.mVector[2] * -0.5;
        F32 l2 = n2.mVector[0] * -1 + n2.mVector[1] * -0.0 + n2.mVector[2] * -0.5;
        
        Color4I c0  = mRenderState.mColorArray[i+0];
        Color4I c1  = mRenderState.mColorArray[i+1];
        Color4I c2  = mRenderState.mColorArray[i+2];
        
        F32 minX = min3(v0.mVector[0], v1.mVector[0], v2.mVector[0]);
        F32 minY = min3(v0.mVector[1], v1.mVector[1], v2.mVector[1]);
        
        F32 maxX = max3(v0.mVector[0], v1.mVector[0], v2.mVector[0]);
        F32 maxY = max3(v0.mVector[1], v1.mVector[1], v2.mVector[1]);
        
        minX = max(minX, 0.0f);
        minY = max(minY, 0.0f);
        maxX = min(maxX, 1.0f*(mViewPort.mWidth-1));
        maxY = min(maxY, 1.0f*(mViewPort.mHeight-1));
        
        F32 A01 = v0.mVector[1] - v1.mVector[1], B01 = v1.mVector[0] - v0.mVector[0];
        F32 A12 = v1.mVector[1] - v2.mVector[1], B12 = v2.mVector[0] - v1.mVector[0];
        F32 A20 = v2.mVector[1] - v0.mVector[1], B20 = v0.mVector[0] - v2.mVector[0];
        
        F32 w0_row = (v2.mVector[0] - v1.mVector[0]) * (minY-v1.mVector[1]) - (v2.mVector[1] - v1.mVector[1])*(minX-v1.mVector[0]);
        F32 w1_row = (v0.mVector[0] - v2.mVector[0]) * (minY-v2.mVector[1]) - (v0.mVector[1] - v2.mVector[1])*(minX-v2.mVector[0]);
        F32 w2_row = (v1.mVector[0] - v0.mVector[0]) * (minY-v0.mVector[1]) - (v1.mVector[1] - v0.mVector[1])*(minX-v0.mVector[0]);
        
        F32 area   = (v1.mVector[0] - v0.mVector[0]) * (v2.mVector[1]-v0.mVector[1]) - (v1.mVector[1] - v0.mVector[1])*(v2.mVector[0]-v0.mVector[0]);
        
        for(F32 y= minY; y<=(maxY+0.5); y+=1.0f)
        {
            F32 w0 = w0_row;
            F32 w1 = w1_row;
            F32 w2 = w2_row;
            
            for(F32 x= minX; x<=(maxX+0.5); x+=1.0f)
            {
                
                if((w0 >= 0 && w1 >= 0 && w2 >= 0) || (w0 <= 0 && w1 <= 0 && w2 <= 0))
                {
                    int xcoord = x;
                    int ycoord = y;
                    int index = xcoord + ycoord*mViewPort.mWidth;
                    
                    F32 z = triLerp(w1/area, w2/area, v0.mVector[2], v1.mVector[2], v2.mVector[2]);
                    if(z <= mRenderState.mZBuffer[index])
                    {
                        mRenderState.mZBuffer[index] = z;
                        F32 light = triLerp(w1/area, w2/area, l0, l1, l2) * 100;
                        Color4I c = triLerp(w1/area, w2/area, c0, c1, c2);
                        
                        c.mRed = min(max((float)c.mRed + light,0),245) + 10;
                        c.mBlue = min(max((float)c.mBlue + light,0),245) + 10;
                        c.mGreen = min(max((float)c.mGreen + light,0),245) + 10;
                        
                        mRenderState.mPixelBuffer[index] = c.toInteger();
                    }
                }
                
                w0 += A12;
                w1 += A20;
                w2 += A01;
            }
            
            w0_row += B12;
            w1_row += B20;
            w2_row += B01;
        }
    }
}
