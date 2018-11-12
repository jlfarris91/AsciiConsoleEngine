#pragma once
#include "ISerializer.h"

class ISerializable
{
public:
    virtual void Serialize(ISerializer &serializer) = 0;
};