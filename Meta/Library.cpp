#include "Library.h"

namespace Meta
{

//Library::RegistrationFunc Library::gRegistrationFallback = nullptr;
Library *gLibrary = new Library;

Library::Library()
{
    RegisterDefaults();
}

Library::~Library()
{
    Clear();
}

Type *Library::RegisterType(Type *type)
{
    if (!type->name.Empty())
    {
        RegisterTypeAlias(type, type->Name);
    }
    if (type->hashCode != 0u)
    {
        RegisterTypeAlias(type, type->HashCode);
    }
    return type;
}

void Library::RegisterTypeAlias(Type *type, StringParam aliasName)
{
    if (type == nullptr)
    {
        throw MetaException("NullObject", "Trying to register an alias for a null type.");
    }

    if (aliasName == string())
    {
        throw MetaException("InvalidAliasName", "Alias name must not be empty.");
    }

    typeNameLookup[aliasName] = type;
    types.insert(type);
}

void Library::RegisterTypeAlias(Type *type, size_t hashcode)
{
    if (type == nullptr)
    {
        throw MetaException("NullObject", "Trying to register an alias for a null type.");
    }

    if (hashcode == 0u)
    {
        throw MetaException("InvalidAliasHashcode", "Alias hashcode cannot be zero.");
    }

    typeHashLookup[hashcode] = type;
    types.insert(type);
}

size_t Library::GetTemplateHashCode(StringParam type)
{
    auto hash_code = Internal::HashCodeAlgorithm::hash_code(type);
    if (this->GetType(hash_code) != nullptr)
    {
        // TODO: Add fallback
        __debugbreak();
    }
    return hash_code;
}
    
Type *Library::GetType(StringParam name)
{
    auto iter = typeNameLookup.find(name);
    if (iter != typeNameLookup.end())
    {
        return iter->second;
    }
    return nullptr;
}

Type *Library::GetType(size_t hashcode)
{
    auto iter = typeHashLookup.find(hashcode);
    if (iter != typeHashLookup.end())
    {
        return iter->second;
    }
    return nullptr;
}

Type *Library::RegisterTemplateType(StringParam name)
{
    auto builder = TypeBuilder(*this);
    builder.SetName(name);
    builder.SetHashCode(this->GetTemplateHashCode(name));
    auto type = builder.Build();
    this->templateTypeNameLookup[name] = type;
    this->templateTypes.insert(type);
    // Register as a regular type too
    this->RegisterType(type);
    return type;
}

Type *Library::GetTemplateType(StringParam name)
{
    auto &&iter = templateTypeNameLookup.find(name);
    if (iter == templateTypeNameLookup.end())
    {
        return RegisterTemplateType(name);
    }
    return iter->second;
}

void Library::Clear()
{
    for (auto type : types)
    {
        delete type;
    }
    typeNameLookup.clear();
    typeHashLookup.clear();
    types.clear();
}

#define _RegisterPrimitiveType(type) \
    { \
        auto builder = TypedTypeBuilder<type>(*this); \
        builder.SetName(#type); \
        auto createdType = builder.Build(); \
        RegisterType(createdType); \
    }

#define RegisterPrimitiveType(type) \
    _RegisterPrimitiveType(type); \
    _RegisterPrimitiveType(type *); \
    _RegisterPrimitiveType(type &);

typedef unsigned int uint;
typedef unsigned char uchar;
typedef unsigned long ulong;

void Library::RegisterDefaults()
{
    {
        auto builder = TypeBuilder(*this);
        builder.SetName("void");
        builder.SetHashCode(TypeId<void>::hash_code());
        auto createdType = builder.Build();
        RegisterType(createdType);
    }

    {
        auto builder = TypeBuilder(*this);
        builder.SetName("void *");
        builder.SetHashCode(TypeId<void*>::hash_code());
        auto createdType = builder.Build();
        RegisterType(createdType);
    }
    
    RegisterPrimitiveType(int);
    RegisterPrimitiveType(unsigned);
    RegisterPrimitiveType(unsigned int);
    RegisterPrimitiveType(float);
    RegisterPrimitiveType(double);
    RegisterPrimitiveType(bool);
    RegisterPrimitiveType(long);
    RegisterPrimitiveType(long long);
    RegisterPrimitiveType(char);
    RegisterPrimitiveType(unsigned char);
    RegisterPrimitiveType(unsigned __int64);

    {
        auto builder = TypedTypeBuilder<std::string>(*this);
        builder.SetName("String");
        auto type = builder.Target;
        RegisterType(type);

        builder.AddConstructor<std::string>();
        builder.AddConstructor<std::string, const char *>();
        builder.AddConstructor<std::string, const std::string &>();
        builder.AddReadOnlyProperty("Length", &std::string::length);
        builder.AddReadOnlyProperty("Size", &std::string::size);
        builder.AddMethod("CStr", &std::string::c_str);
        builder.AddMethod("PushBack", &std::string::push_back);
        builder.AddMethod<std::string, char &, size_t>("Get", &std::string::operator[], { "index" });
        auto createdType = builder.Build();
        RegisterType(createdType);

        Internal::GetOrInitializeType<std::string &>(this);
        Internal::GetOrInitializeType<std::string *>(this);
    }

    RegisterTemplateType("list");
    RegisterTemplateType("vector");    
}

}