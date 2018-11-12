#pragma once
#include "ConsoleGfx.h"

namespace ConsoleGL
{
class ITexture
{
public:
    IGetter(CharInfo *, Data);
    PropertyR(CharInfo *, Data);

    IGetter(unsigned, Width);
    PropertyR(unsigned, Width);

    IGetter(unsigned, Height);
    PropertyR(unsigned, Height);
};
}