#pragma once
#include <exception>
#include <varargs.h>

class UnitySceneLoaderException
{
public:
    UnitySceneLoaderException(const char *fmt...);

    Getter(string, Message);
    PropertyR(string, Message);

protected:

    string message;
};

