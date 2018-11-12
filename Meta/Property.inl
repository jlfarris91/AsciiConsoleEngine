#pragma once
#include "Property.h"
#include "MetaException.h"
#include "Method.h"

namespace Meta
{

template <typename PropertyT>
PropertyT Property::Get()
{
    return getter->Invoke<PropertyT>();
}

template <typename PropertyT>
PropertyT Property::Get(void *obj)
{
    return getter->Invoke<PropertyT>(obj);
}

template <typename PropertyT>
void Property::Set(PropertyT value)
{
    if (setter == nullptr)
    {
        throw MetaException(
            "ReadOnlyProperty",
            "Trying to set read-only Property '%s'.",
            name.c_str());
    }
    setter->Invoke(value);
}

template <typename PropertyT>
void Property::Set(void *obj, PropertyT value)
{
    if (setter == nullptr)
    {
        throw MetaException(
            "ReadOnlyProperty",
            "Trying to set read-only Property '%s'.",
            name.c_str());
    }
    setter->Invoke(obj, value);
}

}