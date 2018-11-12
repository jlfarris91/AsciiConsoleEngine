#include "TypeBuilderTests.h"
#include "Meta/Library.h"
#include "Meta/Interface.h"
#include <Meta/MetaException.h>
#include <Meta/TypeId.h>

using namespace Meta;

DefineTest(TypeBuilderTests::SetName, ProperlySetsName)
{
    // Arrange
    Library library;
    auto builder = TypeBuilder(library);

    // Act
    builder.SetName("Foo");
    builder.SetHashCode(1);
    auto type = builder.Build();

    // Assert
    Assert(type->Name == "Foo");
}

DefineTest(TypeBuilderTests::AddBase, ProperlyAddsBaseReferences)
{
    // Arrange
    Library library;

    struct Bar
    {
        ReflectType(Bar)
        {
            builder.SetName("Bar");
        }
    };

    struct Foo : Bar
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddBase<Bar>();
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();
    auto baseTypes = type->BaseTypes;

    // Assert
    Assert(baseTypes.size() == 1);
    auto base = *baseTypes.begin();
    Assert(base->Name == "Bar");
    Assert(base->HashCode == TypeId<Bar>::hash_code());
}

DefineTest(TypeBuilderTests::AddBase, ProperlyAddsBaseFields)
{
    // Arrange
    Library library;

    struct Bar
    {
        int asd = 123;
        ReflectType(Bar)
        {
            builder.SetName("Bar");
            builder.AddField("Asd", &Bar::asd);
        }
    };

    struct Foo : Bar
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
    AssertContains(type->Fields, [=](Field *field) -> bool
    {
        return field->Name == "Asd";
    });
}

DefineTest(TypeBuilderTests::AddBase, ProperlyAddsBaseProperties)
{
    // Arrange
    Library library;

    struct Bar
    {
        Getter(int, Asd) { return asd; }
        Setter(int, Asd) { asd = value; }
        PropertyR(int, Asd);

        ReflectType(Bar)
        {
            builder.SetName("Bar");
            builder.AddProperty("Asd", &Asd_get, &Asd_set);
        }

    private:
        int asd = 123;
    };

    struct Foo : Bar
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
    AssertContains(type->Properties, [=](Property *prop) -> bool
    {
        return prop->Name == "Asd";
    });
}

DefineTest(TypeBuilderTests::AddBase, ProperlyAddsBaseMethods)
{
    // Arrange
    Library library;

    struct Bar
    {
        int Asd() const
        {
            return asd;
        }
        ReflectType(Bar)
        {
            builder.SetName("Bar");
            builder.AddMethod("Asd", &Asd);
        }

    private:
        int asd = 123;
    };

    struct Foo : Bar
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
    AssertContains(type->Methods, [=](Method *method) -> bool
    {
        return method->Name == "Asd";
    });
}

//DefineTest(TypeBuilderTests::AddBase, ProperlyAddsOverriddenBaseFields)
//{
//    // Arrange
//    Library library;
//
//    struct Bar
//    {
//        int asd = 123;
//        ReflectType(Bar)
//        {
//            builder.SetName("Bar");
//            builder.AddField("Asd", &Bar::asd);
//        }
//    };
//
//    struct Foo : Bar
//    {
//        ReflectType(Foo)
//        {
//            builder.SetName("Foo");
//            builder.AddBase<Bar>();
//        }
//    };
//
//    // Act
//    auto type = library.RegisterType<Foo>();
//
//    // Assert
//    AssertContains(type->Fields, [=](Field *field) -> bool
//    {
//        return field->Name == "Asd";
//    });
//}
//
//DefineTest(TypeBuilderTests::AddBase, ProperlyAddsOverriddenBaseProperties)
//{
//    // Arrange
//    Library library;
//
//    struct Bar
//    {
//        Getter(int, Asd) { return asd; }
//        Setter(int, Asd) { asd = value; }
//        PropertyR(int, Asd);
//
//        ReflectType(Bar)
//        {
//            builder.SetName("Bar");
//            builder.AddProperty("Asd", &Asd_get, &Asd_set);
//        }
//
//    private:
//        int asd = 123;
//    };
//
//    struct Foo : Bar
//    {
//        ReflectType(Foo)
//        {
//            builder.SetName("Foo");
//            builder.AddBase<Bar>();
//        }
//    };
//
//    // Act
//    auto type = library.RegisterType<Foo>();
//
//    // Assert
//    AssertContains(type->Properties, [=](Property *prop) -> bool
//    {
//        return prop->Name == "Asd";
//    });
//}

DefineTest(TypeBuilderTests::AddBase, ProperlyAddsOverriddenBaseMethods)
{
    // Arrange
    Library library;

    struct Bar
    {
        virtual int Asd() const
        {
            return asd;
        }
        ReflectType(Bar)
        {
            builder.SetName("Bar");
            builder.AddMethod("Asd", &Asd);
        }

    private:
        int asd = 123;
    };

    struct Foo : Bar
    {
        virtual int Asd() const override
        {
            return 456;
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddBase<Bar>();
            builder.AddMethod("Asd", &Asd);
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();

    // Assert
    Assert(type->Methods.size() == 1);
    AssertContains(type->Methods, [=](Method *method) -> bool
    {
        return method->Name == "Asd" && method->Type == type;
    });
}

DefineTest(TypeBuilderTests::AddBase, ThrowsIfTryingToAddSelfAsBase)
{
    // Arrange
    Library library;

    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddBase<Foo>();
        }
    };

    // Act
    try
    {
        library.RegisterType<Foo>();
    }
    catch (MetaException ex)
    {
        Assert(ex.ErrorCode == "SelfRegistration");
        return;
    }

    // Assert
    Assert(false);
}

DefineTest(TypeBuilderTests::Build, ShouldThrowExceptionIfNameIsEmpty)
{
    // Arrange
    Library library;
    auto builder = TypeBuilder(library);

    // Act + Assert
    try
    {
        builder.SetHashCode(999u);
        builder.Build();
    }
    catch (MetaException ex)
    {
        // Should throw an exception because name is not set
        Assert(ex.ErrorCode == "TypeMissingName");
        return;
    }

    Assert(false);
}

DefineTest(TypeBuilderTests::Build, ShouldThrowExceptionIfHashCodeIsNotSet)
{
    // Arrange
    Library library;
    auto builder = TypeBuilder(library);

    // Act + Assert
    try
    {
        builder.SetName("Foo");
        builder.Build();
    }
    catch (MetaException ex)
    {
        // Should throw an exception because hash code is not set
        Assert(ex.ErrorCode == "TypeMissingHashCode");
        return;
    }

    Assert(false);
}

DefineTest(TypeBuilderTests, SelfTypeReference)
{
    // Arrange
    Library library;
    auto builder = TypeBuilder(library);

    struct Foo
    {
        void Asd(Foo) const
        {
        }
        void Asd(Foo &) const
        {
        }
        ReflectType(Foo)
        {
            builder.SetName("Foo");
            builder.AddMethod<Foo, void, Foo>("Asd", &Foo::Asd);
            builder.AddMethod<Foo, void, Foo &>("Asd", &Foo::Asd);
        }
    };

    // Act
    auto type = library.RegisterType<Foo>();

    // Assert

}