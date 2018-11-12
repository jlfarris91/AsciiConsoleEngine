#include "ResourceCreator.h"
#include "Resources.h"

ResourceCreator::ResourceCreator(StringParam typeName)
    : typeName(typeName)
{
}

Getter(StringParam, ResourceCreator::TypeName)
{
    return typeName;
}