#pragma once
#include "Handle.h"

DefineTestClass(HandleTests)
{
public:
    DefineTestClass(IsAlive)
    {
    public:
        DeclareTest(ShouldReturnTrueIfObjectIsAlive);
        DeclareTest(ThrowsIfContainerIsNull);
    };
};