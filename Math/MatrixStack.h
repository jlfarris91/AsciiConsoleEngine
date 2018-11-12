/******************************************************************************/
/*!
\file   MatrixStack.h
\author James Farris
\par    email: james.farris@digipen.edu
\date   07/05/2013\n\n
\brief  Precompiled header file, should hold any code that won't change, and will
        increase compile times.

example:


{
	MatrixStack mtxStack;
	Mtx44 finalMtx;

	// ... input matrices starting with parents

	const Matrix4 &world = mtxStack.top();
	Matrix4::ToMtx44(world, finalMtx);
	GXLoadPosMtxImm(finalMtz, GX_PNMXT0);

	// draw calls
}

*/
/******************************************************************************/
//Copyright 2013, Digipen Institute of Technology
#pragma once
#include "Matrix4.h"
#include <stack>

class MatrixStack
{
public:
	typedef std::stack<Matrix4> stack_type;
	MatrixStack();
	void push(const Matrix4 &mtx);
	void pop();
	const Matrix4 &top();
	stack_type::size_type size();
	void clear();
	bool empty();
private:
	stack_type stack;
};