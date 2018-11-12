#pragma once
#include "IObject.h"
#include "Handle.h"

class Object : public IObject
{
public:
    Object() : id(Guid::NewGuid()) {}
    Getter(Guid, Id) { return id; }
    virtual string ToString() { return string(""); }

private:
    Guid id;
};

DefineStrictClassHandle(Object);