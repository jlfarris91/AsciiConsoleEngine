#pragma once
#include "Utility.h"
#include <vector>

namespace Meta
{

class Type;
class Library;
class TypeBuilder;

namespace Internal
{

extern const char *QualifiedTypeFormatString;

template <typename T>
struct IsConcreteWithInitializeMeta
{
    static constexpr bool value = !std::is_void<T>::value && IsConcrete<T>::value && HasMember<T, HashMember_InitializeMeta>::value;
};

template <typename T>
struct IsConcreteWithoutInitializeMeta
{
    static constexpr bool value = !std::is_void<T>::value && IsConcrete<T>::value && !HasMember<T, HashMember_InitializeMeta>::value;
};

template <typename T>
struct IsNotVoidAndNotConcreteWithInitializeMeta
{
    static constexpr bool value = !std::is_void<T>::value && !IsConcrete<T>::value && !HasMember<T, HashMember_InitializeMeta>::value;
};

// Non-void, non-primitive types
template <typename T>
typename std::enable_if<IsConcreteWithInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library = nullptr);

template <typename T>
typename std::enable_if<IsConcreteWithoutInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library = nullptr);

template <typename T>
typename std::enable_if<IsNotVoidAndNotConcreteWithInitializeMeta<T>::value, Type *>::type
GetOrInitializeType(Library *library = nullptr);

// Primitive types
template <typename T>
typename std::enable_if<std::is_void<T>::value, Type *>::type
GetOrInitializeType(Library *library = nullptr);

}

template <typename T>
Type *GetType(Library *library = nullptr);

Type *GetType(StringParam name, Library *library = nullptr);

template <typename ...Args>
TypeList GetTypes(Library *library = nullptr);

template <typename T>
struct ReflectType
{
    static bool InitializeMeta(TypeBuilder &);
};

template <typename T>
struct ReflectTemplateType;

}

#include "Meta.inl"