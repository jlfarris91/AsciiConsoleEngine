#include "Reflections.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Meta/Library.h"
#include "Math/Rect.h"
#include "Component.h"
#include "GameObject.h"
#include "Handle.h"

std::unordered_map<size_t, InitializerFuncT> Reflections::initializers;

template <typename T>
void RegisterExternalType(Meta::Library &library, StringParam name, const InitializerFuncT func)
{
    auto &&builder = Meta::TypedTypeBuilder<T>(library, name);
    auto &&type = builder.Target;
    library.RegisterType(type);
    func(builder);
    type = builder.Build();
    library.RegisterType(type);
}

bool String_InitializeMeta(Meta::TypeBuilder& builder)
{
    builder.SetName("String");
    builder.AddConstructor<std::string>();
    builder.AddConstructor<std::string, const char *>();
    builder.AddConstructor<std::string, const std::string &>();
    builder.AddReadOnlyProperty("Length", &std::string::length);
    builder.AddReadOnlyProperty("Size", &std::string::size);
    builder.AddMethod("CStr", &std::string::c_str);
    builder.AddMethod("PushBack", &std::string::push_back);
    //builder.AddMethod<std::string, char &, size_t>("Get", &std::string::operator[], { "index" });
    return true;
}

void Reflections::RegisterTypes(Meta::Library &library)
{
    Meta::gLibrary->RegistrationFallback = &InitializeType;
    #include "Reflections_.inl"
}

bool Reflections::InitializeType(const Meta::InitializationParams &params)
{
    if (params.hashcode != 0u)
    {
        auto &&iter = initializers.find(params.hashcode);
        if (iter != initializers.end())
        {
            return iter->second(params.builder);
        }
    }

    return false;
}