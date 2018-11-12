#pragma once
#include <vector>

class Guid
{
public:
    typedef __int64 GuidT;
    
    Getter(GuidT, Value);
    PropertyR(GuidT, Value);

    bool operator==(const Guid &other);
    bool operator!=(const Guid &other);
    Guid &operator=(const Guid &other);
    operator GuidT();

    static Guid NewGuid();
private:
    Guid(GuidT value);
    GuidT value;
};