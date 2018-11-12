#pragma once
#include "Meta.h"

namespace Meta
{


/// <summary>
/// Constructor for reference objects. Internally the object is treated as a
/// pointer to the object.
/// </summary>
template <typename T>
Variant::Variant(T obj)
{
    const auto size = sizeof(T);
    if (size > DataMaxSize)
    {
        heapData = new byte[size];
    }

    // Get the Type of the data
    type = Internal::GetOrInitializeType<T>();
}

/// <summary>
/// Constructor for reference objects. Internally the object is treated as a
/// pointer to the object.
/// </summary>
template <typename T>
Variant::Variant(T &obj)
{
    // Store the address of the object reference
    auto typedDataPtr = reinterpret_cast<T*>(stackData);
    *typedDataPtr = &obj;

    // Get the Type of the data
    type = Internal::GetOrInitializeType<T>();
}

/// <summary>
/// Constructor for reference objects. Internally the object is treated as a
/// pointer to the object.
/// </summary>
template <typename T>
Variant::Variant(T *obj)
{
    // Store the address of the object reference
    auto typedDataPtr = reinterpret_cast<T*>(stackData);
    *typedDataPtr = obj;

    // Get the Type of the data
    type = Internal::GetOrInitializeType<T>();
}

template <typename T>
T Variant::As() const
{
    if (heapData != nullptr)
    {
        return *(T*) heapData;
    }
    return *(T*) stackData;
}

template <typename T>
T *Variant::AsPtr() const
{
    return (T*) stackData;
}

template <typename T>
T &Variant::AsRef() const
{
    return *(T*) stackData;
}


}
