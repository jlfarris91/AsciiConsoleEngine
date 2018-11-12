#pragma once
#include "Asset.h"

class ResourceCreator
{
public:
    ResourceCreator(StringParam typeName);
    virtual AssetHandle Create() = 0;

    Getter(StringParam, TypeName);
    PropertyR(string, TypeName);

private:
    string typeName;
};
