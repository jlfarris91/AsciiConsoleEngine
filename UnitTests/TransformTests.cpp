#include "TransformTests.h"
#include "Transform.h"
#include "GameObject.h"

DefineTest(TransformTests::LocalComponents, SettingLocalPositionShouldUpdateWorldPosition_NoParent)
{
    // Arrange
    auto &&go = GameObject::New();
    auto &&trans = Transform::New();
    go->AddComponent(trans);

    // Act
    trans->LocalPosition = Vector3::One * 100.0f;

    // Assert
    Assert(trans->Position == Vector3(100.0f, 100.0f, 100.0f));
}

DefineTest(TransformTests::LocalComponents, SettingLocalRotationShouldUpdateWorldRotation_NoParent)
{
    // Arrange
    auto &&go = GameObject::New();
    auto &&trans = Transform::New();
    go->AddComponent(trans);

    // Act
    trans->LocalRotation = Vector3::One * 100.0f;

    // Assert
    Assert(trans->Rotation == Vector3(100.0f, 100.0f, 100.0f));
}

DefineTest(TransformTests::LocalComponents, SettingLocalScaleShouldUpdateWorldScale_NoParent)
{
    // Arrange
    auto &&go = GameObject::New();
    auto &&trans = Transform::New();
    go->AddComponent(trans);

    // Act
    trans->LocalScale = Vector3::One * 100.0f;

    // Assert
    Assert(trans->Scale == Vector3(100.0f, 100.0f, 100.0f));
}