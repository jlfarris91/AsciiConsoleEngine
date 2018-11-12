#include "stdafx.h"
#include "UnitTests.h"

int main()
{
    UnitTests &tests = UnitTests::GetInstance();
    tests.Run();
    system("pause");
    return 0;
}

