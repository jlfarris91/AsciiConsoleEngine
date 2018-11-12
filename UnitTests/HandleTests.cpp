#include "HandleTests.h"
#include "IHandleContainer.h"

class MockIntContainer : public IHandleContainer<int, unsigned>
{
public:
    static int ResolveHandleCalled;

    MockIntContainer()
        : SelfContainer(this, false)
    {
        ResolveHandleCalled = 0;
    }

    HandleT GetHandle()
    {
        return HandleT(SelfContainer, 0);
    }

    int *ResolveHandle(const HandleT &data) override
    {
        ++ResolveHandleCalled;
        return new int(456);
    }

    int *ResolveHandle(const HandleT &data) const override
    {
        ++ResolveHandleCalled;
        return new int(456);
    }

    HandleT ResolvePointer(const int *ptr) override
    {
        return GetHandle();
    }

    HandleT ResolvePointer(const int *ptr) const override
    {
        return ResolvePointer(ptr);
    }

    SmartPtr<IHandleContainer<int, unsigned>> SelfContainer;
};

int MockIntContainer::ResolveHandleCalled = 0;

DefineTest(HandleTests::IsAlive, ShouldReturnTrueIfObjectIsAlive)
{
    // Arrange
    auto &&container = new MockIntContainer();

    // Act
    auto &&handle = container->GetHandle();
    bool isAlive = handle.IsAlive;

    // Assert
    Assert(isAlive);
    Assert(container->ResolveHandleCalled != 0);
}

DefineTest(HandleTests::IsAlive, ThrowsIfContainerIsNull)
{
    // Arrange
    auto &&container = new MockIntContainer();

    // Act
    auto &&handle = container->GetHandle();

    // Assert
}