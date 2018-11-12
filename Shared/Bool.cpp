#include "Bool.h"

bool atob(const char *value)
{
    return value[0] == 't' || value[0] == 'T' || value[0] == '1';
}