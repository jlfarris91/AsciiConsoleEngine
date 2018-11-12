#include "LibraryTests.h"
#include "Meta/Library.h"
#include "Meta/Interface.h"
using namespace Meta;

DefineTest(LibraryTests::RegisterType, ShouldRegisterTypeWithLibrary)
{
    // Arrange
    auto library = new Library;

    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    auto type = library->RegisterType<Foo>();
    Assert(type != nullptr);
    Assert(type->Name == "Foo");

    // Act
    delete library;

    // Assert

}

DefineTest(LibraryTests::RegisterType, ShouldThrowIfTypeIsAlreadyRegistered)
{
    // Arrange
    Library library;
    Assert(library.GetType<int>() != nullptr);

    // Act
    try
    {
        library.RegisterType<int>();
    }
    catch (MetaException ex)
    {
        Assert(ex.ErrorCode == "TypeAlreadyRegistered");
        return;
    }

    // Assert
    Assert(false);
}

DefineTest(LibraryTests::Destructor, ShouldDeleteTypesOnDestruction)
{
    // Arrange
    auto library = new Library;
    
    struct Foo
    {
        ReflectType(Foo)
        {
            builder.SetName("Foo");
        }
    };

    auto type = library->RegisterType<Foo>();
    Assert(type != nullptr);
    Assert(type->Name == "Foo");

    // Act
    delete library;

    // Assert

}