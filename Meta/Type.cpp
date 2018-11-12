#include "Type.h"
#include "Method.h"
#include "MetaException.h"
#include "Field.h"
#include "Property.h"
#include "Variant.h"

namespace Meta
{

Getter(size_t, Type::HashCode) const
{
    return hashCode;
}

Getter(string, Type::Name) const
{
    if (Qualifier != TypeQualifier::Concrete)
    {
        return concreteType->Name + Internal::GetQualifierString(Qualifier);
    }
    return name;
}

Getter(const TypeCollection &, Type::DerivedTypes) const
{
    return derivedTypes;
}

Getter(const TypeCollection &, Type::BaseTypes) const
{
    return baseTypes;
}

Getter(const TypeList &, Type::TemplateArguments) const
{
    return templateTypes;
}

Getter(Type *, Type::ConcreteType) const
{
    return concreteType;
}

Getter(bool, Type::IsStruct) const
{
    return isStruct;
}

Getter(bool, Type::IsClass) const
{
    return isClass;
}

Getter(bool, Type::IsAbstract) const
{
    return isAbstract;
}

Getter(bool, Type::IsUnion) const
{
    return isUnion;
}

Getter(TypeQualifier, Type::Qualifier) const
{
    return qualifier;
}

Getter(const MethodCollection &, Type::Constructors) const
{
    return constructors;
}

Getter(const MethodCollection &, Type::Methods) const
{
    return methods;
}

Getter(const FieldCollection &, Type::Fields) const
{
    return fields;
}

Getter(const PropertyCollection &, Type::Properties) const
{
    return properties;
}

Getter(size_t, Type::Size) const
{
    return size;
}

bool Type::IsSubclassOf(const Type *base) const
{
    for (auto &&type : baseTypes)
    {
        if (type == base)
            return true;
    }
    return false;
}

bool Type::IsBaseOf(const Type *derived) const
{
    for (auto &&type : derivedTypes)
    {
        if (type == derived)
            return true;
    }
    return false;
}

bool Type::IsAssignableFrom(const Type *other) const
{
    return this == other || IsBaseOf(other);
}

Method *Type::GetMethod(StringParam name) const
{
    for (auto method : methods)
    {
        if (method->Name == name)
            return method;
    }
    return nullptr;
}

Method *Type::GetMethod(StringParam name, const TypeCollection &args) const
{
    for (auto method : methods)
    {
        if (method->Name == name && ValidateMethodParams(method, args))
        {
            return method;
        }
    }
    return nullptr;
}

Method *Type::GetMethod(StringParam name, const ParameterList &args) const
{
    for (auto method : methods)
    {
        if (method->Name == name && ValidateMethodParams(method, args))
        {
            return method;
        }
    }
    return nullptr;
}

MethodCollection Type::GetMethods(StringParam name) const
{
    MethodCollection methods;
    for (auto method : methods)
    {
        if (method->Name == name)
        {
            methods.insert(method);
        }
    }
    return methods;
}

Field *Type::GetField(StringParam name) const
{
    for (auto field : fields)
    {
        if (field->Name == name)
        {
            return field;
        }
    }
    return nullptr;
}

Property *Type::GetProperty(StringParam name) const
{
    for (auto prop : properties)
    {
        if (prop->Name == name)
        {
            return prop;
        }
    }
    return nullptr;
}

bool Type::ValidateMethodParams(Method *method, const TypeCollection & paramTypes) const
{
    auto &&methodParams = method->Parameters;
    if (methodParams.size() != paramTypes.size())
    {
        return false;
    }

    auto paramType = paramTypes.begin();
    for (auto methodParam : methodParams)
    {
        if (methodParam.Type != *paramType)
        {
            return false;
        }
        ++paramType;
    }
    return true;
}

bool Type::ValidateMethodParams(Method *method, const ParameterList &paramTypes) const
{
    auto &&methodParams = method->Parameters;
    if (methodParams.size() != paramTypes.size())
    {
        return false;
    }

    auto paramType = paramTypes.begin();
    for (auto methodParam : methodParams)
    {
        if (methodParam.Type != paramType->Type)
        {
            return false;
        }
        ++paramType;
    }
    return true;
}

void Type::Construct(void *ptr, const VariantList &args, IArgumentDeducer *deducer) const
{
    auto &&matching = deducer->DeduceMethod(constructors, args);
    if (matching == nullptr)
    {
        throw MetaException("MethodMismatch", "No constructor was found matching arguments.");
    }
    matching->InvokeGeneric(Variant(ptr, this), args);
}

void Type::Destruct(void *obj) const
{
    if (obj == nullptr)
    {
        throw MetaException("NullObject", "Cannot destruct null object.");
    }
    destructor->Invoke<void>(obj);
}

bool MemberCompare::operator()(const Member* lhs, const Member* rhs) const
{
    return lhs->Name < rhs->Name;
}

bool MethodCompare::operator()(const Method* lhs, const Method* rhs) const
{
    if (lhs->Name != rhs->Name)
    {
        return lhs->Name < rhs->Name;
    }
    auto &&lhsParams = lhs->Parameters;
    auto &&rhsParams = rhs->Parameters;
    if (lhsParams.size() == rhsParams.size())
    {
        auto otherParam = rhsParams.begin();
        for (auto param : lhsParams)
        {
            if (param.Type->Name < otherParam->Type->Name)
            {
                return true;
            }
        }
        return false;
    }
    return lhsParams.size() < rhsParams.size();
}


}