#pragma once

namespace Meta
{

class Type;
class TypeBuilder;

enum class MemberType
{
    Field,
    Property,
    Method
};

class Member
{
public:
    virtual ~Member()
    {
    }

    Member(MemberType type);

    Getter(string, Name) const;
    PropertyR(string, Name);

    Getter(Meta::MemberType, MemberType);
    PropertyR(Meta::MemberType, MemberType);

    Getter(bool, IsStatic);
    PropertyR(bool, IsStatic);

    Getter(bool, IsConst);
    PropertyR(bool, IsConst);

    Getter(const Type *, Type);
    PropertyR(const Type *, Type);

    virtual bool operator<(const Member *other) const;

protected:

    string name;
    Meta::MemberType memberType;
    Meta::Type *type;

    bool isStatic;
    bool isConst;

    friend class Type;
    friend class TypeBuilder;
};

}
