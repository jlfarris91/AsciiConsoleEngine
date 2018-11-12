#pragma once
#include <exception>
#include <varargs.h>

class JsonException
{
public:
    JsonException(const char *message = nullptr);
    JsonException(const char *fmt...);

    Getter(string, Message);
    PropertyR(string, Message);

protected:

    string message;
};
