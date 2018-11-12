#pragma once
#include <Meta/TypeId.h>
//#include "Handle.h"
//#include "IHandleContainer.h"

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT> Handle<ObjectT, DataT>::InvalidHandle;

template <typename ObjectT, typename DataT>
void Handle<ObjectT, DataT>::InitializeMeta(Meta::TypeBuilder &builder)
{
    typedef Handle<ObjectT, DataT> TypeT;
    auto &&objectType = builder.Library.GetType<ObjectT>();
    builder.SetName(objectType->Name + "Handle");
    builder.AddTemplate("Handle");
    builder.AddTemplateArguments<ObjectT, DataT>();
    builder.AddConstructor<TypeT>();
    builder.AddReadOnlyProperty("IsAlive", &TypeT::IsAlive_get);
    builder.AddMethod<TypeT, ObjectT *>("Resolve", &TypeT::Resolve);
    builder.AddMethod("Equals", &TypeT::operator==, { "other" });
    builder.AddField("InvalidHandle", &TypeT::InvalidHandle);
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT>::Handle()
    : container(nullptr)
{
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT>::Handle(ContainerPtr container, const DataT &data)
    : container(container), data(data)
{
    Resolve();
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT>::Handle(const Handle<ObjectT, DataT> &other)
    : container(other.container), data(other.data)
{
    Resolve();
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT>::Handle(const Handle<ObjectT, DataT> &&other)
    : container(other.container), data(other.data)
{
    Resolve();
}

template <typename ObjectT, typename DataT>
template <typename DerivedT, typename>
Handle<ObjectT, DataT>::Handle(const Handle<DerivedT, DataT> &other)
    : container(other.container), data(other.data)
{
    Resolve();
}

template <typename ObjectT, typename DataT>
ObjectT *Handle<ObjectT, DataT>::operator*()
{
    return Resolve();
}

template <typename ObjectT, typename DataT>
ObjectT *Handle<ObjectT, DataT>::operator->()
{
    return Resolve();
}

template <typename ObjectT, typename DataT>
const ObjectT *Handle<ObjectT, DataT>::operator->() const
{
    return Resolve();
}

template <typename ObjectT, typename DataT>
ObjectT *Handle<ObjectT, DataT>::Resolve()
{
    __ptr = (container != nullptr && container.IsAlive) ? container->ResolveHandle(*this) : nullptr;
    return __ptr;
}

template <typename ObjectT, typename DataT>
const ObjectT *Handle<ObjectT, DataT>::Resolve() const
{
    return (container != nullptr && container.IsAlive) ? container->ResolveHandle(*this) : nullptr;
}

template <typename ObjectT, typename DataT>
bool Handle<ObjectT, DataT>::IsAlive_get()
{
    return Resolve() != nullptr;
}

template <typename ObjectT, typename DataT>
bool Handle<ObjectT, DataT>::operator==(const Handle<ObjectT, DataT> &other) const
{
    return container == other.container && data == other.data;
}

template <typename ObjectT, typename DataT>
bool Handle<ObjectT, DataT>::operator!=(const Handle<ObjectT, DataT> &other) const
{
    return !operator==(other);
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT>::operator bool()
{
    return IsAlive;
}

template <typename ObjectT, typename DataT>
Handle<ObjectT, DataT> &Handle<ObjectT, DataT>::operator=(const Handle<ObjectT, DataT> &rhs)
{
    this->container = rhs.container;
    this->data = rhs.data;
    return *this;
}

template <typename ObjectT, typename DataT>
template <typename DerivedT>
Handle<ObjectT, DataT> &Handle<ObjectT, DataT>::operator=(const Handle<DerivedT, DataT> &rhs)
{
    this->container = rhs.container;
    this->data = rhs.data;
    return *this;
}

template <typename DerivedT, typename BaseT, typename DataT>
Handle<BaseT, DataT> UpCastHandle(const Handle<DerivedT, DataT> &handle)
{
    static_assert(std::is_base_of<BaseT, DerivedT>::value, "Type does not derive from base type.");
    Handle<BaseT, DataT> baseHandle;
    baseHandle.container = handle.container;
    baseHandle.data = handle.data;
    return baseHandle;
}

template <typename DerivedT, typename BaseT, typename DataT>
Handle<DerivedT, DataT> DownCastHandle(const Handle<BaseT, DataT> &handle)
{
    static_assert(std::is_base_of<BaseT, DerivedT>::value, "Type does not derive from base type.");
    Handle<DerivedT, DataT> derivedHandle;
    derivedHandle.container = handle.container;
    derivedHandle.data = handle.data;
    return derivedHandle;
}