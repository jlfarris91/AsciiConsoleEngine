#include "SmartPtrTests.h"
#include "ArrayList.h"

class Foo
{
public:
    std::function<void()> dtorCallback;
    Foo(std::function<void()> dc)
        : dtorCallback(dc)
    {
    }
    virtual ~Foo()
    {
        dtorCallback();
    }
};

DefineTest(SmartPtrTests::Constructor, ThrowsIfPointerIsNull)
{
    // Arrange
    auto &&act = []() { (void)SmartPtr<int>(nullptr); };

    // Act + Assert
    try
    {
        act();
        // failure, ctor should have thrown an exception
        AssertM(false, "Constructor should have thrown exception when pointer is null.");
    }
    catch (std::exception e)
    {
        // success
    }
}

DefineTest(SmartPtrTests::Constructor, ShouldAssignCorrectlyWithConversionCtor)
{
    // Arrange
    int *integer = new int(10);
    
    // Act
    SmartPtr<int> ptr(integer);

    // Assert
    Assert(ptr == integer);
}

DefineTest(SmartPtrTests::Constructor, ShouldAssignCorrectlyWithCopyCtor)
{
    // Arrange
    int *integer = new int(10);
    SmartPtr<int> ptr1(integer);

    Assert(ptr1.ReferenceCount == 1);

    // Act
    SmartPtr<int> ptr2(ptr1);

    // Assert
    Assert(ptr1.ReferenceCount == 2);
    Assert(ptr2.ReferenceCount == 2);
    Assert(ptr2 == integer);
    Assert(ptr1.IsSame(ptr2));
}

DefineTest(SmartPtrTests::Equality, ShouldReturnTrueIfPointersAreEqual)
{
    // Arrange
    int integer = 10;

    // Act
    SmartPtr<int> ptr1(&integer, false);
    SmartPtr<int> ptr2(&integer, false);

    // Assert
    Assert(ptr1 == ptr2);
}

DefineTest(SmartPtrTests::Assignment, ShouldReleaseBeforeAssigningToDifferentPointer)
{
    // Arrange
    bool foo1DtorCalled = false;
    Foo *foo1 = new Foo([&]()
    {
        foo1DtorCalled = true;
    });

    bool foo2DtorCalled = false;
    Foo *foo2 = new Foo([&]()
    {
        foo2DtorCalled = true;
    });

    SmartPtr<Foo> ptr1(foo1, true);
    SmartPtr<Foo> ptr2(foo2, true);

    // Act
    ptr1 = ptr2;

    // Assert
    Assert(foo1DtorCalled);
    Assert(!foo2DtorCalled);
    Assert(ptr1 == ptr2);
}

DefineTest(SmartPtrTests::Assignment, ShouldJoinIfPointersAreTheSameButRefCountersAreDifferent)
{
    // Arrange
    bool fooDtorCalled = false;
    Foo *foo = new Foo([&]()
    {
        fooDtorCalled = true;
    });

    SmartPtr<Foo> ptr1(foo);
    SmartPtr<Foo> ptr2(foo);

    // Assert that they start out with different ref counters
    Assert(ptr1 == ptr2);
    Assert(!ptr1.IsSame(ptr2));
    Assert(ptr1.ReferenceCount == 1);
    Assert(ptr2.ReferenceCount == 1);

    // Act
    ptr1 = ptr2;

    // Assert
    Assert(!fooDtorCalled);
    Assert(ptr1.IsSame(ptr2));
}

DefineTest(SmartPtrTests::Release, ShouldDeleteMemoryWhenReferenceCountReachesZero)
{
    // Arrange
    int dtorCalled = 0;

    Foo *foo = new Foo([&]()
    {
        ++dtorCalled;
    });

    // Act
    {
        SmartPtr<Foo> ptr1(foo, true);
        SmartPtr<Foo> ptr2 = ptr1;
        SmartPtr<Foo> ptr3 = ptr1;
    }

    // Assert
    Assert(dtorCalled == 1);
}

DefineTest(SmartPtrTests::Join, ShouldBeSameAfterJoin)
{
    // Arrange
    bool fooDtorCalled = false;
    Foo *foo = new Foo([&]()
    {
        fooDtorCalled = true;
    });

    SmartPtr<Foo> ptr1(foo);
    SmartPtr<Foo> ptr2(foo);

    // Assert that they start out with different ref counters
    Assert(ptr1 == ptr2);
    Assert(!ptr1.IsSame(ptr2));
    Assert(ptr1.ReferenceCount == 1);
    Assert(ptr2.ReferenceCount == 1);

    // Act
    ptr1.Join(ptr2);

    // Assert
    Assert(!fooDtorCalled);
    Assert(ptr1.IsSame(ptr2));
    Assert(ptr1 == ptr2);
    Assert(ptr1.ReferenceCount == 2);
    Assert(ptr2.ReferenceCount == 2);
}