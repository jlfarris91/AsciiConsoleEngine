#pragma once
#include "Field.h"
#include "MetaException.h"

namespace Meta
{

void CheckBounds(unsigned index, unsigned count);
void CheckReadOnly(GenericFuncT setter, StringParam name);

template <typename FieldT>
FieldT Field::Get()
{
    return Generic::Invoke<FieldT>(getter);
}

template <typename FieldT>
FieldT Field::Get(void *obj)
{
    return Generic::Invoke<FieldT>(getter, obj);
}

template <typename FieldT>
FieldT Field::Get(unsigned index)
{
    auto result = Generic::Invoke<FieldT*>(getter);
    return *(result + index);
}

template <typename FieldT>
FieldT Field::Get(void *obj, unsigned index)
{
    auto result = Generic::Invoke<FieldT*>(getter, obj);
    return *(result + index);
}

template <typename FieldT>
void Field::Set(FieldT value)
{
    if (isArray)
    {
        throw MetaException(
            "CannotSetArray",
            "Arrays are read-only, use void Set(index, FieldT) to set "
            "individual elements in the array.");
    }
    CheckReadOnly(setter, name);
    Generic::Invoke<void>(setter, value);
}

template <typename FieldT>
void Field::Set(void *obj, FieldT value)
{
    if (isArray)
    {
        throw MetaException(
            "CannotSetArray",
            "Arrays are read-only, use void Set(void*, index, FieldT) to set "
            "individual elements in the array.");
    }
    CheckReadOnly(setter, name);
    Generic::Invoke<void>(setter, obj, value);
}

template <typename FieldT>
void Field::Set(unsigned index, FieldT value)
{
    CheckReadOnly(setter, name);
    auto result = &Generic::Invoke<void>(setter, value);
    *(result + index) = value;
}

template <typename FieldT>
void Field::Set(void *obj, unsigned index, FieldT value)
{
    CheckReadOnly(setter, name);
    auto result = &Generic::Invoke<void>(setter, obj, value);
    *(result + index) = value;
}

}