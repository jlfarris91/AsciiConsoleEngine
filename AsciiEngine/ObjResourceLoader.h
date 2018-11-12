#pragma once
#include "ResourceLoader.h"

class ObjResourceLoader : public ResourceLoader
{
public:
    ObjResourceLoader();
    AssetHandle Load(StringParam filename) override;
};