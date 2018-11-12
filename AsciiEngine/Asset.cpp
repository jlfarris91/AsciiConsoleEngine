#include "Asset.h"
#include "Resources.h"

DefineReflectedType(Asset)
{
    ReflectProperty(Name);
}

Getter(StringParam, Asset::Name)
{
    return name;
}

Setter(StringParam, Asset::Name)
{
    // TODO: validate for unique name
    name = value;
}