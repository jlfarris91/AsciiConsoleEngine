#pragma once

#pragma once

DefineTestClass(LibraryTests)
{
    DefineTestClass(RegisterType)
    {
        DeclareTest(ShouldRegisterTypeWithLibrary);
        DeclareTest(ShouldThrowIfTypeIsAlreadyRegistered);
    };
    DefineTestClass(Destructor)
    {
        DeclareTest(ShouldDeleteTypesOnDestruction);
    };
};