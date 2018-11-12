#pragma once
#include <exception>
#include "Args.h"

template <typename T>
void Args::MustNotBeNull(T &&arg)
{
	if (arg == nullptr)
		throw new std::exception("Argument must not be null!");
}