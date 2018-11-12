#include "UnitTests.h"

void UnitTests::Run()
{
    unsigned passed = 0u, failed = 0u;
    std::cout << tests.size() << " tests discovered. " << std::endl;
    for (auto &&unitTest : tests)
    {
        std::cout << unitTest->className << "::" << unitTest->methodName;
        try
        {
            unitTest->Run();
            std::cout << " - passed" << std::endl;
            ++passed;
        }
        catch (std::exception e)
        {
            std::cout << " - failed" << std::endl;
            std::cout << "------------------------------" << std::endl;
            std::cout << e.what() << std::endl;
            std::cout << "------------------------------" << std::endl;
            ++failed;
        }
    }
    std::cout << "Passed: " << passed << std::endl;
    std::cout << "Failed: " << failed << std::endl;
}

void UnitTests::RegisterUnitTest(UnitTestBase *test)
{
    tests.push_back(test);
}
