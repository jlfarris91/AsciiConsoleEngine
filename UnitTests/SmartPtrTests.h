#pragma once
#include "SmartPtr.h"

DefineTestClass(SmartPtrTests)
{
    DefineTestClass(Constructor)
    {
        DeclareTest(ThrowsIfPointerIsNull);
        DeclareTest(ShouldAssignCorrectlyWithConversionCtor);
        DeclareTest(ShouldAssignCorrectlyWithCopyCtor);
    };
    DefineTestClass(Equality)
    {
        DeclareTest(ShouldReturnTrueIfPointersAreEqual);
    };
    DefineTestClass(Assignment)
    {
        DeclareTest(ShouldReleaseBeforeAssigningToDifferentPointer);
        DeclareTest(ShouldJoinIfPointersAreTheSameButRefCountersAreDifferent);
    };
    DefineTestClass(Release)
    {
        DeclareTest(ShouldDeleteMemoryWhenReferenceCountReachesZero);
    };
    DefineTestClass(Join)
    {
        DeclareTest(ShouldBeSameAfterJoin);
    };
    DefineTestClass(IsSame)
    {
        
    };
};