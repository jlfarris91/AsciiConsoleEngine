#include "ExternalRegistrationTests.h"

struct Foo
{
    void asd(int val) const { }
};

bool InitializeFoo(Meta::TypeBuilder &builder)
{
    builder.SetName("Foo");
    builder.AddMethod("asd", &Foo::asd, { "val" });
    return true;
}

bool InitializeType(const Meta::InitializationParams &params)
{
    if (params.hashcode == Meta::TypeId<Foo>::hash_code())
    {
        return InitializeFoo(params.builder);
    }
    return false;
}

DefineTest(ExternalRegistrationTests, ShouldDoNothingIfRegistrationFunctionIsNull)
{
    // Arrange
    Meta::Library library;
    library.RegistrationFallback = nullptr;

    // Act
    auto type = library.GetType<Foo>();

    // Assert
    Assert(type->Methods.size() == 0);
}

DefineTest(ExternalRegistrationTests, ShouldRegisterTypeIfRegistrationFunctionIsNotNull)
{
    // Arrange
    Meta::Library library;
    library.RegistrationFallback = InitializeType;

    // Act
    auto type = library.GetType<Foo>();

    // Assert
    Assert(type->Name == "Foo");
}