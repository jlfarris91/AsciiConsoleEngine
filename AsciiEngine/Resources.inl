#pragma once
#include "Shared/Exception.h"
#include "ResourceLoader.h"

template <typename T>
Handle<T, StrictIndex> Resources::GetAsset(StringParam name)
{
    string typeName = T::GetTypeName();
    return this->GetAsset(typeName, name);
}