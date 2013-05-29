//
// Taylor Petrick
//

#ifndef MATRIX_UTILS_HPP
#define MATRIX_UTILS_HPP

#include "frame.hpp"
#include "matrix4F.hpp"

Matrix4F orthoProjMatrix(F32 pLeft, F32 pRight, F32 pTop, F32 pBottom, F32 pNear, F32 pFar)
{
    Matrix4F proj;
    
    proj.mMatrix[ 0] = 2.0 / (pRight - pLeft);
    proj.mMatrix[ 4] = 0.0;
    proj.mMatrix[ 8] = 0.0;
    proj.mMatrix[12] = 0.0;
    
    proj.mMatrix[ 1] = 0.0;
    proj.mMatrix[ 5] = 2.0 / (pTop - pBottom);
    proj.mMatrix[ 9] = 0.0;
    proj.mMatrix[13] = 0.0;
    
    proj.mMatrix[ 2] = 0.0;
    proj.mMatrix[ 6] = 0.0;
    proj.mMatrix[10] = -2.0 / (pFar - pNear);
    proj.mMatrix[14] = 0.0;
    
    proj.mMatrix[ 3] = -(pRight + pLeft) / (pRight - pLeft);
    proj.mMatrix[ 7] = -(pTop + pBottom) / (pTop - pBottom);
    proj.mMatrix[11] = -(pFar + pNear) / (pFar - pNear);
    proj.mMatrix[15] = 1;
    
    return proj;
}

Matrix4F orthoProjMatrix(const Frame& pFrame)
{
    return orthoProjMatrix(0, pFrame.mWidth, 0, pFrame.mHeight, pFrame.mNear, pFrame.mFar);
}


#endif