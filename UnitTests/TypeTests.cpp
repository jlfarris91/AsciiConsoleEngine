#include "TypeTests.h"
#include <Meta/Library.h>
#include <Meta/Interface.h>
#include <Meta/MetaException.h>

DefineTest(TypeTests::Destruct, ProperlyDestructsObject)
{
    // Arrange
    Meta::Library library;

    static auto destructed = false;

    struct Foo
    {
        ~Foo()
        {
            destructed = true;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    auto type = library.RegisterType<Foo>();
    Foo foo;

    // Act
    type->Destruct(&foo);

    // Assert
    Assert(destructed);
}

DefineTest(TypeTests::Destruct, ThrowsIfObjectIsNull)
{
    // Arrange
    Meta::Library library;

    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    auto type = library.RegisterType<Foo>();
    
    // Act + Assert
    try
    {
        type->Destruct(nullptr);
    }
    catch (Meta::MetaException ex)
    {
        Assert(ex.ErrorCode == "NullObject");
        return;
    }

    // Assert
    Assert(false);
}

DefineTest(TypeTests::Pointer, ASD)
{
    // Assert
    Meta::Library library;

    struct Foo
    {
        int PtrTest(int *ptr) const
        {
            return *ptr * 2;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddMethod("PtrTest", &PtrTest, { "ptr" });
        }
    };

    auto type = library.RegisterType<Foo>();
    auto method = *type->Methods.begin();

    Foo foo;
    auto i = 123;

    // Act
    auto result = method->Invoke<int>(foo, &i);

    // Assert
    Assert(result == 123 * 2);
}

DefineTest(TypeTests::Method, Overloads)
{
    // Assert
    Meta::Library library;

    struct Foo
    {
        int PtrTest(int *ptr) const
        {
            return *ptr * 2;
        }
        int PtrTest(float *ptr) const
        {
            return (int)*ptr * 3;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddMethod<Foo, int, int*>("PtrTest", &PtrTest, { "ptr" });
            builder.AddMethod<Foo, int, float*>("PtrTest", &PtrTest, { "ptr" });
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();

    // Assert
    Assert(type->Methods.size() == 2);
    auto &&iter = type->Methods.begin();
    auto &&method1 = *iter;
    auto &&method2 = *(++iter);
    Assert(method1->Name == "PtrTest");
    Assert(method1->Parameters[0].Type == library.GetType<float *>());
    Assert(method2->Name == "PtrTest");
    Assert(method2->Parameters[0].Type == library.GetType<int *>());
}

DefineTest(TypeTests::IsSubclassOf, ReturnsTrueIfIsSubclass)
{
    // Arrange
    Meta::Library library;

    struct Bar
    {
        ReflectType(Bar)
        {
            builder.SetName("Bar");
        }
    };

    struct Foo : public Bar
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddBase<Bar>();
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();

    // Assert
    auto base = library.GetType<Bar>();
    Assert(type->IsSubclassOf(base));
}

DefineTest(TypeTests::IsSubclassOf, ReturnsFalseIfIsNotSubclass)
{
    // Arrange
    Meta::Library library;

    struct Bar
    {
        ReflectType(Bar)
        {
            builder.SetName("Bar");
        }
    };

    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    // Act
    auto barType = library.RegisterType<Bar>();
    auto fooType = library.RegisterType<Foo>();

    // Assert
    Assert(!fooType->IsSubclassOf(barType));
}

DefineTest(TypeTests::IsBaseOf, ReturnsTrueIfIsBaseOf)
{
    // Arrange
    Meta::Library library;

    struct Bar
    {
        ReflectType(Bar)
        {
            builder.SetName("Bar");
        }
    };

    struct Foo : public Bar
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddBase<Bar>();
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();

    // Assert
    auto base = library.GetType<Bar>();
    Assert(base->IsBaseOf(type));
}

DefineTest(TypeTests::IsBaseOf, ReturnsFalseIfIsNotBaseOf)
{
    // Arrange
    Meta::Library library;

    struct Bar
    {
        ReflectType(Bar)
        {
            builder.SetName("Bar");
        }
    };

    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    // Act
    auto barType = library.RegisterType<Bar>();
    auto fooType = library.RegisterType<Foo>();

    // Assert
    Assert(!barType->IsBaseOf(fooType));
}