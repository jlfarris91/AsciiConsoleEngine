#include "TestComponent.h"
#include "AsciiEngine/Transform.h"
#include "AsciiEngine/GameObject.h"
#include <AsciiEngine/Input.h>

DefineReflectedType(TestComponent)
{
    builder.SetName("TestComponent");
    builder.AddBase<Component>();
    builder.AddBase<PoolableObject<TestComponent>>();
    builder.AddField("Count", &TestComponent::Count);
    builder.AddMethod<TestComponent, TestComponentHandle>("New", &TestComponent::New);
}

void TestComponent::Start()
{
    startPos = Transform->LocalPosition;
    startRot = Transform->LocalRotation;
}

void TestComponent::Update()
{
    ::Transform *trans = *Transform;
    if (trans == nullptr)
        return;

    if (gInput->IsKeyDown(Keys::Space))
    {
        trans->LocalPosition = startPos;
        trans->LocalRotation = startRot;
    }
}