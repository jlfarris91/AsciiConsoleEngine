#include "Transform.h"
#include "Math/Mathf.h"
#include "GameObject.h"

DefineReflectedType(Transform)
{
    builder.AddBase<Component>();
    ReflectPropertyRO(Position);
    ReflectPropertyRO(Scale);
    ReflectPropertyRO(Rotation);
    ReflectProperty(LocalPosition);
    ReflectProperty(LocalScale);
    ReflectProperty(LocalRotation);
    ReflectPropertyRO(Forward);
    ReflectPropertyRO(Right);
    ReflectPropertyRO(Up);
    ReflectPropertyRO(WorldMtx);
    ReflectProperty(Parent);
    ReflectProperty(IsDirty);
    ReflectPropertyRO(Children);
    //ReflectMethod(SetRotation, "quaternion");
    ReflectMethod(GetRotation);
    ReflectMethod(LookAt, "target");
}

Getter(Vector3, Transform::Position)
{
    if (isDirty)
    {
        UpdateWorld();
    }
	return position;
}

Getter(Vector3, Transform::Scale)
{
    if (isDirty)
    {
        UpdateWorld();
    }
	return scale;
}

Getter(Vector3, Transform::Rotation)
{
    if (isDirty)
    {
        UpdateWorld();
    }
	return rotation;
}

Getter(Vector3, Transform::LocalPosition)
{
    if (isDirty)
    {
        UpdateWorld();
    }
	return localPosition;
}

void Transform::LocalPosition_set(Vec3Param value)
{
	localPosition = value;
    IsDirty = true;
    physicsDirty = true;
}

Getter(Vector3, Transform::LocalScale)
{
    if (isDirty)
    {
        UpdateWorld();
    }
    return localScale;
}

void Transform::LocalScale_set(Vec3Param value)
{
	localScale = value;
    IsDirty = true;
    physicsDirty = true;
}

Getter(Vector3, Transform::LocalRotation)
{
    if (isDirty)
    {
        UpdateWorld();
    }
    return localRotation;
}

void Transform::LocalRotation_set(Vec3Param value)
{
	localRotation = value;
    IsDirty = true;
    physicsDirty = true;
}

Getter(const Matrix4 &, Transform::WorldMtx)
{
    if (isDirty)
    {
        UpdateWorld();
    }
	return worldMtx;
}

Getter(Vector3, Transform::Forward)
{
    if (isDirty)
    {
        UpdateWorld();
    }
    return forward;
}

Getter(Vector3, Transform::Right)
{
    if (isDirty)
    {
        UpdateWorld();
    }
    return right;
}

Getter(Vector3, Transform::Up)
{
    if (isDirty)
    {
        UpdateWorld();
    }
    return up;
}

Getter(TransformHandle, Transform::Parent)
{
	return parent;
}

Setter(TransformHandle, Transform::Parent)
{
    if (parent != value)
    {
        // remove from old parent
        if (parent)
        {
            parent->Children.remove(Self);
        }

        // set new parent
        parent = value;

        if (parent)
        {
            parent->Children.push_back(Self);
        }

        // make sure to update 
        UpdateWorld();
    }
}

Getter(bool, Transform::IsDirty)
{
    return isDirty;
}

Setter(bool, Transform::IsDirty)
{
    if (isDirty != value)
    {
        isDirty = value;
        if (isDirty)
        {
            physicsDirty = true;
            for (auto &&child : children)
            {
                child->IsDirty = true;
            }
        }
    }
}

Getter(Transform::ChildList &, Transform::Children)
{
    return children;
}

void Transform::SetRotation(Vector4 quat)
{
    LocalRotation = Mathf::EulerFromQuaternion2(quat);
}

void Transform::SetRotation(Vector3 axis, float angle)
{
    LocalRotation = Mathf::AxisAngleToEuler(axis, angle);
}

Vector4 Transform::GetRotation()
{
    return Vector4();
}

void Transform::LookAt(Vec3Param target)
{
    // direction vector in local space
    Vector3 d = (target - position).Normalized();

    float x = atan2(-d.y, d.z) * Mathf::RAD_TO_DEG;
    float y = atan2(d.x, d.z) * Mathf::RAD_TO_DEG;
    float z = atan2(d.y, d.x) * Mathf::RAD_TO_DEG;

    rotation = Vector3(x, y, z);
    IsDirty = true;
}

void Transform::UpdateMatrix()
{
    Matrix4 transMtx, rotXMtx, rotYMtx, rotZMtx, scaleMtx;
    auto &&parentPtr = *parent;

    Matrix4::SetTranslation(transMtx, localPosition);
    Matrix4::SetRotation(rotXMtx, localRotation.x * Mathf::DEG_TO_RAD, Vector3::Right);
    Matrix4::SetRotation(rotYMtx, localRotation.y * Mathf::DEG_TO_RAD, Vector3::Up);
    Matrix4::SetRotation(rotZMtx, localRotation.z * Mathf::DEG_TO_RAD, Vector3::Forward);
    //Matrix4::FromEuler(rotMtx, localRotation);
    Matrix4::SetScale(scaleMtx, localScale);
    worldMtx = transMtx * rotYMtx * rotXMtx * rotZMtx * scaleMtx;

    if (parentPtr)
    {
        worldMtx = parentPtr->WorldMtx * worldMtx;
    }
}

void Transform::UpdateWorld()
{
    UpdateMatrix();

    position = localPosition;
    rotation = localRotation;
    scale = localScale;

    forward = (worldMtx * Vector3::Forward).Normalized();
    right = (worldMtx * Vector3::Right).Normalized();
    up = (worldMtx * Vector3::Up).Normalized();

    isDirty = false;
}