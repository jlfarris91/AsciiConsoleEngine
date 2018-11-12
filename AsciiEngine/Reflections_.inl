#pragma once

#define ReflectExternalTypeAsWith(type, name, func) \
    RegisterInitializer<type>((func));

#define ReflectExternalTypeAs(type, name) \
    ReflectExternalTypeAsWith(type, name, (&Meta::ReflectType<type>::InitializeMeta))

#define ReflectExternalType(type) \
    ReflectExternalTypeAs(type, #type)

#define ReflectExternalTemplateTypeAs(type, name, ...) \
    ReflectExternalTypeAs(type<__VA_ARGS__>, name)

#define ReflectExternalTemplateType(type, ...) \
    ReflectExternalTemplateTypeAs(type, #type, __VA_ARGS__)

#include "Reflections_Types.inl"

#undef ReflectExternalTypeAsWith
#define ReflectExternalTypeAsWith(type, name, func) \
    RegisterExternalType<type>(library, name, (func));

#include "Reflections_Types.inl"