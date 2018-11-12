#pragma once
#include "ITexture.h"

namespace ConsoleGL
{

class Texture : public ITexture
{
public:
    Getter(CharInfo *, Data);
    Getter(unsigned, Width);
    Getter(unsigned, Height);
//private:
    CharInfo *data = nullptr;
    int width = 0;
    int height = 0;
};

}