#pragma once
#include <vector>

namespace Meta
{

class Type;

class Parameter
{
public:
    Parameter(StringParam name, Type *type, bool isConst = false, bool isOptional = false);

    Getter(StringParam, Name) const;
    PropertyR(StringParam, Name);

    Getter(Meta::Type *, Type) const;
    PropertyR(Meta::Type *, Type);

    Getter(bool, IsConst) const;
    PropertyR(bool, IsConst);

    Getter(bool, IsOptional) const;
    PropertyR(bool, IsOptional);

private:

    string name;
    Meta::Type *type;
    bool isConst = false;
    bool isOptional = false;
};

typedef std::vector<Parameter> ParameterList;

}