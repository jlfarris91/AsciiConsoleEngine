#pragma once

DefineTestClass(TypeBuilderTests)
{
    DefineTestClass(SetName)
    {
        DeclareTest(ProperlySetsName);
    };
    DefineTestClass(AddBase)
    {
        DeclareTest(ProperlyAddsBaseReferences);
        DeclareTest(ProperlyAddsBaseFields);
        DeclareTest(ProperlyAddsBaseProperties);
        DeclareTest(ProperlyAddsBaseMethods);
        DeclareTest(ProperlyAddsOverriddenBaseFields);
        DeclareTest(ProperlyAddsOverriddenBaseProperties);
        DeclareTest(ProperlyAddsOverriddenBaseMethods);
        DeclareTest(ThrowsIfTryingToAddSelfAsBase);
    };
    DefineTestClass(Build)
    {
        DeclareTest(ShouldThrowExceptionIfNameIsEmpty);
        DeclareTest(ShouldThrowExceptionIfHashCodeIsNotSet);
    };
    DefineTestClass(AddMethod)
    {
        DeclareTest(ProperlyAddsNonConstMethod);
        DeclareTest(ProperlyAddsConstMethod);
        DeclareTest(ProperlyAddsStaticMethod);
    };
    DeclareTest(SelfTypeReference);
};