#pragma once

DefineTestClass(ExternalRegistrationTests)
{
    DeclareTest(ShouldDoNothingIfRegistrationFunctionIsNull);
    DeclareTest(ShouldRegisterTypeIfRegistrationFunctionIsNotNull);
};
