#pragma once
#include "GameObject.h"

DefineTestClass(GameObjectUnitTests)
{
    DefineTestClass(Constructor)
    {
        Constructor();
        DeclareTest(ShouldCreateTransform);
    };
    DefineTestClass(GetComponent)
    {
        GetComponent();
        DeclareTest(ShouldReturnComponentHandleIfComponentExists);
        DeclareTest(ShouldReturnInvalidHandleIfComponentDoesNotExist);
    };
};