#pragma once
#include "ISerializer.h"

class GameObjectSerializer : public ISerializer
{
public:
    string Serialize(void *object) override;
};