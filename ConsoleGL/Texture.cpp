#include "Texture.h"

namespace ConsoleGL
{

Getter(CharInfo *, Texture::Data)
{
    return data;
}

Getter(unsigned, Texture::Width)
{
    return width;
}

Getter(unsigned, Texture::Height)
{
    return height;
}

}