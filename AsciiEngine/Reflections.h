#pragma once
#include "Meta/Meta.h"

typedef bool(*InitializerFuncT)(Meta::TypeBuilder &);

struct Reflections
{
    static void RegisterTypes(Meta::Library & library);

    template <typename T>
    static void RegisterInitializer(const InitializerFuncT &func);

    static bool InitializeType(const Meta::InitializationParams &params);

private:

    static std::unordered_map<size_t, InitializerFuncT> initializers;
};

#include "Reflections.inl"