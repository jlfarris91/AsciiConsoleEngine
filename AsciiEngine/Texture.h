#pragma once
#include "Asset.h"
#include "ObjectPool.h"

namespace ConsoleGL
{
    class ITexture;
}

class Texture : public Asset, public PoolableObject<Texture>
{
public:
    DefineTypeName(Texture);
    Texture(ConsoleGL::ITexture *rawTexture = nullptr);

    Getter(uint, Width);
    PropertyR(uint, Width);

    Getter(uint, Height);
    PropertyR(uint, Height);

    Getter(ConsoleGL::ITexture *, RawTexture);
    PropertyR(ConsoleGL::ITexture *, RawTexture);


private:
    ConsoleGL::ITexture *texture = nullptr;
};

DefineStrictClassHandle(Texture);