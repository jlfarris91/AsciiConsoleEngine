#include "Method.h"
#include "Type.h"

namespace Meta
{

Method::Method()
    : Member(MemberType::Method)
{
}

Getter(Type *, Method::ReturnType)
{
    return returnType;
}

Getter(const ParameterList &, Method::Parameters) const
{
    return params;
}

Getter(string, Method::FullName)
{
    string args;

    auto isconst = isConst ? " const" : string();
    auto isstatic = isStatic ? "static " : string();

    for (auto param = params.begin();;)
    {
        args += String::Format(
            "%s %s",
            param->Type->Name.c_str(),
            param->Name.c_str());

        auto next = param++;
        if (next == params.end())
        {
            break;
        }
        args += ", ";
        param = next;
    }

    return String::Format(
        "%s%s %s::%s(%s)%s",
        isstatic.c_str(),
        returnType->Name.c_str(),
        type->Name.c_str(),
        name.c_str(),
        args.c_str(),
        isconst.c_str());
}

Variant Method::InvokeGeneric(const VariantList &args) const
{
    auto &&returnStorage = (void*)alloca(returnType->Size);
    auto &&argsStorage = (void**)alloca(sizeof(void*) * args.size());

    func(returnStorage, argsStorage);

    return Variant(returnStorage, returnType);
}

Variant Method::InvokeGeneric(const Variant &obj, const VariantList &args) const
{
    auto &&returnStorage = (void*) alloca(returnType->Size);
    auto &&argsStorage = (void**) alloca(sizeof(void*) * args.size());

    func(returnStorage, argsStorage);

    return Variant(returnStorage, returnType);
}

}