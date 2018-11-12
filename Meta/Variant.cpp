#include "Variant.h"
#include "Type.h"

namespace Meta
{
    
Variant::Variant()
{
}

Variant::Variant(void *ptr, const Meta::Type *type)
    : type(type)
{
    auto &&size = type->Size;
    if (size <= DataMaxSize)
    {
        memcpy(stackData, ptr, size);
    }
    else
    {
        heapData = new byte[size];
        memcpy(heapData, ptr, size);
    }
}

Variant::~Variant()
{
    type->Destruct(heapData != nullptr ? heapData : stackData);
}

bool Variant::operator==(const Variant &rhs)
{
    return this->type == rhs.type;
}

bool Variant::operator!=(const Variant &rhs)
{
    return !this->operator==(rhs);
}


}