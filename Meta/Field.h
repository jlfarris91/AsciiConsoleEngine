#pragma once
#include "Member.h"
#include "Generic.h"

namespace Meta
{
    
class Type;
class Method;

class Field : public Member
{
public:
    Field();

    Getter(Meta::Type *, Type);
    PropertyR(Meta::Type *, Type);

    template <typename FieldT>
    FieldT Get();

    template <typename FieldT>
    FieldT Get(void *obj);

    template <typename FieldT>
    FieldT Get(unsigned index);

    template <typename FieldT>
    FieldT Get(void *obj, unsigned index);

    template <typename FieldT>
    void Set(void *obj, FieldT value);

    template <typename FieldT>
    void Set(FieldT value);

    template <typename FieldT>
    void Set(void *obj, unsigned index, FieldT value);

    template <typename FieldT>
    void Set(unsigned index, FieldT value);

    Getter(bool, IsArray) const;
    PropertyR(bool, IsArray);

    Getter(unsigned, Count) const;
    PropertyR(unsigned, Count);

private:
    Meta::Type *type = nullptr;
    GenericFuncT getter = nullptr;
    GenericFuncT setter = nullptr;

    bool isArray = false;
    unsigned count = 0u;

    friend class TypeBuilder;
};

}

#include "Field.inl"