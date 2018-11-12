#include "Exception.h"
#include <stdarg.h>

Exception::Exception(const char *fmt...)
{
    char line[256];
    va_list args;

    va_start(args, fmt);
    vsprintf_s(line, fmt, args);
    va_end(args);

    message = line;
}

Getter(string, Exception::Message)
{
    return message;
}