#include "DepthBuffer.h"

namespace ConsoleGL
{

DepthBuffer::DepthBuffer(uint width, uint height)
    : width(width), height(height), data(NULL)
{
    Resize(width, height);
}

DepthBuffer::~DepthBuffer()
{
    SafeArrayDelete(data);
}

void DepthBuffer::Resize(uint width, uint height)
{
    Release();
    if (width > 0 && height > 0)
        data = new float[width * height];
    this->width = width;
    this->height = height;
}

void DepthBuffer::Release()
{
    SafeArrayDelete(data);
    width = height = 0;
}

}