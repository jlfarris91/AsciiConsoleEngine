#pragma once
#include "Handle.h"
#include "StrictIndex.h"
#include "Object.h"
#include "EnumDefinitions.h"
#include "Meta/Interface.h"

#define DefineTypeName(type) \
    static const char *GetTypeName() { return #type; }

#define ReflectProperty(prop) \
    builder.AddProperty(#prop, &this_type::##prop##_get, &this_type::##prop##_set)

#define ReflectPropertyRO(prop) \
    builder.AddReadOnlyProperty(#prop, &prop##_get)

#define ReflectMethod(method, ...) \
    builder.AddMethod(#method, &this_type::##method, { __VA_ARGS__ })

#define ReflectField(field) \
    builder.AddField(#field, &this_type::##field)

#define ReflectFieldRO(field) \
    builder.AddReadOnlyField(#field, &this_type::##field)

typedef std::initializer_list<const char *> ArgNames;

#include "Reflections.h"