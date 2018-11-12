#pragma once
#include "Shared/Guid.h"

class IObject
{
public:
    virtual ~IObject() = default;
    IGetter(Guid, Id);
    PropertyR(Guid, Id);
    virtual string ToString() = 0;
};