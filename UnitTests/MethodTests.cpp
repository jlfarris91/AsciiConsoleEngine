#include "MethodTests.h"
#include <Meta/Library.h>
#include "Meta/Interface.h"
#include "Meta/Meta.h"

DefineTest(MethodTests::Invoke, InvokeWithVoidReturnTypeNoArgs)
{
    // Arrange
    Meta::Library library;

    struct Foo
    {
        int _asd = 0;
        void DoSomething(int asd)
        {
            _asd = asd;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddMethod("DoSomething", &DoSomething, { "asd" });
        }
    };

    auto type = library.RegisterType<Foo>();
    auto method = *type->Methods.begin();

    Foo foo;

    // Act
    method->Invoke<void>(foo, 123);

    // Assert
    Assert(foo._asd == 123);
}

DefineTest(MethodTests::Invoke, InvokeWithReturnTypeNoArgs)
{
    // Arrange
    Meta::Library library;

    struct Foo
    {
        int DoSomething(int asd)
        {
            return asd * 2;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddMethod("DoSomething", &DoSomething, { "asd" });
        }
    };

    auto type = library.RegisterType<Foo>();
    auto method = *type->Methods.begin();

    Foo foo;

    // Act
    auto result = method->Invoke<int>(foo, 123);

    // Assert
    Assert(result == 123 * 2);
}