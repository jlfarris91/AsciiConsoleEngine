#include "TypeBuilder.h"

namespace Meta
{

TypeBuilder::TypeBuilder(Meta::Library &library)
    : library(library)
{
    target = new Type;
}

TypeBuilder::TypeBuilder(Meta::Library &library, StringParam name)
    : TypeBuilder(library)
{
    SetName(name);
}

TypeBuilder::~TypeBuilder()
{
    if (IsOwner && target != nullptr)
    {
        delete target;
    }
}

void TypeBuilder::SetName(StringParam name) const
{
    target->name = name;
}

void TypeBuilder::AddAlias(StringParam name) const
{
    library.RegisterTypeAlias(target, name);
    target->aliases.push_back(name);
}

void TypeBuilder::AddAlias(size_t hashcode) const
{
    library.RegisterTypeAlias(target, hashcode);
}
    
void TypeBuilder::SetSize(size_t size)
{
    target->size = size;
}

void TypeBuilder::SetHashCode(size_t hashCode)
{
    target->hashCode = hashCode;
}

void TypeBuilder::IsClass(bool value)
{
    target->isClass = value;
}

void TypeBuilder::IsStruct(bool value)
{
    target->isStruct = value;
}

void TypeBuilder::IsAbstract(bool value)
{
    target->isAbstract = value;
}

void TypeBuilder::IsUnion(bool value)
{
    target->isUnion = value;
}

void TypeBuilder::SetQualifier(TypeQualifier value)
{
    target->qualifier = value;
}

Type* TypeBuilder::AddTemplate(StringParam name)
{
    auto templateType = library.GetTemplateType(name);
    templateType->implementations.push_back(target);
    return templateType;
}

void TypeBuilder::SetConcreteType(Type *type)
{
    if (type->Qualifier != TypeQualifier::Concrete)
    {
        throw MetaException(
            "TypeIsNotConcrete",
            "Type '%s' is not a concrete type.",
            type->Name.c_str());
    }
    target->concreteType = type;
}

Type *TypeBuilder::Build()
{
    if (target->Name == string())
    {
        throw MetaException("TypeMissingName", "Type name is required.");
    }

    if (target->HashCode == 0u)
    {
        throw MetaException("TypeMissingHashCode", "Type hash code is required.");
    }

    if (target->Qualifier != TypeQualifier::Concrete && target->ConcreteType == nullptr)
    {
        throw MetaException(
            "QualifiedTypeMustReferenceConcreteType",
            "Type '%s' is a pointer or reference but does not reference a concrete type.",
            target->Name.c_str());
    }

    auto type = target;
    target = new Type;
    IsOwner = true;
    return type;
}

Getter(Type *, TypeBuilder::Target)
{
    return target;
}

Getter(Library &, TypeBuilder::Library)
{
    return library;
}

}