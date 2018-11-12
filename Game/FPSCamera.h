#pragma once
#include "AsciiEngine/Component.h"
#include "AsciiEngine/ObjectPool.h"
#include "AsciiEngine/MouseButtons.h"

DefineComponentClass(FpsCamera)
{
public:
    DeclareNameProperty(FpsCamera);
    ReflectType(FpsCamera);

    void Start() override;
    void Update() override;

    MouseButtons MouseButton;
    float DeadZone = 0.5f;

private:

    float wasDown = false;
};