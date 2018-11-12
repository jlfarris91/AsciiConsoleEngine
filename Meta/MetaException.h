#pragma once

namespace Meta
{

class MetaException
{
public:
    MetaException(StringParam errorcode, const char *fmt, ...);

    Getter(StringParam, ErrorCode);
    PropertyR(StringParam, ErrorCode);

    Getter(StringParam, Message);
    PropertyR(StringParam, Message);

protected:
    string errorcode;
    string message;
};

}