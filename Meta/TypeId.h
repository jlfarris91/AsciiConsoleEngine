#pragma once

namespace Meta
{

namespace Internal
{

template <typename T>
class HashCodeWrapper
{
};

template <typename T>
class TemplateTypeWrapper
{ 
};

template <typename T>
string CleanupName(StringParam name)
{
    string result;
    result = name.Remove("struct ");
    result = name.Remove("class ");
    return result;
}

}

template <typename, typename = void>
struct TypeId;

template <typename T>
struct TypeId<T, typename std::enable_if<!std::is_reference<T>::value>::type>
{
    typedef typename std::remove_const<T>::type TypeT;
    static size_t hash_code()
    {
        return typeid(TypeT).hash_code();
    }
    static StringParam name()
    {
        static string name = typeid(TypeT).name();
        return name;
    }
    static Type *type(Library *library = nullptr)
    {
        return Meta::GetType<T>(library);
    }
};

template <typename T>
struct TypeId<T, typename std::enable_if<std::is_reference<T>::value>::type>
{
    typedef typename std::remove_const<T>::type TypeT;
    static size_t hash_code()
    {
        return typeid(Internal::TemplateTypeWrapper<TypeT>).hash_code();
    }
    static StringParam name()
    {
        static string name = typeid(TypeT).name();
        return name;
    }
    static Type *type(Library *library = nullptr)
    {
        return Meta::GetType<T>(library);
    }
};

}
