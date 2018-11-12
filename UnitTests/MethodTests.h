#pragma once

DefineTestClass(MethodTests)
{
    DefineTestClass(Invoke)
    {
        DeclareTest(InvokeWithVoidReturnTypeNoArgs);
        DeclareTest(InvokeWithReturnTypeNoArgs);
    };
};
