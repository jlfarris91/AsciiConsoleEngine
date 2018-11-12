#pragma once
#include "Library.h"
#include <iostream>

namespace Meta
{

namespace Internal
{

template <typename T>
typename std::enable_if<IsConcreteWithInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library)
{
    typedef typename Internal::Clean<T>::type TypeT;

    if (library == nullptr)
    {
        library = gLibrary;
    }

    auto type = library->GetType<TypeT>(false);
    if (type == nullptr)
    {
        auto builder = TypedTypeBuilder<TypeT>(*library);
        builder.SetName(TypeT::GetTypeName());

        // Add to library before initializing meta for self-reference        
        type = builder.Target;
        library->RegisterType(type);
        builder.IsOwner = false;

        // Initialize the type
        TypeT::InitializeMeta(builder);

        // TODO: Unregister Type when InitializeMeta throws an exception
    }

    return type;
}

template <typename T>
typename std::enable_if<IsConcreteWithoutInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library)
{
    typedef typename Internal::Clean<T>::type TypeT;

    if (library == nullptr)
    {
        library = gLibrary;
    }

    auto type = library->GetType<TypeT>(false);
    if (type == nullptr)
    {
        auto &&hashcode = TypeId<TypeT>().hash_code();
        auto &&builder = TypedTypeBuilder<TypeT>(*library);
        type = builder.Target;
        library->RegisterType(type);
        ReflectType<TypeT>::InitializeMeta(builder);
        type = builder.Build();
        library->RegisterType(type);

        // TODO: Unregister Type when InitializeMeta throws an exception
    }

    return type;
}

template <typename T>
typename std::enable_if<IsNotVoidAndNotConcreteWithInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library)
{
    typedef typename Internal::Clean<T>::type TypeT;
    typedef typename Concrete<TypeT>::type ConcreteT;

    if (library == nullptr)
    {
        library = gLibrary;
    }

    auto type = library->GetType<TypeT>(false);
    if (type == nullptr)
    {
        const Type *concreteType = library->GetType<ConcreteT>();

        const string name = String::Format(
            QualifiedTypeFormatString,
            concreteType->Name.c_str(),
            Internal::GetQualifierString<TypeT>().c_str());

        auto builder = TypedTypeBuilder<TypeT>(*library);
        builder.SetName(name);
        type = builder.Build();
        library->RegisterType(type);
    }

    return type;
}

template <typename T>
typename std::enable_if<std::is_void<T>::value, Type *>::type
GetOrInitializeType(Library *library)
{
    typedef typename Internal::Clean<T>::type TypeT;
    if (library == nullptr)
    {
        library = gLibrary;
    }
    return library->GetType<TypeT>(false);
}

}

template <typename T>
Type *GetType(Library *library)
{
    typedef typename Internal::Clean<T>::type TypeT;
    return Internal::GetOrInitializeType<TypeT>(library);
}

template <typename ...Args>
TypeList GetTypes(Library *library)
{
    TypeList types;
    Internal::UnrollTemplateTypes<Args...>(library, types);
    return std::move<Args...>(types);
}

template <typename T>
bool ReflectType<T>::InitializeMeta(TypeBuilder &builder)
{
    static auto initialized = false;

    if (!initialized && builder.Library.RegistrationFallback)
    {
        initialized = true;
        auto params = InitializationParams(builder);
        params.hashcode = TypeId<T>::hash_code();
        if (!builder.Library.RegistrationFallback(params))
        {
            std::cout << "Type '" << TypeId<T>::name() << "' not registered." << std::endl;
            builder.SetName(TypeId<T>::name());
        }
    }

    return false;
}
    
}

