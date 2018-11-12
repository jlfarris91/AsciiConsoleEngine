#include "UnitySceneBlock.h"

//UnitySceneBlock::UnitySceneBlock(const UnitySceneBlock &other)
//    : Name(other.Name),
//    Value(other.Value),
//    TypeId(other.TypeId),
//    FileId(other.FileId),
//    Children(other.Children),
//    Line(other.Line)
//{
//}

UnitySceneBlock *UnitySceneBlock::FindChild(StringParam name)
{
    for (auto &&child : Children)
    {
        if (child.Name == name)
            return &child;
    }
    return nullptr;
}

int UnitySceneBlock::GetInt()
{
    int i;
    sscanf_s(Value.c_str(), "%d", &i);
    return i;
}

float UnitySceneBlock::GetFloat()
{
    float f;
    sscanf_s(Value.c_str(), "%f", &f);
    return f;
}

bool UnitySceneBlock::GetBool()
{
    int b;
    sscanf_s(Value.c_str(), "%d", &b);
    return b != 0;
}

Vector2 UnitySceneBlock::GetVector2()
{
    Vector2 vec;
    sscanf_s(Value.c_str(), "{x: %f, y: %f}", &vec.x, &vec.y);
    return vec;
}

Vector3 UnitySceneBlock::GetVector3()
{
    Vector3 vec;
    sscanf_s(Value.c_str(), "{x: %f, y: %f, z: %f}", &vec.x, &vec.y, &vec.z);
    return vec;
}

Vector4 UnitySceneBlock::GetVector4()
{
    Vector4 vec;
    sscanf_s(Value.c_str(), "{x: %f, y: %f, z: %f, w: %f}", &vec.x, &vec.y, &vec.z, &vec.w);
    return vec;
}

Vector4 UnitySceneBlock::GetColor()
{
    Vector4 vec;
    sscanf_s(Value.c_str(), "{r: %f, g: %f, b: %f, a: %f}", &vec.x, &vec.y, &vec.z, &vec.w);
    return vec;
}

FileIdT UnitySceneBlock::GetFileId()
{
    FileIdT id = 0;
    sscanf_s(Value.c_str(), "{fileID: %lu}", &id);
    return id;
}