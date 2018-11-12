#pragma once
#include "Asset.h"

class ResourceLoader
{
public:
    ResourceLoader(StringParam typeName, StringParam dataType);
    virtual AssetHandle Load(StringParam filename) = 0;

    Getter(StringParam, TypeName);
    PropertyR(string, TypeName);

    Getter(StringParam, DataType);
    PropertyR(StringParam, DataType);
private:
    string typeName;
    string dataType;
};