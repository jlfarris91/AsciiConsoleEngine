#pragma once

class UnitTestBase
{
public:
    UnitTestBase(char *className, char *methodName);
    char *className = nullptr;
    char *methodName = nullptr;
    virtual void Run() = 0;
};

template <typename Class, void(Class::*MemberPtr)(void)>
class UnitTest : public UnitTestBase
{
public:
    UnitTest(char *className, char *methodName)
        : UnitTestBase(className, methodName)
    {
    }

    void Run() override
    {
        if (MemberPtr == nullptr)
            return;
        Class instance;
        (instance.*MemberPtr)();
    }
};
