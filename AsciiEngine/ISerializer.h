#pragma once
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "IObject.h"

#define DeclareVirtualSerializeFn(type, def) \
    virtual bool Serialize(StringParam name, type &field, type defaultValue = def) = 0

#define DeclareSerializeFn(type, def) \
    bool Serialize(StringParam name, type &field, type defaultValue = def) override

DeclareEnum2(SerializerDirection,
    Serialize,
    Deserialize);

class ISerializer
{
public:

    DeclareVirtualSerializeFn(int, 0);
    DeclareVirtualSerializeFn(float, 0.0f);
    DeclareVirtualSerializeFn(double, 0.0);
    DeclareVirtualSerializeFn(bool, false);
    DeclareVirtualSerializeFn(string, string());
    DeclareVirtualSerializeFn(Vector2, Vector2::Zero);
    DeclareVirtualSerializeFn(Vector3, Vector3::Zero);
    DeclareVirtualSerializeFn(Vector4, Vector4::Zero);

    virtual string Serialize(void *object) = 0;

    virtual bool SerializeReference(StringParam name, IObject* field);

    IGetter(SerializerDirection::Type, Direction);
    PropertyR(SerializerDirection::Type, Direction);
};
