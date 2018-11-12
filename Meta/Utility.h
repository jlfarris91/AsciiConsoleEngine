#pragma once
#include "HasMember.h"
#include "Library.h"
#include "Parameter.h"

namespace Meta
{

class Library;
typedef std::initializer_list<const char *> ArgNames;
    
namespace Internal
{

template <typename T>
struct Clean
{
    typedef typename std::remove_const<T>::type type;
};
    
template <typename T>
struct Concrete
{
    typedef typename std::remove_const<typename std::remove_reference<typename std::remove_pointer<typename std::remove_all_extents<T>::type>::type>::type>::type type;
};

template <typename T>
struct IsConcrete
{
    static constexpr bool value = !std::is_void<T>::value && !std::is_reference<T>::value && !std::is_pointer<T>::value && !std::is_array<T>::value;
};

template <typename T>
struct ArrayToPtr
{
    typedef typename std::remove_all_extents<T>::type type;
};

struct HashCodeAlgorithm
{
    static size_t hash_code(StringParam string)
    {
        return std::hash<std::string>()(string);
    }
};

template <unsigned int idx>
void UnrollTemplateTypes(Library &, TypeList &, bool)
{
}

template <unsigned int idx, typename T, typename ...Args>
void UnrollTemplateTypes(Library &library, TypeList &types, bool registerIfMissing = true)
{
    auto type = library.GetType<T>(registerIfMissing);
    types.push_back(type);
    UnrollTemplateTypes<idx + 1, Args...>(library, types, registerIfMissing);
}

template <typename ...Args>
void UnrollTemplateTypes(Library &library, TypeList &types, bool registerIfMissing = true)
{
    UnrollTemplateTypes<0u, Args...>(library, types, registerIfMissing);
}

template <typename ...Args>
void UnrollArgumentNames(Library &library, ParameterList &params, const ArgNames &args)
{
    auto paramTypes = library.GetTypes<Args...>();
    auto paramTypesSize = paramTypes.size();
    for (auto idx = 0u; idx < paramTypesSize; ++idx)
    {
        string name;

        if (idx < args.size())
        {
            name = *(args.begin() + idx);
        }
        else
        {
            char temp[8];
            sprintf_s(temp, "param%d", idx);
            name = temp;
        }

        Parameter param(name, paramTypes[idx]);
        params.push_back(param);
    }
}

template <typename ...Args>
string BuildTemplateNameFromArguments(StringParam name, Library &library)
{
    TypeList types;
    Internal::UnrollTemplateTypes<Args...>(library, types);

    string paramListStr;
    auto size = types.size();
    for (auto i = 0; i < size; ++i)
    {
        if (types[i] != nullptr)
        {
            paramListStr += types[i]->Name;
        }
        if (i < size - 1)
        {
            paramListStr += ", ";
        }
    }

    return String::Format("%s<%s>", name.c_str(), paramListStr.c_str());
}

template <typename T>
string GetQualifierString()
{
    if (std::is_reference<T>::value)
    {
        return " &";
    }
    if (std::is_pointer<T>::value)
    {
        return " *";
    }
    return string();
}

inline string GetQualifierString(TypeQualifier qualifier)
{
    switch (qualifier)
    {
    case TypeQualifier::Reference:
        return " &";
    case TypeQualifier::Pointer:
        return " *";
    default:
        return string();
    }
}

}

}
