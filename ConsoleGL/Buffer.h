#pragma once
#include "Math/Int2.h"
#include "ConsoleGfx.h"

namespace ConsoleGL
{
//----------------------------------------------------------------------- Buffer
//******************************************************************************
class Buffer
{
public:
    uint width;
    uint height;
    CharInfo *data;
    Char alphaMask;

    Buffer(uint width = 0, uint height = 0);
    Buffer(Size size);
    virtual ~Buffer();

    void Resize(uint width, uint height);
    void Clear(Char c, CharAttr attr);

    void Plot(Char c, CharAttr attr, uint x, uint y)
    {
        #ifdef _DEBUG
        if (!InBounds(x, y))
            return;
        #endif
        CharInfo &data = this->data[y * width + x];
        data.Char.AsciiChar = c;
        data.Attributes = attr;
    }

    bool InBounds(uint x, uint y) const;

protected:
    virtual void Release();
};

typedef const Buffer &BufferParam;
typedef Buffer *BufferPtr;
}