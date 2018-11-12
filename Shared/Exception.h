#pragma once

class Exception
{
public:
    Exception(const char *fmt...);

    Getter(string, Message);
    PropertyR(string, Message);

protected:

    string message;
};

