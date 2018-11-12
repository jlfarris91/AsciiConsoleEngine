#pragma once
#include "Property.h"

namespace Meta
{

Property::Property()
    : Member(MemberType::Property)
{
}


Getter(Type *, Property::Type)
{
    return type;
}

}