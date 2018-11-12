#pragma once

class Asset : public Object
{
public:
    ReflectType(Asset);

    Getter(StringParam, Name);
    Setter(StringParam, Name);
    PropertyRW(string, Name);
private:
    string name;
};

DefineStrictClassHandle(Asset);