#include "Member.h"

namespace Meta
{

Member::Member(Meta::MemberType type)
    : memberType(type)
{
}


Getter(string, Member::Name) const
{
    return name;
}

Getter(Meta::MemberType, Member::MemberType)
{
    return memberType;
}

Getter(bool, Member::IsStatic)
{
    return isStatic;
}

Getter(bool, Member::IsConst)
{
    return isConst;
}

Getter(const Type *, Member::Type)
{
    return type;
}

bool Member::operator<(const Member *other) const
{
    return name < other->name;
}

}