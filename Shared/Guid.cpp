#include "Guid.h"
#include <chrono>

Guid::GuidT base = 0u;

Guid::GuidT GetCurrentMillisecsSinceEpoch()
{
    return std::chrono::system_clock::now().time_since_epoch() /
        std::chrono::milliseconds(1);
}

Guid::Guid(Guid::GuidT value)
    : value(value)
{
}

bool Guid::operator==(const Guid &other)
{
    return value == other.value;
}

bool Guid::operator!=(const Guid &other)
{
    return value != other.value;
}

Guid &Guid::operator=(const Guid &other)
{
    value = other.value;
    return *this;
}

Guid::operator GuidT()
{
    return value;
}

Guid Guid::NewGuid()
{
    if (base == 0u)
    {
        base = GetCurrentMillisecsSinceEpoch();
    }
    return Guid(base);
}