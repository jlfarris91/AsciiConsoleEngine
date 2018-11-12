#pragma once
#include "Field.h"

namespace Meta
{

Field::Field()
    : Member(MemberType::Field)
{
}

Getter(Type *, Field::Type)
{
    return type;
}

Getter(bool, Field::IsArray) const
{
    return isArray;
}

Getter(unsigned, Field::Count) const
{
    return count;
}

void CheckBounds(unsigned index, unsigned count)
{
    if (index > count)
    {
        throw MetaException(
            "IndexOutOfBounds",
            "Requested index %u of array of size %u.",
            index,
            count);
    }
}

void CheckReadOnly(GenericFuncT setter, StringParam name)
{
    if (setter == nullptr)
    {
        throw MetaException(
            "ReadOnlyField",
            "Trying to set-read only field '%s'.",
            name.c_str());
    }
}

}