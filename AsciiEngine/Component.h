#pragma once
#include "Meta/Interface.h"

class Transform;
class GameObject;
typedef Handle<GameObject, StrictIndex> GameObjectHandle;
typedef Handle<Transform, StrictIndex> TransformHandle;

//-------------------------------------------------------------------- Component
//******************************************************************************
class Component : public Object
{
public:
    ReflectType(Component);

    Component() = default;

	virtual void Start(void) {}
	virtual void Update(void) {}
    virtual void LateUpdate(void) {}
	virtual void OnEnabled(void) {}
	virtual void OnDisabled(void) {}
	virtual void OnDestroy(void) {}

    Getter(GameObjectHandle, Owner);
    PropertyRW(GameObjectHandle, Owner);

    virtual Getter(StringParam, Name) const = 0;
    PropertyR(string, Name);
    
    GetSet(bool, IsEnabled);
    PropertyRW(bool, IsEnabled);

    Getter(TransformHandle, Transform);
    PropertyR(TransformHandle, Transform);

private:
    GameObjectHandle owner;
    string name;
    bool enabled = true;

    Setter(GameObjectHandle, Owner);

    friend class GameObject;
};

DefineStrictClassHandle(Component);

#define DeclareNameProperty(type) \
    Getter(StringParam, Name) const override \
    { \
        return type::GetTypeName(); \
    }

#define DeclareNamePropertyAs(name) \
    Getter(StringParam, Name) const override \
    { \
        static string _className = #name; \
        return _name; \
    }

#define DefineComponentClass(name) \
    class name : public Component, public PoolableObject<name>
