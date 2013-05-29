//
// Taylor Petrick
//

#ifndef MATRIX_HPP
#define MATRIX_HPP

#include <assert.h>
#include "matrix4F.hpp"

/// A node in the matrix stack
struct MatrixNode
{
	///The matrix representation at this level
	Matrix4F	mMatrix;

	///The next node down in the stack
	MatrixNode*	mChild;

	/// Default constructor, leaves the Matrix4F as the indentity and zeros out the child node
	MatrixNode() 
	{
		mChild = 0;
	}

	/// Constructs a matrix node from a Matrix4F instance
	MatrixNode(const Matrix4F& pMatrix)
	{
		mMatrix = pMatrix;
		mChild  = 0;
	}
};

// A matrix stack representation 
class MatrixStack
{

public:
	/// The matrix stack
	MatrixNode* mStack;

public:

	/// Constructs a new stack, with a single node containing the identity matrix
	MatrixStack()
	{
		mStack = new MatrixNode();
	}

	/// Pushes a new node on the stack
	void push() 
	{
		MatrixNode* node = new MatrixNode(mStack->mMatrix);
		node->mChild = mStack;
		mStack = node;
	}

	/// Pops the current node off the stack
	void pop()
	{
		assert(mStack->mChild != 0);

		MatrixNode* top = mStack;
		mStack = top->mChild;
		delete top;
	}

    /// Multiplies a vector by the top of the stack
    Vector4F mult(const Vector4F& pVector, bool pNormal = false)
    {
        return mStack->mMatrix.mult(pVector, pNormal);
    }
    
    
	/// Multiplies the top of the stack by an arbitrary matrix
	void mult(const Matrix4F& pMatrix) 
	{
		mStack->mMatrix = mStack->mMatrix.mult(pMatrix);
	}

	/// Translates the top of the stack by three floats
	void translation(F32 pX, F32 pY, F32 pZ)
	{
		Matrix4F trans;
		trans.translation(pX, pY, pZ);
		mult(trans);
	}

	/// Scales the top of the stack by three floats
	void scale(F32 pX, F32 pY, F32 pZ) 
	{
		Matrix4F scale;
		scale.scale(pX, pY, pZ);
		mult(scale);
	}

	/// Rotates around the X axis
	void rotateX(F32 pAngle)
	{
		Matrix4F rot;
		rot.rotateX(pAngle);
		mult(rot);
	}

	/// Rotates around the Y axis
	void rotateY(F32 pAngle)
	{
		Matrix4F rot;
		rot.rotateY(pAngle);
		mult(rot);
	}

	/// Rotates around the Z axis
	void rotateZ(F32 pAngle)
	{
		Matrix4F rot;
		rot.rotateZ(pAngle);
		mult(rot);
	}
};

#endif