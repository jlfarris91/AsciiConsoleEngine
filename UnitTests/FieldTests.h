#pragma once

DefineTestClass(FieldTests)
{
    DefineTestClass(Get)
    {
        DeclareTest(ShouldProperlyGetValue);
        DeclareTest(ShouldProperlyGetStaticValue);
    };
    DefineTestClass(Set)
    {
        DeclareTest(ShouldProperlySetValue);
        DeclareTest(ShouldThrowIfReadOnly);
        DeclareTest(ShouldProperlySetStaticValue);
    };
};

