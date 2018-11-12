#pragma once
#include <vector>
#include <functional>
#include <iostream>
#include <exception>
#include <assert.h>
#include "UnitTest.h"

class UnitTests
{
public:

    static UnitTests &GetInstance()
    {
        static UnitTests tests;
        return tests;
    }

    void Run();
    void RegisterUnitTest(UnitTestBase *test);
    std::vector<UnitTestBase *> tests;
};

template <typename T>
struct TestClass
{
protected:
    typedef T this_type;
};

#define DefineTestClass(T) \
    struct T : public TestClass<T>

#define DeclareTest(TestName) \
    void TestName(void); \
    static UnitTest<this_type, &this_type::TestName> TestName##Test

#define DefineTest(Class, TestName) \
    UnitTest<Class, &Class::TestName> Class::TestName##Test(#Class, #TestName); \
    void Class::TestName(void)