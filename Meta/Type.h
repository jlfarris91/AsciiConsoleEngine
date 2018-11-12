#pragma once
#include <unordered_set>
#include "Parameter.h"
#include "TypeQualifier.h"
#include "ArgumentDeducer.h"

namespace Meta
{

class Field;
class Library;
class Member;
class Method;
class Property;
class Type;
class Variant;
enum class TypeQualifier;

typedef std::vector<string> NameList;

class Type
{
public:

    Getter(size_t, HashCode) const;
    PropertyR(size_t, HashCode);

    Getter(string, Name) const;
    PropertyR(string, Name);

    Getter(const TypeCollection &, BaseTypes) const;
    PropertyR(const TypeCollection &, BaseTypes);

    Getter(const TypeCollection &, DerivedTypes) const;
    PropertyR(const TypeCollection &, DerivedTypes);

    Getter(const TypeList &, TemplateArguments) const;
    PropertyR(const TypeList &, TemplateArguments);

    Getter(Type *, ConcreteType) const;
    PropertyR(Type *, ConcreteType);

    Getter(bool, IsStruct) const;
    PropertyR(bool, IsStruct);

    Getter(bool, IsClass) const;
    PropertyR(bool, IsClass);

    Getter(bool, IsAbstract) const;
    PropertyR(bool, IsAbstract);

    Getter(bool, IsUnion) const;
    PropertyR(bool, IsUnion);

    Getter(size_t, Size) const;
    PropertyR(size_t, Size);

    Getter(const MethodCollection &, Constructors) const;
    PropertyR(const MethodCollection &, Constructors);

    Getter(const MethodCollection &, Methods) const;
    PropertyR(const MethodCollection &, Methods);

    Getter(const FieldCollection &, Fields) const;
    PropertyR(const FieldCollection &, Fields);

    Getter(const PropertyCollection &, Properties) const;
    PropertyR(const PropertyCollection &, Properties);

    Getter(TypeQualifier, Qualifier) const;
    PropertyR(TypeQualifier, Qualifier);

    bool IsSubclassOf(const Type *base) const;
    bool IsBaseOf(const Type *derived) const;
    bool IsAssignableFrom(const Type *other) const;

    Method *GetMethod(StringParam name) const;
    Method *GetMethod(StringParam name, const TypeCollection &args) const;
    Method *GetMethod(StringParam name, const ParameterList &args) const;
    MethodCollection GetMethods(StringParam name) const;

    Field *GetField(StringParam name) const;
    Property *GetProperty(StringParam name) const;

    void Construct(void *ptr, const VariantList &args, IArgumentDeducer *deducer = ArgumentDeducer::Strict) const;

    void Destruct(void *obj) const;

private:

    bool ValidateMethodParams(Method *method, const TypeCollection &params)  const;
    bool ValidateMethodParams(Method *method, const ParameterList &params)  const;

    size_t hashCode = 0u;
    string name;
    size_t size = 0u;
    Type *concreteType = nullptr;

    bool isClass = false;
    bool isStruct = false;
    bool isAbstract = false;
    bool isUnion = false;
    TypeQualifier qualifier = TypeQualifier::Concrete;

    // TODO: add constructor support
    MethodCollection constructors;
    Method *destructor = nullptr;

    TypeCollection derivedTypes;
    TypeCollection baseTypes;

    TypeList templateTypes;
    TypeList implementations;

    NameList aliases;
    MethodCollection methods;
    FieldCollection fields;
    PropertyCollection properties;
    MemberCollection members;

    friend class Library;
    friend class TypeBuilder;
};

}