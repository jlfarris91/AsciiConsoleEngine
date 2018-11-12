#pragma once
#include "AsciiEngine/Component.h"
#include "AsciiEngine/ObjectPool.h"
#include "Math/Vector3.h"

class TestComponent : public Component, public PoolableObject<TestComponent>
{
public:
    DeclareNameProperty(TestComponent);
    ReflectType(TestComponent);

    void Start() override;
    void Update() override;

    int Count;

private:

    Vector3 startPos;
    Vector3 startRot;
};

DefineStrictClassHandle(TestComponent);