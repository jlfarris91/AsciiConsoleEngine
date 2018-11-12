#pragma once
#include "Method.h"
#include "TypeQualifier.h"
#include "Type.h"

namespace Meta
{

class Field;
class Library;
class Property;
class Type;

enum class FieldModifier
{
    None,
    ReadOnly
};

typedef std::initializer_list<const char *> ArgNames;

class TypeBuilder
{
public:
    explicit TypeBuilder(Library &library);
    explicit TypeBuilder(Library &library, StringParam name);
    ~TypeBuilder();

    /// <summary>Sets the name of the type.</summary>
    /// <param name="size">The name of the type."</param>
    void SetName(StringParam name) const;

    void AddAlias(StringParam name) const;
    void AddAlias(size_t hashcode) const;

    template <typename ...Args>
    void AddTemplatedAlias(StringParam name) const;

    /// TODO: Support more than 1 argument
    template <typename ...Args>
    void SetTemplatedName(StringParam name) const;

    /// <summary>Sets the size of the type.</summary>
    /// <param name="size">The size of the type."</param>
    void SetSize(size_t size);

    /// <summary>Sets the hash code of the type.</summary>
    void SetHashCode(size_t hashCode);

    template <typename T>
    Method *AddConstructor();

    template <typename T, typename U, typename ...Args>
    Method *AddConstructor(const ArgNames &args = {});

    /// <summary>Adds a new method to the type.</summary>
    /// <param name="name">The name of the method.</param>
    /// <param name="func">The member function pointer.</param>
    /// <param name="argNames">A collection of strings representing the argument names.</param>
    template <typename T = void, typename ReturnT = void, typename ...Args>
    Method *AddMethod(StringParam name, ReturnT(T::*func)(Args...), const ArgNames &args = {});

    /// <summary>Adds a new method to the type.</summary>
    /// <param name="name">The name of the method.</param>
    /// <param name="func">The member function pointer.</param>
    /// <param name="argNames">A collection of strings representing the argument names.</param>
    template <typename T = void, typename ReturnT = void, typename ...Args>
    Method *AddMethod(StringParam name, ReturnT(T::*func)(Args...) const, const ArgNames &args = {});

    /// <summary>Adds a new method to the type.</summary>
    /// <param name="name">The name of the method.</param>
    /// <param name="func">The member function pointer.</param>
    /// <param name="argNames">A collection of strings representing the argument names.</param>
    template <typename T = void, typename ReturnT = void, typename ...Args>
    Method *AddMethod(StringParam name, ReturnT(*func)(Args...), const ArgNames &args = {});

    /// <summary>Adds a new field to the type.</summary>
    /// <param name="name">The name of the field.</param>
    /// <param name="func">The member pointer.</param>
    template <typename T, typename FieldT>
    Field *AddField(StringParam name, FieldT T::*fieldPtr);

    /// <summary>Adds a new field to the type.</summary>
    /// <param name="name">The name of the field.</param>
    /// <param name="func">The member pointer.</param>
    template <typename FieldT>
    Field *AddField(StringParam name, FieldT *fieldPtr);

    /// <summary>Adds a new field to the type.</summary>
    /// <param name="name">The name of the field.</param>
    /// <param name="func">The member pointer.</param>
    template <typename T, typename FieldT>
    Field *AddReadOnlyField(StringParam name, FieldT T::*fieldPtr);

    /// <summary>Adds a new field to the type.</summary>
    /// <param name="name">The name of the field.</param>
    /// <param name="func">The member pointer.</param>
    template <typename FieldT>
    Field *AddReadOnlyField(StringParam name, FieldT *fieldPtr);

    /// <summary>Adds a new method to the type.</summary>
    /// <param name="name">The name of the method.</param>
    /// <param name="func">The member function pointer.</param>
    template <typename T, typename ReturnT, typename ValueT>
    Property *AddProperty(StringParam name, ReturnT(T::*getter)(void), void(T::*setter)(ValueT));

    /// <summary>Adds a new method to the type.</summary>
    /// <param name="name">The name of the method.</param>
    /// <param name="func">The member function pointer.</param>
    template <typename T, typename ReturnT, typename ValueT>
    Property *AddProperty(StringParam name, ReturnT(T::*getter)(void) const, void(T::*setter)(ValueT));

    /// <summary>Adds a new read-only property to the type.</summary>
    /// <param name="name">The name of the property.</param>
    /// <param name="func">The member function pointer.</param>
    template <typename T, typename ReturnT>
    Property *AddReadOnlyProperty(StringParam name, ReturnT(T::*getter)(void));

    /// <summary>Adds a new read-only property to the type.</summary>
    /// <param name="name">The name of the property.</param>
    /// <param name="func">The member function pointer.</param>
    template <typename T, typename ReturnT>
    Property *AddReadOnlyProperty(StringParam name, ReturnT(T::*getter)(void) const);

    /// <summary>Sets the base type.</summary>
    template <typename BaseT>
    Type *AddBase();

    Type *AddTemplate(StringParam name);

    template <typename ...Args>
    void AddTemplateArguments();

    template <typename T>
    void SetDestructor();

    void SetConcreteType(Type *type);

    template <typename T>
    void SetConcreteType();

    /// <summary>Builds the type.</summary>
    Type *Build();

    Getter(Type *, Target);
    PropertyR(Type *, Target);

    Getter(Meta::Library &, Library);
    PropertyR(Meta::Library &, Library);

    /// <summary>Determines if the TypeBuilder is responsible for deleting the Type.</summary>
    bool IsOwner = true;

protected:
    Meta::Library &library;
    Type *target;

    template <typename ReturnT, typename ...Args>
    void InitializeMethod(Method *method, StringParam name, const ArgNames &args);

    template <typename FieldT>
    Field *InitializeField(StringParam name);

    void IsClass(bool value);
    void IsStruct(bool value);
    void IsAbstract(bool value);
    void IsUnion(bool value);
    void SetQualifier(TypeQualifier value);
};

template <typename T>
class TypedTypeBuilder : public TypeBuilder
{
public:
    // Non-void types
    explicit TypedTypeBuilder(Meta::Library &library);
    explicit TypedTypeBuilder(Meta::Library &library, StringParam name);

private:

    void SetDefaultTypeInfo();

    template <typename T2>
    typename std::enable_if<
        std::is_reference<T2>::value &&
        !std::is_pointer<T2>::value,
    void>::type
    SetSpecificTypeInfo();

    template <typename T2>
    typename std::enable_if<
        !std::is_reference<T2>::value &&
        std::is_pointer<T2>::value,
    void>::type
    SetSpecificTypeInfo();

    template <typename T2>
    typename std::enable_if<
        !std::is_reference<T2>::value &&
        !std::is_pointer<T2>::value,
    void>::type
    SetSpecificTypeInfo();
};

}

#include "TypeBuilder.inl"