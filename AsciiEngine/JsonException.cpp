#include "JsonException.h"

JsonException::JsonException(const char *message)
    : message(message)
{
}

JsonException::JsonException(const char *fmt...)
{
    char line[256];
    va_list args;

    va_start(args, fmt);
    vsprintf_s(line, fmt, args);
    va_end(args);

    message = line;
}

Getter(string, JsonException::Message)
{
    return message;
}