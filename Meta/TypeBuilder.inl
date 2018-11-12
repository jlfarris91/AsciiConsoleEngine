#pragma once
#include "Method.h"
#include "Generic.h"
#include "Type.h"
#include "MetaException.h"
#include "Field.h"
#include "Property.h"
#include "TypeId.h"
#include "Utility.h"

namespace Meta
{

template <typename ...Args>
void TypeBuilder::SetTemplatedName(StringParam name) const
{
    auto &&templatedName = Internal::BuildTemplateNameFromArguments<Args...>(name, library);
    SetName(templatedName);
}

template <typename ...Args>
void TypeBuilder::AddTemplatedAlias(StringParam name) const
{
    auto &&templatedName = Internal::BuildTemplateNameFromArguments<Args...>(name, library);
    AddAlias(templatedName);
}

template <typename T>
Method *TypeBuilder::AddConstructor()
{
    auto method = new Method();
    method->returnType = library.GetType<void>();
    method->name = "ctor";
    method->func = Generic::Wrapper::WrapDefaultConstructor<T>();
    method->isConst = true;
    method->isStatic = true;
    method->type = target;
    target->constructors.insert(method);
    return method;
}

template <typename T, typename U, typename ...Args>
Method *TypeBuilder::AddConstructor(const ArgNames &args)
{
    auto method = new Method();
    method->returnType = library.GetType<void>();
    method->name = "ctor";
    method->func = Generic::Wrapper::WrapConstructor<T, U, Args...>();
    method->isConst = true;
    method->isStatic = true;
    method->type = target;
    Internal::UnrollArgumentNames<Args...>(library, method->params, args);
    target->constructors.insert(method);

    return method;
}

/// <summary>Adds a new method to the type.</summary>
/// <param name="name">The name of the method.</param>
/// <param name="func">The member function pointer.</param>
/// <param name="argNames">A collection of strings representing the argument names.</param>
template <typename T, typename ReturnT, typename ...Args>
Method *TypeBuilder::AddMethod(StringParam name, ReturnT(T::*func)(Args...), const ArgNames &args)
{
    auto &&method = new Method;
    method->isConst = false;
    method->isStatic = false;
    method->func = Generic::Wrapper::Wrap<T, ReturnT, Args...>(func);
    InitializeMethod<ReturnT, Args...>(method, name, args);
    return method;
}

/// <summary>Adds a new method to the type.</summary>
/// <param name="name">The name of the method.</param>
/// <param name="func">The member function pointer.</param>
/// <param name="argNames">A collection of strings representing the argument names.</param>
template <typename T, typename ReturnT, typename ...Args>
Method *TypeBuilder::AddMethod(StringParam name, ReturnT(T::*func)(Args...) const, const ArgNames & args)
{
    auto &&method = new Method;
    method->isConst = true;
    method->isStatic = false;
    method->func = Generic::Wrapper::Wrap<T, ReturnT, Args...>(func);
    InitializeMethod<ReturnT, Args...>(method, name, args);
    return method;
}

/// <summary>Adds a new method to the type.</summary>
/// <param name="name">The name of the method.</param>
/// <param name="func">The member function pointer.</param>
/// <param name="argNames">A collection of strings representing the argument names.</param>
template <typename T, typename ReturnT, typename ...Args>
Method *TypeBuilder::AddMethod(StringParam name, ReturnT(*func)(Args...), const ArgNames & args)
{
    auto &&method = new Method;
    method->isConst = false;
    method->isStatic = true;
    method->func = Generic::Wrapper::Wrap(func);
    InitializeMethod<ReturnT, Args...>(method, name, args);
    return method;
}

template <typename ReturnT, typename ...Args>
void TypeBuilder::InitializeMethod(Method *method, StringParam name, const ArgNames &args)
{
    method->name = name;
    method->type = target;

    method->returnType = library.GetType<ReturnT>();
    if (method->returnType == nullptr)
    {
        delete method;
        throw new MetaException(
            "TypeNotRegistered",
            "Return type for method %s on type %s could not be found.",
            name.c_str(),
            target->name.c_str());
    }

    // Fill out the argument list
    Internal::UnrollArgumentNames<Args...>(library, method->params, args);

    // If this method has already been registered remove it
    auto &&existing = target->GetMethod(method->Name, method->Parameters);
    if (existing != nullptr)
    {
        target->methods.erase(existing);
        target->members.erase(existing);
    }

    target->methods.insert(method);
    target->members.insert(method);
}

template <typename T, typename FieldT>
Field *TypeBuilder::AddField(StringParam name, FieldT T::*fieldPtr)
{
    if (target->GetField(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A field named '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto field = InitializeField<FieldT>(name);
    field->getter = Generic::Wrapper::WrapGetter(fieldPtr);
    field->setter = Generic::Wrapper::WrapSetter(fieldPtr);
    field->isConst = false;
    field->isStatic = false;
    return field;
}

template <typename FieldT>
Field *TypeBuilder::AddField(StringParam name, FieldT *fieldPtr)
{
    auto field = InitializeField<FieldT>(name);
    field->getter = Generic::Wrapper::WrapGetter(fieldPtr);
    field->setter = Generic::Wrapper::WrapSetter(fieldPtr);
    field->isConst = false;
    field->isStatic = true;
    return field;
}

template <typename T, typename FieldT>
Field *TypeBuilder::AddReadOnlyField(StringParam name, FieldT T::*fieldPtr)
{
    auto field = InitializeField<FieldT>(name);
    field->getter = Generic::Wrapper::WrapGetter(fieldPtr);
    field->isConst = false;
    field->isStatic = false;
    return field;
}

template <typename FieldT>
Field *TypeBuilder::AddReadOnlyField(StringParam name, FieldT *fieldPtr)
{
    auto field = InitializeField<FieldT>(name);
    field->getter = Generic::Wrapper::WrapGetter(fieldPtr);
    field->isConst = false;
    field->isStatic = true;
    return field;
}

template <typename FieldT>
Field *TypeBuilder::InitializeField(StringParam name)
{
    if (target->GetField(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A field named '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto field = new Field();
    field->name = name;
    field->type = library.GetType<FieldT>();
    field->isArray = std::is_array<FieldT>::value;
    target->fields.insert(field);
    target->members.insert(field);

    return field;
}

template <typename T, typename ReturnT, typename ValueT>
Property *TypeBuilder::AddProperty(StringParam name, ReturnT(T::*getter)(void), void(T::*setter)(ValueT))
{
    if (target->GetProperty(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A property named '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto prop = new Property;
    prop->name = name;

    if (getter == nullptr && setter == nullptr)
    {
        throw MetaException("NullObject", "Getter and setter cannot both be null.");
    }

    if (getter != nullptr)
    {
        auto getterMethod = new Method;
        getterMethod->returnType = library.GetType<ReturnT>();
        getterMethod->func = Generic::Wrapper::Wrap<T, ReturnT>(getter);
        getterMethod->name = "getter";
        getterMethod->isConst = false;
        getterMethod->isStatic = false;
        prop->getter = getterMethod;
    }

    if (setter != nullptr)
    {
        auto setterMethod = new Method;
        setterMethod->returnType = library.GetType<ReturnT>();
        setterMethod->func = Generic::Wrapper::Wrap<T, void, ValueT>(setter);
        setterMethod->name = "getter";
        setterMethod->isConst = false;
        setterMethod->isStatic = false;
        prop->getter = setterMethod;
    }

    prop->type = library.GetType<ReturnT>();
    prop->isConst = false;
    prop->isStatic = false;
    target->properties.insert(prop);
    target->members.insert(prop);
    return prop;
}

template <typename T, typename ReturnT, typename ValueT>
Property *TypeBuilder::AddProperty(StringParam name, ReturnT(T::*getter)(void) const, void(T::*setter)(ValueT))
{
    if (target->GetProperty(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A property named '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto prop = new Property;
    prop->name = name;

    if (getter == nullptr && setter == nullptr)
    {
        throw MetaException("NullObject", "Getter and setter cannot both be null.");
    }

    if (getter != nullptr)
    {
        auto getterMethod = new Method;
        getterMethod->returnType = library.GetType<ReturnT>();
        getterMethod->func = Generic::Wrapper::Wrap<T, ReturnT>(getter);
        getterMethod->name = "getter";
        getterMethod->IsConst = true;
        getterMethod->IsStatic = false;
        prop->getter = getterMethod;
    }

    if (setter != nullptr)
    {
        auto setterMethod = new Method;
        setterMethod->returnType = library.GetType<ReturnT>();
        setterMethod->func = Generic::Wrapper::Wrap<T, void, ValueT>(setter);
        setterMethod->name = "setter";
        setterMethod->IsConst = false;
        setterMethod->IsStatic = false;
        prop->getter = setterMethod;
    }

    prop->type = library.GetType<ReturnT>();
    prop->isConst = false;
    prop->isStatic = false;
    target->properties.insert(prop);
    target->members.insert(prop);
    return prop;
}

template <typename T, typename ReturnT>
Property *TypeBuilder::AddReadOnlyProperty(StringParam name, ReturnT(T::*getter)(void))
{
    if (target->GetProperty(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A propertyd name '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto prop = new Property;
    prop->name = name;

    if (getter == nullptr)
    {
        throw MetaException("NullObject", "Getter must not be null.");
    }

    auto getterMethod = new Method;
    getterMethod->returnType = library.GetType<ReturnT>();
    getterMethod->func = Generic::Wrapper::Wrap<T, ReturnT>(getter);
    getterMethod->name = "getter";
    getterMethod->isConst = false;
    getterMethod->isStatic = false;
    prop->getter = getterMethod;

    prop->type = library.GetType<ReturnT>();
    prop->isConst = false;
    prop->isStatic = false;
    target->properties.insert(prop);
    target->members.insert(prop);
    return prop;
}

template <typename T, typename ReturnT>
Property *TypeBuilder::AddReadOnlyProperty(StringParam name, ReturnT(T::*getter)(void) const)
{
    if (target->GetProperty(name) != nullptr)
    {
        throw MetaException(
            "MemberAlreadyRegistered",
            "A propertyd name '%s' has already been registered with type '%s'.",
            name.c_str(),
            target->name.c_str());
    }

    auto prop = new Property;
    prop->name = name;

    if (getter == nullptr)
    {
        throw MetaException("NullObject", "Getter must not be null.");
    }

    auto getterMethod = new Method;
    getterMethod->returnType = library.GetType<ReturnT>();
    getterMethod->func = Generic::Wrapper::Wrap<T, ReturnT>(getter);
    getterMethod->name = "getter";
    getterMethod->isConst = true;
    getterMethod->isStatic = false;
    prop->getter = getterMethod;

    prop->type = library.GetType<ReturnT>();
    prop->isConst = false;
    prop->isStatic = false;
    target->properties.insert(prop);
    target->members.insert(prop);
    return prop;
}

template <typename BaseT>
Type *TypeBuilder::AddBase()
{
    Type *baseType = library.GetType<BaseT>();
    if (baseType == nullptr)
    {
        throw MetaException("TypeNotRegistered", "Base type is not registered with the library.");
    }

    if (baseType == target)
    {
        throw MetaException("SelfRegistration", "Cannot set self type as base type.");
    }

    // Add to base type list
    target->baseTypes.insert(baseType);

    // Add this type to the base type derived types list
    baseType->derivedTypes.insert(target);

    for (auto field : baseType->fields)
    {
        auto &&existing = target->GetField(field->Name);
        if (existing == nullptr)
        {
            target->fields.insert(field);
            target->members.insert(field);
        }
    }

    for (auto prop : baseType->properties)
    {
        auto &&existing = target->GetProperty(prop->Name);
        if (existing == nullptr)
        {
            target->properties.insert(prop);
            target->members.insert(prop);
        }
    }

    for (auto method : baseType->methods)
    {
        auto &&existing = target->GetMethod(method->Name, method->Parameters);
        if (existing == nullptr)
        {
            target->methods.insert(method);
            target->members.insert(method);
        }
    }

    return baseType;
}

namespace Internal
{
    
template <unsigned int idx>
void UnrollTemplateArguments(Library &, TypeList &)
{
}

template <unsigned int idx, typename T, typename ...Args>
void UnrollTemplateArguments(Library &library, TypeList &args)
{
    auto type = library.GetType<T>();
    args.push_back(type);
    UnrollTemplateArguments<idx + 1, Args...>(library, args);
}

template <typename ...Args>
void UnrollTemplateArguments(Library &library, TypeList &args)
{
    UnrollTemplateArguments<0u, Args...>(library, args);
}

}

template <typename ...Args>
void TypeBuilder::AddTemplateArguments()
{
    Internal::UnrollTemplateArguments<Args...>(library, target->templateTypes);
}

template <typename T>
void TypeBuilder::SetConcreteType()
{
    typedef typename std::remove_reference<typename std::remove_pointer<T>::type>::type ConcreteT;
    SetConcreteType(library.GetType<ConcreteT>());
}

template <typename T>
void TypeBuilder::SetDestructor()
{
    auto method = new Method;
    method->memberType = MemberType::Method;
    method->func = Generic::Wrapper::WrapDestructor<T>();
    method->returnType = library.GetType<void>();
    method->name = "destructor";
    target->destructor = method;
}

/// <summary>
/// Creates a new instance of the TypedTypeBuilder using the template type to
/// automatically deduce type information.
/// </summary>
template <typename T>
TypedTypeBuilder<T>::TypedTypeBuilder(Meta::Library &library)
    : TypeBuilder(library)
{
    SetDefaultTypeInfo();
}

/// <summary>
/// Creates a new instance of the TypedTypeBuilder using the template type to
/// automatically deduce type information.
/// </summary>
template <typename T>
TypedTypeBuilder<T>::TypedTypeBuilder(Meta::Library &library, StringParam name)
    : TypedTypeBuilder<T>(library)
{
    SetName(name);
}

template <typename T>
void TypedTypeBuilder<T>::SetDefaultTypeInfo()
{
    //SetName(TypeId<T>::name());
    SetSize(sizeof(T));
    SetHashCode(TypeId<T>::hash_code());
    IsClass(std::is_class<T>::value);
    IsStruct(!std::is_class<T>::value);
    IsUnion(std::is_union<T>::value);

    SetSpecificTypeInfo<T>();
}

// Reference
template <typename T>
template <typename T2>
typename std::enable_if<std::is_reference<T2>::value && !std::is_pointer<T2>::value, void>::type
TypedTypeBuilder<T>::SetSpecificTypeInfo()
{
    SetQualifier(TypeQualifier::Reference);
    SetConcreteType<typename std::remove_reference<T>::type>();
    return;
}

// Pointer
template <typename T>
template <typename T2>
typename std::enable_if<!std::is_reference<T2>::value && std::is_pointer<T2>::value, void>::type
TypedTypeBuilder<T>::SetSpecificTypeInfo()
{
    SetQualifier(TypeQualifier::Pointer);
    SetConcreteType<typename std::remove_pointer<T>::type>();
    return;
}

// Non-reference, non-pointer
template <typename T>
template <typename T2>
typename std::enable_if<!std::is_reference<T2>::value && !std::is_pointer<T2>::value, void>::type
TypedTypeBuilder<T>::SetSpecificTypeInfo()
{
    SetQualifier(TypeQualifier::Concrete);
    SetDestructor<T>();
    return;
}

}