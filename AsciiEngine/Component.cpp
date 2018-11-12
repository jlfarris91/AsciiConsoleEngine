#include "Component.h"
#include "GameObject.h"
#include "Transform.h"

DefineReflectedType(Component)
{
    builder.SetName("Component");
    ReflectPropertyRO(Owner);
    ReflectPropertyRO(Name);
    ReflectProperty(IsEnabled);
    ReflectPropertyRO(Transform);
}

Getter(GameObjectHandle, Component::Owner)
{
    return owner;
}

Setter(GameObjectHandle, Component::Owner)
{
    owner = value;
}

Getter(bool, Component::IsEnabled)
{
    return enabled;
}

Setter(bool, Component::IsEnabled)
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

Getter(TransformHandle, Component::Transform)
{
    return Owner->Transform;
}