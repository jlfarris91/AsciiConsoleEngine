#pragma once

class Args
{
public:

	template <typename T>
	static void MustNotBeNull(T &&arg);
};

#include "Args.inl"