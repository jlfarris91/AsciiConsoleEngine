#include "Parameter.h"

namespace Meta
{

Parameter::Parameter(StringParam name, Meta::Type* type, bool isConst, bool isOptional)
    : name(name), type(type), isOptional(isOptional), isConst(isConst)
{
}

Getter(StringParam, Parameter::Name) const
{
    return name;
}

Getter(Type *, Parameter::Type) const
{
    return type;
}

Getter(bool, Parameter::IsConst) const
{
    return isConst;
}

Getter(bool, Parameter::IsOptional) const
{
    return isOptional;
}

}