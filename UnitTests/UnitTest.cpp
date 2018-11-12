#include "UnitTest.h"
#include "UnitTests.h"

UnitTestBase::UnitTestBase(char *className, char *methodName)
    : className(className), methodName(methodName)
{
    UnitTests::GetInstance().RegisterUnitTest(this);
}