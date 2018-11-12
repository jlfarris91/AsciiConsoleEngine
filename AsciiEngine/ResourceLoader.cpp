#include "ResourceLoader.h"
#include "Resources.h"

ResourceLoader::ResourceLoader(StringParam typeName, StringParam dataType)
    : typeName(typeName), dataType(dataType)
{
}

Getter(StringParam, ResourceLoader::TypeName)
{
    return typeName;
}

Getter(StringParam, ResourceLoader::DataType)
{
    return dataType;
}