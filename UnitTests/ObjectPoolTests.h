#pragma once

DefineTestClass(ObjectPoolTests)
{
    DefineTestClass(New)
    {
        DeclareTest(ShouldReturnValidHandle);
        DeclareTest(ShouldReserveAdditionalObjectsWhenAtCapacity);
    };
    DefineTestClass(Recycle)
    {
        DeclareTest(ShouldMakeObjectReusable);
    };
    DefineTestClass(Count)
    {
        DeclareTest(ShouldReturnNumberOfActiveObjects);
    };
    DefineTestClass(Reserve)
    {
        DeclareTest(ShouldReserveObjects);
    };
};