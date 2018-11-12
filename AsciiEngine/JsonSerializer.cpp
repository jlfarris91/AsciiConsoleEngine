#include "JsonSerializer.h"

#include <sstream>

#include "JsonException.h"
#include "JsonNode.h"

#define DefineJsonSerializerFn(fieldType, jsonFieldType, fmt) \
bool JsonSerializer::Serialize(StringParam name, fieldType &field, fieldType defaultValue)\
{\
    if (direction == SerializerDirection::Serialize)\
    {\
        JsonNode node;\
        node.type = jsonFieldType;\
        node.value = String::Format(fmt, field);\
        node.name = name;\
        currentNode->children.push_back(node);\
        return true;\
    }\
    else\
    {\
        JsonNode node;\
        if (!currentNode->TryGetChild(name, node))\
        {\
            field = defaultValue;\
            return false;\
        }\
        else\
        {\
            if (node.type != jsonFieldType)\
            {\
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",\
                    JsonFieldType::Names[jsonFieldType],\
                    JsonFieldType::Names[node.type]);\
            }\
            sscanf_s(node.value.c_str(), fmt, &field);\
            return true;\
        }\
    }\
}

DefineJsonSerializerFn(int, JsonFieldType::Integer, "%d");
DefineJsonSerializerFn(float, JsonFieldType::Float, "%f");
DefineJsonSerializerFn(double, JsonFieldType::Double, "%lf");

bool JsonSerializer::Serialize(StringParam name, bool &field, bool defaultValue)
{
    if (direction == SerializerDirection::Serialize)
    {
        JsonNode node;
        node.type = JsonFieldType::Bool;
        node.value = String::Format("%s", field ? "true" : "false");
        node.name = name;
        currentNode->children.push_back(node);
        return true;
    }
    else
    {
        JsonNode node;
        if (!currentNode->TryGetChild(name, node))
        {
            field = defaultValue;
            return false;
        }
        else
        {
            if (node.type != JsonFieldType::Bool)
            {
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",
                    JsonFieldType::Names[JsonFieldType::Bool],
                    JsonFieldType::Names[node.type]);
            }

            field = atob(node.value.c_str());
            return true;
        }
    }
}

bool JsonSerializer::Serialize(StringParam name, string &field, string defaultValue)
{
    if (direction == SerializerDirection::Serialize)
    {
        JsonNode node;
        node.type = JsonFieldType::String;
        node.value = field;
        node.name = name;
        currentNode->children.push_back(node);
        return true;
    }
    else
    {
        JsonNode node;
        if (!currentNode->TryGetChild(name, node))
        {
            field = defaultValue;
            return false;
        }
        else
        {
            if (node.type != JsonFieldType::String)
            {
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",
                    JsonFieldType::Names[JsonFieldType::String],
                    JsonFieldType::Names[node.type]);
            }

            field = node.value;
            return true;
        }
    }
}

bool JsonSerializer::Serialize(StringParam name, Vector2 &field, Vector2 defaultValue)
{
    if (direction == SerializerDirection::Serialize)
    {
        JsonNode node;
        node.type = JsonFieldType::Vector2;
        node.value = String::Format("{ %f, %f }", field.x, field.y);
        node.name = name;
        currentNode->children.push_back(node);
        return true;
    }
    else
    {
        JsonNode node;
        if (!currentNode->TryGetChild(name, node))
        {
            field = defaultValue;
            return false;
        }
        else
        {
            if (node.type != JsonFieldType::Vector2)
            {
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",
                    JsonFieldType::Names[JsonFieldType::Vector2],
                    JsonFieldType::Names[node.type]);
            }

            sscanf_s(node.value.c_str(), "{ %f, %f }", &field.x, &field.y);
            return true;
        }
    }
}

bool JsonSerializer::Serialize(StringParam name, Vector3 &field, Vector3 defaultValue)
{
    if (direction == SerializerDirection::Serialize)
    {
        JsonNode node;
        node.type = JsonFieldType::Vector3;
        node.value = String::Format("{ %f, %f, %f }", field.x, field.y);
        node.name = name;
        currentNode->children.push_back(node);
        return true;
    }
    else
    {
        JsonNode node;
        if (!currentNode->TryGetChild(name, node))
        {
            field = defaultValue;
            return false;
        }
        else
        {
            if (node.type != JsonFieldType::Vector3)
            {
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",
                    JsonFieldType::Names[JsonFieldType::Vector3],
                    JsonFieldType::Names[node.type]);
            }

            sscanf_s(node.value.c_str(), "{ %f, %f, %f }", &field.x, &field.y, &field.z);
            return true;
        }
    }
}

bool JsonSerializer::Serialize(StringParam name, Vector4 &field, Vector4 defaultValue)
{
    if (direction == SerializerDirection::Serialize)
    {
        JsonNode node;
        node.type = JsonFieldType::Vector4;
        node.value = String::Format("{ %f, %f, %f, %f }", field.x, field.y);
        node.name = name;
        currentNode->children.push_back(node);
        return true;
    }
    else
    {
        JsonNode node;
        if (!currentNode->TryGetChild(name, node))
        {
            field = defaultValue;
            return false;
        }
        else
        {
            if (node.type != JsonFieldType::Vector4)
            {
                throw JsonException("Expected JsonNode of type %s but found type %s instead.",
                    JsonFieldType::Names[JsonFieldType::Vector4],
                    JsonFieldType::Names[node.type]);
            }

            sscanf_s(node.value.c_str(), "{ %f, %f, %f, %f }", &field.x, &field.y, &field.z, &field.w);
            return true;
        }
    }
}


