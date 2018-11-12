#pragma once
//#include "SmartPtr.h"

#ifndef SafeDelete
#define SafeDelete(a) {if (a!=NULL) delete a; a = NULL;}
#endif

template <typename T>
SmartPtr<T>::SmartPtr(T *ptr, bool isOwner)
    : ptr(ptr), ref(new RefCounter()), isOwner(isOwner)
{
    ++ref->count;
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &other)
    : ptr(other.ptr), ref(other.ref), isOwner(other.isOwner)
{
    ++ref->count;
}

template <typename T>
SmartPtr<T>::SmartPtr(const SmartPtr<T> &&other)
    : ptr(other.ptr), ref(other.ref), isOwner(other.isOwner)
{
    ++ref->count;
}

template <typename T>
template <typename T2>
SmartPtr<T>::SmartPtr(const SmartPtr<T2> &other)
{
    this->ptr = (T*)const_cast<T2*>(other.ptr);
    this->ref = other.ref;
    this->isOwner = other.isOwner;
    ++other.ref->count;
}

template <typename T>
SmartPtr<T>::~SmartPtr()
{
    Release();
}

template <typename T>
T &SmartPtr<T>::operator*()
{
    return *ptr;
}

template <typename T>
const T &SmartPtr<T>::operator*() const
{
    return *ptr;
}

template <typename T>
T *SmartPtr<T>::operator&()
{
    return ptr;
}

template <typename T>
const T *SmartPtr<T>::operator&() const
{
    return ptr;
}

template <typename T>
T *SmartPtr<T>::operator->()
{
    return ptr;
}

template <typename T>
const T *SmartPtr<T>::operator->() const
{
    return ptr;
}

template <typename T>
template <typename T2>
SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T2> &rhs)
{
    return this->operator=(SmartPtr<T>(rhs));
}

template <typename T>
SmartPtr<T> &SmartPtr<T>::operator=(const SmartPtr<T> &other)
{
    // they're the same so do nothing
    if (IsSame(other))
    {
        return *this;
    }

    // the pointers are the same but the reference counter isn't
    // we want to join this smart pointer with other so that they
    // share a reference counter
    if (ptr == other.ptr && ref != other.ref)
    {
        Join(other);
        return *this;
    }
    
    // if other points to a different object release the old
    Release();

    // before assigning the new
    ptr = other.ptr;
    ref = other.ref;
    ++ref->count;

    return *this;
}

template <typename T>
bool SmartPtr<T>::operator==(const T *other) const
{
    return ptr == other;
}

template <typename T>
bool SmartPtr<T>::operator!=(const T *other) const
{
    return !operator==(other);
}

template <typename T>
bool SmartPtr<T>::operator==(const SmartPtr<T> &other) const
{
    return (ptr == other.ptr);
}

template <typename T>
bool SmartPtr<T>::operator!=(const SmartPtr<T> &other) const
{
    return !operator==(other);
}

template <typename T>
void SmartPtr<T>::Release()
{
    if (ref == nullptr)
    {
        throw std::exception("Shared reference should not be null.");
    }

    if (--ref->count == 0)
    {
        if (isOwner)
        {
            SafeDelete(ptr);
        }
        SafeDelete(ref);
    }
}

template <typename T>
void SmartPtr<T>::Join(const SmartPtr<T> &other)
{
    if (ptr != other.ptr)
    {
        throw std::exception("Can only join two smart pointers that are pointing at the same address.");
    }

    if (ref != other.ref)
    {
        // remove self from current counter
        if (--ref->count == 0)
        {
            SafeDelete(ref);
        }
        // assign to the new ref counter;
        ref = other.ref;
        ++ref->count;
    }
}

template <typename T>
bool SmartPtr<T>::IsSame(const SmartPtr<T> &other) const
{
    return ptr == other.ptr && ref == other.ref;
}

template <typename T>
Getter(bool, SmartPtr<T>::IsAlive) const
{
    return ptr != nullptr && ref != nullptr;
}

template <typename T>
Getter(unsigned, SmartPtr<T>::ReferenceCount) const
{
    return ref->count;
}

template <typename T>
Getter(bool, SmartPtr<T>::IsOwner) const
{
    return isOwner;
}