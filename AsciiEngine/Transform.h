#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"
#include "Shared/ArrayList.h"

class Transform;
DefineStrictClassHandle(Transform);

class Transform : public Component, public PoolableObject<Transform>
{
public:
    typedef ArrayList<TransformHandle> ChildList;

    DeclareNameProperty(Transform);
    ReflectType(Transform);

    Getter(Vector3, Position);
    PropertyRW(Vector3, Position);

    Getter(Vector3, Scale);
    PropertyR(Vector3, Scale);

    Getter(Vector3, Rotation);
    PropertyRW(Vector3, Rotation);

    Getter(Vector3, LocalPosition);
    void LocalPosition_set(Vec3Param value);
    PropertyRW(Vector3, LocalPosition);

    Getter(Vector3, LocalScale);
    void LocalScale_set(Vec3Param value);
    PropertyRW(Vector3, LocalScale);

    Getter(Vector3, LocalRotation);
    void LocalRotation_set(Vec3Param value);
    PropertyRW(Vector3, LocalRotation);

    Getter(Vector3, Forward);
    PropertyR(Vector3, Forward);

    Getter(Vector3, Right);
    PropertyR(Vector3, Right);

    Getter(Vector3, Up);
    PropertyR(Vector3, Up);

    Getter(const Matrix4 &, WorldMtx);
    PropertyR(const Matrix4 &, WorldMtx);

    GetSet(TransformHandle, Parent);
    PropertyRW(TransformHandle, Parent);

    GetSet(bool, IsDirty);
    PropertyRW(bool, IsDirty);

    Getter(ChildList &, Children);
    PropertyR(ChildList, Children);

    void SetRotation(Vector4 quat);
    void SetRotation(Vector3 axis, float angle);
    Vector4 GetRotation();

    void LookAt(Vec3Param target);

    bool physicsDirty = false;

private:

    void UpdateMatrix();
    void UpdateWorld();

    Vector3 position;
    Vector3 scale = Vector3::One;
    Vector3 rotation;

    Vector3 localPosition;
    Vector3 localScale = Vector3::One;
    Vector3 localRotation;

    Vector3 forward = Vector3::Forward;
    Vector3 right = Vector3::Right;
    Vector3 up = Vector3::Up;

    Matrix4 worldMtx;
    TransformHandle parent;
    bool isDirty = false;

    ChildList children;
};
