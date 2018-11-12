#pragma once
#include "GameObject.h"
#include <type_traits>

template <typename ComponentT>
Handle<ComponentT, StrictIndex> GameObject::GetComponent() const
{
    auto &&compHandle = GetComponent(ComponentT::GetTypeName());
    return DownCastHandle<ComponentT, Component, StrictIndex>(compHandle);
}

template <typename ComponentT, typename ...Args>
Handle<ComponentT, StrictIndex> GameObject::AddComponent(Args... args)
{
    auto &&component = ComponentT::New();
    this->AddComponent(UpCastHandle<ComponentT, Component, StrictIndex>(component));
    return component;
}

template <typename ComponentT>
bool GameObject::HasComponent() const
{
    return HasComponent(ComponentT::GetTypeName());
}