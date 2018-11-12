/******************************************************************************/
/*!
\file   MatrixStack.cpp
\author James Farris
\par    email: james.farris@digipen.edu
\date   07/05/2013\n\n
\brief  Precompiled header file, should hold any code that won't change, and will
        increase compile times.
*/
/******************************************************************************/
//Copyright 2013, Digipen Institute of Technology
#include "MatrixStack.h"

MatrixStack::MatrixStack()
{
	stack.push(Matrix4());
}

void MatrixStack::push(const Matrix4 &mtx)
{
	stack.push(stack.top() * mtx);
}

void MatrixStack::pop()
{
	if (stack.size() > 1)
		stack.pop();
}

const Matrix4 &MatrixStack::top()
{
	return stack.top();
}

MatrixStack::stack_type::size_type MatrixStack::size()
{
	return stack.size();
}

void MatrixStack::clear()
{
	while (stack.size() > 1)
		stack.pop();
}

bool MatrixStack::empty()
{
	return stack.empty();
}