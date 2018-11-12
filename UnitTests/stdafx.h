#pragma once
#include "../Shared/Include.h"
#include "../AsciiEngine/Include.h"
#include "UnitTests.h"

#ifdef _DEBUG
#define AssertM(assert, msg) \
    if (!(assert)) throw std::exception(msg)
#else
#define AssertM(assert, msg)
#endif

#define Assert(assert) AssertM(assert, "");
#define AssertContainsM(list, contains, msg) \
    {\
        bool _contains = false; \
        for (auto &&_item : list) \
        { \
            if (contains(_item)) \
            { \
                _contains = true; \
                break; \
            } \
        } \
        AssertM(_contains, msg); \
    }
#define AssertContains(list, contains) \
    AssertContainsM(list, contains, "")