#pragma once

#include "Shared/ArrayList.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

DeclareEnum11(JsonFieldType,
    None,
    Integer,
    Float,
    Double,
    Bool,
    String,
    ULong,
    Vector2,
    Vector3,
    Vector4,
    Data);

class JsonNode
{
public:
    JsonNode() = default;

    bool TryGetChild(StringParam name, JsonNode &out);
    JsonNode &operator=(const JsonNode &other);

    JsonFieldType::Type type = JsonFieldType::None;
    ArrayList<JsonNode> children;
    string value;
    string name;
};
