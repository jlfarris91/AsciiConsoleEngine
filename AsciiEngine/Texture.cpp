#include "Texture.h"
#include "ConsoleGL\ITexture.h"

Texture::Texture(ConsoleGL::ITexture *rawTexture)
    : texture(rawTexture)
{
}

Getter(uint, Texture::Width)
{
    return texture->Width;
}

Getter(uint, Texture::Height)
{
    return texture->Height;
}

Getter(ConsoleGL::ITexture *, Texture::RawTexture)
{
    return texture;
}