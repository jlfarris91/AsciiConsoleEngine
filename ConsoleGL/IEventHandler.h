#pragma once
#include "ConsoleGfx.h"

namespace ConsoleGL
{

class IEventHandler
{
public:
	virtual void Handle(const INPUT_RECORD *message) = 0;
};

}