#pragma once
#include "Asset.h"
#include "ObjectPool.h"

class Script : public Asset, public PoolableObject<Script>
{
public:
    DefineTypeName(Script);
    Script() = default;
};

DefineStrictClassHandle(Script);