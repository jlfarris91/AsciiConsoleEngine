#pragma once

class IGameObject;
class Transform;

class IComponent
{
public:
	IPropertyR(GameObjectHandle, Owner);
    IPropertyRW(bool, Enabled);

    IGetterRef(const string, Name);
    Property(string, Name);

    IPropertyR(TransformHandle, Transform);

	virtual void Start(void) = 0;
	virtual void Update(void) = 0;
	virtual void OnEnabled(void) = 0;
	virtual void OnDisabled(void) = 0;
	virtual void OnDestroy(void) = 0;
};