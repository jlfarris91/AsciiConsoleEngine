#pragma once
#include "ObjectPool.h"
#include "Component.h"
#include <unordered_map>
#include <list>
#include "Meta/Interface.h"

class Transform;
class Component;

typedef std::list<ComponentHandle> ComponentList;
typedef std::unordered_map<string, size_t> ComponentIndexMap;

class GameObject : public PoolableObject<GameObject>, public Object//, public ISerializable
{
public:
    ReflectType(GameObject);

    GameObject();
    virtual ~GameObject();

	/// Gets a component by type name.
	ComponentHandle GetComponent(StringParam type) const;

    /// Gets a component by type.
    template <typename ComponentT>
    Handle<ComponentT, StrictIndex> GetComponent() const;

    template <typename ComponentT, typename ...Args>
    Handle<ComponentT, StrictIndex> AddComponent(Args... args);

    ComponentHandle AddComponent(ComponentHandle component);

    bool HasComponent(StringParam type) const;

    template <typename ComponentT>
    bool HasComponent() const;

    //void Serialize(ISerializable &serializer);

    /// Gets the object's Name
	Getter(const string &, Name);
	Setter(string, Name);
    PropertyRW(string, Name);

    /// Should the GameObject be updated?
    GetSet(bool, IsEnabled);
    PropertyRW(bool, IsEnabled);

	/// Gets the list of all components on this object.
	GetterRef(ComponentList, Components);
    PropertyR(ComponentList, Components);

	/// Gets the transform component.
	Getter(TransformHandle, Transform);
    PropertyR(TransformHandle, Transform);

    GameObjectHandle Self;

    bool Initialized = false;

private:
    void OnEnabled();
    void OnDisabled();

	string name;
	ComponentList components;
    bool enabled = false;
};

#include "GameObject.inl"

DefineStrictClassHandle(GameObject);