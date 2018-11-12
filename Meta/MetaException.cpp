#include "MetaException.h"
#include <stdarg.h>

namespace Meta
{

MetaException::MetaException(StringParam errorcode, const char *fmt, ...)
    : errorcode(errorcode)
{
    char line[256];
    va_list args;

    va_start(args, fmt);
    vsprintf_s(line, fmt, args);
    va_end(args);

    message = line;
}

Getter(StringParam, MetaException::ErrorCode)
{
    return errorcode;
}

Getter(StringParam, MetaException::Message)
{
    return message;
}

}