#include "GameObjectUnitTests.h"
#include "Component.h"
#include "Transform.h"
#include "MeshFilter.h"

GameObjectUnitTests::Constructor::Constructor()
{
    GameObject::Pool.Clear();
}

DefineTest(GameObjectUnitTests::Constructor, ShouldCreateTransform)
{
    // Act
    auto &&go = GameObject::New();

    // Assert
    Assert(go->HasComponent<Transform>());
}

GameObjectUnitTests::GetComponent::GetComponent()
{
    GameObject::Pool.Clear();
}

DefineTest(GameObjectUnitTests::GetComponent, ShouldReturnComponentHandleIfComponentExists)
{
    // Arrange
    auto &&go = GameObject::New();

    // Act
    auto &&component = go->GetComponent(Transform::GetTypeName());
    auto &&transform = (TransformHandle)component;

    // Assert
    Assert(transform != TransformHandle::InvalidHandle);
    Assert(transform.IsAlive);
}