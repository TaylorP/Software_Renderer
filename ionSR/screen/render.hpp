//
// Taylor Petrick
//

#ifndef RENDER_HPP
#define RENDER_HPP

#include "color4I.hpp"
#include "matrixStack.hpp"
#include "screen.hpp"
#include "vector4F.hpp"


/// The current render state and data, including settings and buffers
struct RenderState
{
    /// The pixel buffer
    U32*        mPixelBuffer;
    
    
    /// The current vertex array
    Vector4F*   mVertexArray;
    
    /// The current normal array
    Vector4F*   mNormalArray;
    
    /// The current vertex colors
    Color4I*    mColorArray;
    
    
    /// The size of the vertex array
    U32         mVertexCount;
    
    
    /// The z-buffer, for depth sorting
    F32*        mZBuffer;
};


/// The main renderer class. Does the rasterization of triangles and processes vertex attributes
class Render
{
    
private:
    
    /// A reference to the screen to render to
    Screen* mScreenInst;

    /// The render state
    RenderState mRenderState;
    
    /// The current projection matrix
    Matrix4F    mProjection;
    
    /// The current view port
    Frame       mViewPort;
    
    /// Interpolate a float paramter on three verticies. Uses barycentric coordinate properties to assume the value of W0.
    F32 triLerp(F32 pW1, F32 pW2, F32 pValue0, F32 pValue1, F32 pValue2);
    
    /// Interploate a Color4F paramter on three verticies.
    Color4I triLerp(F32 pW1, F32 pW2, Color4I pValue0, Color4I pValue1, Color4I pValue2);
    
public:
    
    /// Constructs a render instances
    Render(Screen* pScreen, const Frame& pViewPort);
    
    /// Destructor
    ~Render();
    
    
    /// Starts the renderer, called at the beginning of a frame
    void preRender();
    
    /// Stops the renderer and displays the content to the screen, at the end of a frame
    void postRender();
    
    
    /// Sets the current vertex buffer
    void setVertexArray(const Vector4F* pArray, U32 pCount, MatrixStack* pStack);
    
    /// Sets the current color buffer
    void setColorArray(Color4I* pArray, U32 pCount);
    
    /// Sets the current normal buffer
    void setNormalArray(const Vector4F* pArray, U32 pCount, MatrixStack* pStack);
    
    /// Renders the current vertex array
    void renderArray();
    
};
#endif