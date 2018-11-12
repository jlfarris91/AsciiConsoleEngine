#pragma once
#include "UnitTests.h"
#include "ArrayList.h"

DefineTestClass(ArrayListTests)
{
    DefineTestClass(Push_Back)
    {
        DeclareTest(ShouldAppendItem);
        DeclareTest(ShouldCallCopyCtor);
    };
    DefineTestClass(Push_Range)
    {
        DeclareTest(ShouldAppendItems);
        DeclareTest(ShouldAppendOtherListsItems);
    };
    DefineTestClass(Insert)
    {
        DeclareTest(ShouldInsertItem);
        DeclareTest(ShouldInsertToFront);
        DeclareTest(ShouldInsertToBack);
        DeclareTest(ShouldInsertIntoEmptyList);
    };
    DefineTestClass(Remove)
    {
        DeclareTest(ShouldRemoveItem);
        DeclareTest(ShouldRemoveFirstItem);
        DeclareTest(ShouldRemoveLastItem);
        DeclareTest(ShouldCallItemsDestructor);
    };
    DefineTestClass(Reserve)
    {
        DeclareTest(ShouldIncreaseSizeIfArrayCapacityIsLess);
        DeclareTest(ShouldDoNothingIfArrayCapacityIsGreater);
        DeclareTest(ShouldDoNothingIfArrayCapacityIsEqual);
    };
    DefineTestClass(Range)
    {
        DeclareTest(ShouldIterateThroughAllElements);
    };
};