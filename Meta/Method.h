#pragma once
#include "Member.h"
#include "Parameter.h"
#include <vector>
#include <functional>
#include "Variant.h"

namespace Meta
{

class Type;
class TypeBuilder;

class Method : public Member
{
public:
    typedef std::function<void(void*, void**)> FuncT;

    Method();

    Getter(Meta::Type *, ReturnType);
    PropertyR(Meta::Type *, ReturnType);

    Getter(const ParameterList &, Parameters) const;
    PropertyRW(const ParameterList &, Parameters);

    template <typename ReturnT, typename T, typename ...Args>
    ReturnT Invoke(T &obj, Args... args);

    template <typename ReturnT, typename ...Args>
    ReturnT Invoke(Args... args);

    Variant InvokeGeneric(const VariantList &args) const;
    Variant InvokeGeneric(const Variant &obj, const VariantList &args) const;

    Getter(string, FullName);
    PropertyR(string, FullName);

private:
    Meta::Type *returnType = nullptr;
    ParameterList params;
    FuncT func;

    friend class TypeBuilder;
};

}

#include "Method.inl"
