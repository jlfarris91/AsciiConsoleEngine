#include "GameObject.h"
#include "Transform.h"

//DefineReflectedType(GameObject)

DefineStrictClassHandle(GameObject);

void GameObject::InitializeMeta(Meta::TypeBuilder& builder)
{
    builder.AddBase<PoolableObject<GameObject>>();
    builder.AddMethod<GameObject, GameObjectHandle>("New", &New);
    builder.AddMethod<GameObject, ComponentHandle>("GetComponent", &GameObject::GetComponent, { "type" });
    builder.AddMethod<GameObject, ComponentHandle, ComponentHandle>("AddComponent", &GameObject::AddComponent, { "type" });
    builder.AddProperty("Name", &Name_get, &Name_set);
    builder.AddProperty("IsEnabled", &IsEnabled_get, &IsEnabled_set);
    builder.AddReadOnlyProperty("Components", &Components_get);
    builder.AddReadOnlyProperty("Transform", &Transform_get);
    builder.AddField("Self", &GameObject::Self);
}

GameObject::GameObject()
    : Self(Pool.ResolvePointer(this))
{
    // add transform component
    AddComponent<::Transform>();
}

GameObject::~GameObject()
{
}

ComponentHandle GameObject::GetComponent(StringParam typeName) const
{
    for (auto &&component : components)
    {
        if (component->Name == typeName)
        {
            return component;
        }
        else
        {
            auto compType = component->GetType();
            auto baseType = Meta::GetType(typeName);
            if (compType->IsSubclassOf(baseType))
            {
                return component;
            }
        }
    }
    return ComponentHandle::InvalidHandle;
}

ComponentHandle GameObject::AddComponent(ComponentHandle component)
{
    auto typeName = component->Name;
    components.push_back(component);
    component->Owner = Self;
    component->IsEnabled = true;
    // TODO: call Start() somewhere
    return component;
}

bool GameObject::HasComponent(StringParam typeName) const
{
    for (ComponentHandle component : components)
    {
        if (component->Name == typeName)
        {
            return true;
        }
    }
    return false;
}

Getter(const string &, GameObject::Name)
{
    return name;
}

Setter(string, GameObject::Name)
{
    name = value;
}

GetterRef(ComponentList, GameObject::Components)
{
	return components;
}

Getter(TransformHandle, GameObject::Transform)
{
    return (TransformHandle)components.front();
}

Getter(bool, GameObject::IsEnabled)
{
    return enabled;
}

Setter(bool, GameObject::IsEnabled)
{
    if (enabled != value)
    {
        enabled = value;
        if (enabled)
        {
            OnEnabled();
        }
        else
        {
            OnDisabled();
        }
    }
}

void GameObject::OnEnabled()
{
    for (auto &&component : Components)
    {
        component->IsEnabled = true;
    }
}

void GameObject::OnDisabled()
{
    for (auto &&component : Components)
    {
        component->IsEnabled = false;
    }
}