#pragma once
#include "ResourceLoader.h"

class TextureResourceLoader : public ResourceLoader
{
public:
    TextureResourceLoader();
    AssetHandle Load(StringParam filename) override;
};