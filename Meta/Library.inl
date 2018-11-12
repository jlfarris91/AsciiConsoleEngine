#pragma once
#include "TypeId.h"

namespace Meta
{

template <typename T>
Type *Library::RegisterType()
{
    typedef typename Internal::Clean<T>::type TypeT;
    auto type = Internal::GetOrInitializeType<TypeT>(this);
    //auto name = type->Name;

    // Throw an exception if the user tries to register the same type twice
    //auto typeNameIter = typeNameLookup.find(name);
    //if (typeNameIter != typeNameLookup.end())
    //{
    //    throw MetaException(
    //        "TypeAlreadyRegistered",
    //        "Type with name '%s' has already been registered with the library.",
    //        name.c_str());
    //}

    RegisterType(type);
    return type;
}

template <typename T>
typename std::enable_if<!std::is_void<T>::value, Type *>::type
Library::RegisterPrimitive(StringParam name)
{
    typedef typename Internal::Clean<T>::type TypeT;
    auto type = new Type;
    type->name = name;
    type->size = sizeof(TypeT);
    type->hashCode = TypeId<TypeT>::hash_code();
    typeNameLookup[type->name] = type;
    typeHashLookup[type->hashCode] = type;
    return type;
}

template <typename T>
typename std::enable_if<std::is_void<T>::value, Type *>::type
Library::RegisterPrimitive(StringParam name)
{
    static_assert(false ,"Cannot register type void, it is registered by default.");
    return;
}

template <typename T>
Type *Library::GetType(bool registerIfMissing)
{
    typedef typename Internal::Clean<T>::type TypeT;
    typedef typename Internal::ArrayToPtr<TypeT>::type NonArrayT;
    auto hash = TypeId<NonArrayT>::hash_code();
    // Lookup type by type hash
    auto iter = typeHashLookup.find(hash);
    if (iter == typeHashLookup.end())
    {
        if (registerIfMissing)
        {
            // Register the type if it hasn't already been registered
            return RegisterType<NonArrayT>();
        }
        return nullptr;
    }
    return iter->second;
}

template <typename ...Args>
TypeList Library::GetTypes(bool registerIfMissing)
{
    TypeList types;
    Internal::UnrollTemplateTypes<Args...>(*this, types, registerIfMissing);
    return types;
}

}
