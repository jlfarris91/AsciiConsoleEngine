#include "Buffer.h"
#include "RenderUtility.h"

namespace ConsoleGL
{
//----------------------------------------------------------------------- Buffer
//******************************************************************************
Buffer::Buffer(uint width, uint height)
    :data(NULL)
{
    alphaMask = RenderUtility::sDefaultAlphaMask;
    Resize(width, height);
}

//******************************************************************************
Buffer::Buffer(Size size)
    : data(NULL)
{
    alphaMask = RenderUtility::sDefaultAlphaMask;
    Resize(Split2(size));
}

//******************************************************************************
Buffer::~Buffer()
{
    SafeArrayDelete(data);
}

//******************************************************************************
void Buffer::Resize(uint width, uint height)
{
    Release();
    if (width > 0 && height > 0)
    {
        data = new CharInfo[width * height];
    }
    this->width = width;
    this->height = height;
}

//******************************************************************************
void Buffer::Clear(Char c, CharAttr attr)
{
    uint length = width * height;
    for (uint i = 0; i < length; ++i)
    {
        CharInfo &ci = data[i];
        ci.Char.AsciiChar = c;
        ci.Attributes = attr;
    }
}

//******************************************************************************
bool Buffer::InBounds(uint x, uint y) const
{
    return x >= 0 && x < width &&
        y >= 0 && y < height;
}

//******************************************************************************
void Buffer::Release()
{
    SafeArrayDelete(data);
    width = height = 0;
}
}