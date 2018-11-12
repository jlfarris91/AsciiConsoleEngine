#pragma once

#include <unordered_set>
#include <set>

namespace Meta
{

class Type;
class Method;
class Field;
class Property;
class Member;
class Variant;

struct MemberCompare
{
    bool operator()(const Member *lhs, const Member *rhs) const;
};

struct MethodCompare
{
    bool operator()(const Method *lhs, const Method *rhs) const;
};

typedef std::unordered_set<Type *> TypeCollection;
typedef std::vector<Type *> TypeList;
typedef std::set<Method*, MethodCompare> MethodCollection;
typedef std::set<Field *, MemberCompare> FieldCollection;
typedef std::set<Property *, MemberCompare> PropertyCollection;
typedef std::set<Member *, MemberCompare> MemberCollection;
typedef std::vector<Variant> VariantList;

}
