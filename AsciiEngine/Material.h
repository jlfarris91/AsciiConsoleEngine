#pragma once
#include "Asset.h"
#include "ObjectPool.h"
#include "Texture.h"

typedef std::vector<TextureHandle> TextureList;

class Material : public Asset, public PoolableObject<Material>
{
public:
    DefineTypeName(Material);

    Getter(TextureList &, Textures);
    PropertyR(TextureList, Textures);

private:
    TextureList textures;
};

DefineStrictClassHandle(Material);