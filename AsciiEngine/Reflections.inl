#pragma once
#include "Meta/TypeBuilder.h"
#include "Math/Vector3.h"
#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include "Math/Matrix4.h"
#include "Math/Rect.h"
#include <list>
#include <string>
#include <vector>

template <typename ...Args>
void SafeSetTemplatedName(Meta::TypeBuilder &builder, StringParam name)
{
    if (builder.Target->Name.Empty())
    {
        builder.SetTemplatedName<Args...>(name);
    }
    else
    {
        builder.AddTemplatedAlias<Args...>(name);
    }
}

template <>
struct Meta::ReflectType<String>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        typedef String this_type;
        builder.SetName("String");
        builder.AddConstructor<String>();
        builder.AddConstructor<String, String::ValueT &&>({"value"});
        builder.AddConstructor<String, const String::ValueT &>({ "value" });
        builder.AddConstructor<String, const char *>({ "value" });
        builder.AddMethod("Length", &String::Length);
        builder.AddMethod("Empty", &String::Empty);
        return true;
    }
};

template <>
struct Meta::ReflectType<Vector2>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        typedef Vector2 this_type;
        builder.SetName("Vector2");
        ReflectFieldRO(Up);
        ReflectFieldRO(Zero);
        ReflectFieldRO(One);
        ReflectFieldRO(Epsilon);
        builder.AddField("x", &Vector2::x);
        builder.AddField("y", &Vector2::y);
        builder.AddMethod("Assign", &Vector2::operator=, { "other" });
        builder.AddMethod<Vector2, Vector2>("Negate", &Vector2::operator-);
        builder.AddMethod("Add", &Vector2::operator+, { "other" });
        builder.AddMethod<Vector2, Vector2, const Vector2 &>("Subtract", &Vector2::operator-, { "other" });
        builder.AddMethod("Multiply", &Vector2::operator*, { "scalar" });
        builder.AddMethod("Divide", &Vector2::operator/, { "scalar" });
        builder.AddMethod("PlusEquals", &Vector2::operator+=, { "other" });
        builder.AddMethod("MinusEquals", &Vector2::operator-=, { "other" });
        builder.AddMethod("TimesEquals", &Vector2::operator*=, { "scalar" });
        builder.AddMethod("DivideEquals", &Vector2::operator/=, { "scalar" });
        builder.AddMethod("Equals", &Vector2::operator==, { "other" });
        builder.AddMethod("NotEquals", &Vector2::operator!=, { "other" });
        builder.AddMethod("Length", &Vector2::Length);
        builder.AddMethod("LengSq", &Vector2::LengthSq);
        builder.AddMethod("Dot", &Vector2::Dot, { "lhs", "rhs" });
        builder.AddMethod("Normalize", &Vector2::Normalize, { "vector" });
        return true;
    }
};

template <>
struct Meta::ReflectType<Vector3>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        typedef Vector3 this_type;
        builder.SetName("Vector3");
        ReflectFieldRO(Forward);
        ReflectFieldRO(Up);
        ReflectFieldRO(Right);
        ReflectFieldRO(Zero);
        ReflectFieldRO(One);
        ReflectFieldRO(Epsilon);
        ReflectFieldRO(cMin);
        ReflectFieldRO(cMax);
        builder.AddField("x", &Vector3::x);
        builder.AddField("y", &Vector3::y);
        builder.AddField("z", &Vector3::z);
        builder.AddField("r", &Vector3::x);
        builder.AddField("b", &Vector3::y);
        builder.AddField("g", &Vector3::z);
        builder.AddConstructor<Vector3, float, float, float>({ "x", "y", "z" });
        builder.AddConstructor<Vector3, const Vector3 &>({ "other" });
        builder.AddConstructor<Vector3, const Vector2 &>({ "other" });
        builder.AddConstructor<Vector3, const Vector4 &>({ "other" });
        builder.AddMethod("Assign", &Vector3::operator=, { "other" });
        builder.AddMethod<Vector3, Vector3>("Negate", &Vector3::operator-);
        builder.AddMethod("Add", &Vector3::operator+, { "other" });
        builder.AddMethod<Vector3, Vector3, const Vector3 &>("Subtract", &Vector3::operator-, { "other" });
        builder.AddMethod<Vector3, Vector3, const float>("Multiply", &Vector3::operator*, { "scalar" });
        builder.AddMethod<Vector3, Vector3, const Vector3 &>("Multiply", &Vector3::operator*, { "other" });
        builder.AddMethod("Divide", &Vector3::operator/, { "scalar" });
        builder.AddMethod("PlusEquals", &Vector3::operator+=, { "other" });
        builder.AddMethod("MinusEquals", &Vector3::operator-=, { "other" });
        builder.AddMethod("TimesEquals", &Vector3::operator*=, { "scalar" });
        builder.AddMethod("DivideEquals", &Vector3::operator/=, { "scalar" });
        builder.AddMethod("Normalized", &Vector3::Normalized);
        builder.AddMethod("Length", &Vector3::Length);
        builder.AddMethod("LengSq", &Vector3::LengthSq);
        builder.AddMethod("Equals", &Vector3::operator==, { "other" });
        builder.AddMethod("NotEquals", &Vector3::operator!=, { "other" });
        builder.AddMethod("Dot", &Vector3::Dot, { "lhs",{ "rhs" } });
        builder.AddMethod("Cross", &Vector3::Cross, { "lhs", "rhs" });
        builder.AddMethod("Normalize", &Vector3::Normalize, { "vector" });
        builder.AddMethod("Min", &Vector3::Min, { "a", "b" });
        builder.AddMethod("Max", &Vector3::Max, { "a", "b" });
        builder.AddMethod("All", &Vector3::All, { "value" });
        return true;
    }
};

template <>
struct Meta::ReflectType<Vector4>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        typedef Vector4 this_type;
        builder.SetName("Vector4");
        ReflectFieldRO(Up);
        ReflectFieldRO(Zero);
        ReflectFieldRO(One);
        ReflectFieldRO(Epsilon);
        builder.AddField("x", &Vector4::x);
        builder.AddField("y", &Vector4::y);
        builder.AddField("z", &Vector4::z);
        builder.AddField("w", &Vector4::w);
        builder.AddField("r", &Vector4::x);
        builder.AddField("b", &Vector4::y);
        builder.AddField("g", &Vector4::z);
        builder.AddField("a", &Vector4::w);
        builder.AddConstructor<Vector4, float, float, float, float>({ "x", "y", "z", "w" });
        builder.AddConstructor<Vector4, const Vector4 &, float>({ "other", "w" });
        builder.AddConstructor<Vector4, const Vector4 &>({ "other" });
        builder.AddMethod("Assign", &Vector4::operator=, { "other" });
        builder.AddMethod<Vector4, Vector4>("Negate", &Vector4::operator-);
        builder.AddMethod("Add", &Vector4::operator+, { "other" });
        builder.AddMethod<Vector4, Vector4, const Vector4 &>("Subtract", &Vector4::operator-, { "other" });
        builder.AddMethod("Multiply", &Vector4::operator*, { "scalar" });
        builder.AddMethod("Divide", &Vector4::operator/, { "scalar" });
        builder.AddMethod("PlusEquals", &Vector4::operator+=, { "other" });
        builder.AddMethod("MinusEquals", &Vector4::operator-=, { "other" });
        builder.AddMethod("TimesEquals", &Vector4::operator*=, { "scalar" });
        builder.AddMethod("DivideEquals", &Vector4::operator/=, { "scalar" });
        builder.AddMethod("Equals", &Vector4::operator==, { "other" });
        builder.AddMethod("NotEquals", &Vector4::operator!=, { "other" });
        builder.AddMethod("Dot", &Vector4::Dot, { "lhs", "rhs" });
        builder.AddMethod("Cross", &Vector4::Cross, { "lhs", "rhs" });
        builder.AddMethod("Length", &Vector4::Length);
        builder.AddMethod("LengSq", &Vector4::LengthSq);
        builder.AddMethod("Normalize", &Vector4::Normalize, { "vector" });
        return true;
    }
};

template <>
struct Meta::ReflectType<Matrix4>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        typedef Matrix4 this_type;
        builder.SetName("Matrix4");
        ReflectFieldRO(Zero);
        ReflectFieldRO(Identity);
        builder.AddReadOnlyField("Elements", &Matrix4::v);
        return true;
    }
};

template <>
struct Meta::ReflectType<Rect>
{
    static bool InitializeMeta(Meta::TypeBuilder& builder)
    {
        builder.SetName("Rect");
        builder.AddConstructor<Rect, float, float, float, float>({ "left","top","right","bottom" });
        builder.AddConstructor<Rect, const Rect &>({ "other" });
        builder.AddField("Top", &Rect::top);
        builder.AddField("Left", &Rect::left);
        builder.AddField("Bottom", &Rect::bottom);
        builder.AddField("Right", &Rect::right);
        builder.AddReadOnlyProperty("Width", &Rect::width);
        builder.AddReadOnlyProperty("Height", &Rect::height);
        builder.AddMethod("Expand", &Rect::expand, { "size" });
        builder.AddMethod("Overlaps", &Rect::overlaps, { "other" });
        builder.AddMethod<Rect, bool, const Rect &>("Contains", &Rect::contains, { "other" });
        builder.AddMethod<Rect, bool, Vec2Param>("Contains", &Rect::contains, { "point" });
        builder.AddMethod("Assign", &Rect::operator=, { "other" });
        builder.AddMethod("Equals", &Rect::operator==, { "other" });
        builder.AddMethod("NotEquals", &Rect::operator!=, { "other" });
        return true;
    }
};

template <typename U>
struct Meta::ReflectType<std::vector<U, std::allocator<U>>>
{
    static const char *TypeName() { return "vector"; };
    static size_t hash_code()
    {
        return Internal::HashCodeAlgorithm::hash_code(TypeName());
    }
    static bool InitializeMeta(Meta::TypeBuilder &builder)
    {
        SafeSetTemplatedName<U>(builder, TypeName());
        builder.AddTemplateArguments<U>();
        builder.AddTemplate(TypeName());
        builder.AddConstructor<std::vector<U>>();
        builder.AddMethod<std::vector<U>, void, U &&>("push_back", &std::vector<U>::push_back, { "item" });
        builder.AddMethod("clear", &std::vector<U>::clear);
        builder.AddReadOnlyProperty("size", &std::vector<U>::size);
        builder.AddMethod<std::vector<U>, U&, size_t>("get", &std::vector<U>::operator[], { "index" });
        return true;
    }
};

template <typename U>
struct Meta::ReflectType<std::list<U, std::allocator<U>>>
{
    static bool InitializeMeta(Meta::TypeBuilder &builder)
    {
        SafeSetTemplatedName<U>(builder, "List");
        builder.AddTemplateArguments<U>();
        builder.AddConstructor<std::list<U>>();
        builder.AddMethod<std::list<U>, void, U &&>("PushBack", &std::list<U>::push_back, { "item" });
        builder.AddMethod("Clear", &std::list<U>::clear);
        builder.AddReadOnlyProperty("Count", &std::list<U>::size);
        return true;
    }
};

template <typename U, typename V>
struct Meta::ReflectType<Handle<U, V>>
{
    static bool InitializeMeta(Meta::TypeBuilder &builder)
    {
        typedef Handle<U, V> TypeT;
        
        builder.AddTemplateArguments<U, V>();
        builder.AddConstructor<TypeT>();
        builder.AddReadOnlyProperty("IsAlive", &TypeT::IsAlive_get);
        builder.AddMethod<TypeT, U *>("Resolve", &TypeT::Resolve);
        builder.AddMethod("Equals", &TypeT::operator==, { "other" });
        builder.AddField("InvalidHandle", &TypeT::InvalidHandle);
        return true;
    }
};

template <typename T>
void Reflections::RegisterInitializer(const InitializerFuncT &func)
{
    auto hashcode = Meta::TypeId<T>::hash_code();
    initializers[hashcode] = func;
}
