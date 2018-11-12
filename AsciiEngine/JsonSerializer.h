#pragma once
#include "ISerializer.h"
#include "Shared/ArrayList.h"

class JsonNode;

class JsonSerializer : public ISerializer
{
public:

    DeclareSerializeFn(int, 0);
    DeclareSerializeFn(float, 0.0f);
    DeclareSerializeFn(double, 0.0);
    DeclareSerializeFn(bool, false);
    DeclareSerializeFn(string, string());
    DeclareSerializeFn(Vector2, Vector2::Zero);
    DeclareSerializeFn(Vector3, Vector3::Zero);
    DeclareSerializeFn(Vector4, Vector4::Zero);

    virtual string Serialize(void *object) = 0;

    virtual bool SerializeReference(StringParam name, IObject* field);

    Getter(SerializerDirection::Type, Direction);

private:

    JsonNode *root;
    JsonNode *currentNode;

    SerializerDirection::Type direction;
};