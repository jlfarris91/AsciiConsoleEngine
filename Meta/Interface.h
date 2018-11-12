#pragma once
#include "Meta.h"
#include "Type.h"
#include "TypeBuilder.h"

#define ReflectTypeAs(type, name) \
    typedef type this_type; \
    virtual Meta::Type *type::GetType() const \
    { \
        return Meta::Internal::GetOrInitializeType<type>(); \
    } \
    static StringParam GetTypeName() { static string typeName = name; return typeName; } \
    static void type::InitializeMeta(Meta::TypeBuilder &builder)

#define ReflectType(type) \
    ReflectTypeAs(type, #type)

#define _GenerateTemplatedTypeName(type) #type
#define GenerateTemplatedTypeName(type, ...) _GenerateTemplatedTypeName(type##<__VA_ARGS__>)

#define ReflectTemplatedTypeAs(type, name, ...) \
    typedef type##<__VA_ARGS__> this_type; \
    virtual Meta::Type *type::GetType() const \
    { \
        return Meta::Internal::GetOrInitializeType<type##<__VA_ARGS__>>(); \
    } \
    static StringParam GetTypeName() { static string typeName = name; return typeName; } \
    static void type::InitializeMeta(Meta::TypeBuilder &builder)

#define ReflectTemplatedType(type, ...) \
    ReflectTemplatedTypeAs(type, GenerateTemplatedTypeName(type, __VA_ARGS__), __VA_ARGS__)

#define DefineReflectedType(type) \
    void type##::InitializeMeta(Meta::TypeBuilder &builder)

#define DefineReflectedTemplatedType(type, ...) \
    void type<__VA_ARGS__>##::InitializeMeta(Meta::TypeBuilder &builder)