#include "FieldTests.h"
#include "Meta/Library.h"
#include "Meta/Field.h"
#include "Meta/Interface.h"
using namespace Meta;

struct Foo
{
    static int sBar;
    int bar = 123;
    int robar = 123;
    ReflectType(Foo)
    {
        builder.SetName("Foo");
        builder.AddField("Bar", &Foo::bar);
        builder.AddReadOnlyField("roBar", &Foo::bar);
        builder.AddField("sBar", &sBar);
    }
};

int Foo::sBar = 123;

DefineTest(FieldTests::Get, ShouldProperlyGetValue)
{
    // Arrange
    Library library;
    auto type = library.RegisterType<Foo>();
    auto field = type->GetField("Bar");

    Foo foo;

    // Act
    auto result = field->Get<int>(&foo);

    // Assert
    Assert(result == 123);
}

DefineTest(FieldTests::Get, ShouldProperlyGetStaticValue)
{
    // Arrange
    Library library;
    auto type = library.RegisterType<Foo>();
    auto field = type->GetField("sBar");

    // Act
    auto result = field->Get<int>();

    // Assert
    Assert(result == 123);
}

DefineTest(FieldTests::Set, ShouldProperlySetValue)
{
    // Arrange
    Library library;
    auto type = library.RegisterType<Foo>();
    auto field = type->GetField("Bar");

    Foo foo;

    // Act
    field->Set<int>(&foo, 456);

    // Assert
    Assert(foo.bar == 456);
}

DefineTest(FieldTests::Set, ShouldThrowIfReadOnly)
{
    // Arrange
    Library library;
    auto type = library.RegisterType<Foo>();
    auto field = type->GetField("roBar");

    Foo foo;

    // Act + Assert
    try
    {
        field->Set<int>(&foo, 456);
    }
    catch (MetaException ex)
    {
        Assert(ex.ErrorCode == "ReadOnlyField");
        return;
    }

    // Assert
    Assert(false);
}

DefineTest(FieldTests::Set, ShouldProperlySetStaticValue)
{
    // Arrange
    Library library;
    auto type = library.RegisterType<Foo>();
    auto field = type->GetField("sBar");

    Foo foo;

    // Act
    field->Set<int>(456);

    // Assert
    Assert(foo.sBar == 456);
}
