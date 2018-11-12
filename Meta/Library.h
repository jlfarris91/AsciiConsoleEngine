#pragma once
#include <unordered_map>
#include "TypeBuilder.h"

namespace Meta
{
    
class Type;

struct InitializationParams
{
    explicit InitializationParams(TypeBuilder &builder)
        : builder(builder) {}
    TypeBuilder &builder;
    size_t hashcode = 0u;
    bool isTemplated = false;
};

/// <summary>Contains reflected type information.</summary>
class Library
{
public:
    /// <summary>Constructs a new instance of a Library.</summary>
    Library();
    virtual ~Library();

    /// <summary>Registers a type with the library.</summary>
    Type *RegisterType(Type *type);

    /// <summary>Registers a type with the library.</summary>
    template <typename T>
    Type *RegisterType();

    void RegisterTypeAlias(Type *type, StringParam name);
    void RegisterTypeAlias(Type *type, size_t hashcode);

    /// <summary>Registers a primitive type with the library.</summary>
    /// <param name="name">The name of the primitive type.</param>
    template <typename T>
    typename std::enable_if<!std::is_void<T>::value, Type *>::type
    RegisterPrimitive(StringParam name);

    /// <summary>Registers a primitive type with the library.</summary>
    /// <param name="name">The name of the primitive type.</param>
    template <typename T>
    typename std::enable_if<std::is_void<T>::value, Type *>::type
    RegisterPrimitive(StringParam name);

    /// <summary>Returns a registered type.</summary>
    /// <param name="registerIfMissing">
    /// Should the type be registered automatically if not already?
    /// </param>
    template <typename T>
    Type *GetType(bool registerIfMissing = true);

    /// <summary>Returns a registered type by name.</summary>
    /// <param name="name">The name of the type.</param>
    Type *GetType(StringParam name);

    /// <summar>Gets type info by hashcode.</summary>
    /// <param name="hashcode">The hashcode of the type.</param>
    Type *GetType(size_t hashcode);

    template <typename ...Args>
    TypeList GetTypes(bool registerIfMissing = true);

    Type *RegisterTemplateType(StringParam name);
    Type *GetTemplateType(StringParam name);

    /// <summary>Deletes all types registered with this library.</summary>
    void Clear();

    virtual size_t GetTemplateHashCode(StringParam type);

    typedef bool(*RegistrationFunc)(const InitializationParams &);
    RegistrationFunc RegistrationFallback = nullptr;

private:

    void RegisterDefaults();

    std::unordered_map<string, Type *> typeNameLookup;
    std::unordered_map<size_t, Type *> typeHashLookup;
    std::unordered_map<string, Type *> templateTypeNameLookup;

    TypeCollection types;
    TypeCollection templateTypes;
};

/// <summary>Global library instance.</summary>
extern Library *gLibrary;


}

#include "Library.inl"