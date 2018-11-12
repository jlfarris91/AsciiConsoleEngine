#include "JsonNode.h"

DefineEnum11(JsonFieldType,
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

bool JsonNode::TryGetChild(StringParam name, JsonNode &out)
{
    for (auto &&child : children)
    {
        if (child.name == name)
        {
            out = child;
        }
    }
    return false;
}

JsonNode &JsonNode::operator=(const JsonNode &other)
{
    this->value = other.value;
    this->children = other.children;
    this->name = other.name;
    this->type = other.type;
    this->value = other.value;
    return *this;
}