#pragma once
#include "Member.h"
#include "Generic.h"

namespace Meta
{

class Type;
class Method;

class Property : public Member
{
public:
    Property();

    Getter(Meta::Type *, Type);
    PropertyR(Meta::Type *, Type);

    template <typename PropertyT>
    PropertyT Get();

    template <typename PropertyT>
    PropertyT Get(void *obj);

    template <typename PropertyT>
    void Set(void *obj, PropertyT value);

    template <typename PropertyT>
    void Set(PropertyT value);

private:
    Meta::Type *type;
    Method *getter;
    Method *setter;

    friend class TypeBuilder;
};

}

#include "Property.inl"