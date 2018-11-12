#pragma once

namespace ConsoleGL
{

class DepthBuffer
{
public:

    uint width;
    uint height;
    float *data;

    DepthBuffer(uint width = 0, uint height = 0);
    virtual ~DepthBuffer();

    void Resize(uint width, uint height);

    inline void Clear(float value)
    {   
        memset(data, 0, width * height * sizeof(int));
    }

    inline void Plot(float value, uint x, uint y)
    {
        #ifdef _DEBUG
        if (!InBounds(x, y))
            return;
        #endif
        this->data[y * width + x] = value;
    }

    inline bool InBounds(uint x, uint y) const
    {
        return x >= 0 && x < width &&
            y >= 0 && y < height;
    }

    inline float GetDepthAt(uint x, uint y)
    {
        #ifdef _DEBUG
        if (!InBounds(x, y))
            return INT_MIN;
        #endif
        return data[y * width + x];
    }

protected:
    virtual void Release();
};

typedef DepthBuffer *DepthBufferPtr;
}