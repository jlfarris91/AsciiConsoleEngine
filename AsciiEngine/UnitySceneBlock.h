#pragma once
#include <unordered_map>
#include <vector>
#include "UnitySceneLoaderCommon.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"

class UnitySceneBlock;
typedef std::vector<UnitySceneBlock> BlockList;

class UnitySceneBlock
{
public:
    string Name;
    string Value;
    string Line;
    ushort TypeId = 0;
    FileIdT FileId = 0;
    BlockList Children;
    bool Handled = false;

    UnitySceneBlock() = default;
    //UnitySceneBlock(const UnitySceneBlock &other) = default;
    UnitySceneBlock *FindChild(StringParam name);

    int GetInt();
    float GetFloat();
    bool GetBool();
    Vector2 GetVector2();
    Vector3 GetVector3();
    Vector4 GetVector4();
    Vector4 GetColor();
    FileIdT GetFileId();

    template <typename T>
    T GetValue()
    {
        throw new std::exception("GetValue not implemented for template type.");
    }

    template <>
    int GetValue<int>()
    {
        return GetInt();
    }

    template <>
    float GetValue<float>()
    {
        return GetFloat();
    }

    template <>
    bool GetValue<bool>()
    {
        return GetBool();
    }

    template <>
    Vector2 GetValue<Vector2>()
    {
        return GetVector2();
    }

    template <>
    Vector3 GetValue<Vector3>()
    {
        return GetVector3();
    }

    template <>
    Vector4 GetValue<Vector4>()
    {
        if (Value.Find('r') != string::npos)
            return GetColor();
        return GetVector4();
    }

    template <>
    FileIdT GetValue<unsigned long>()
    {
        return GetFileId();
    }

    template <>
    string GetValue<String>()
    {
        return Value;
    }

    template <typename T>
    T GetChildValue(StringParam childName, T defaultValue)
    {
        if (auto &&child = FindChild(childName))
        {
            return child->GetValue<T>();
        }
        return defaultValue;
    }
};