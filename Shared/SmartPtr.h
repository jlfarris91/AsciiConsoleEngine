#pragma once

class RefCounter
{
public:
    unsigned count = 0u;
};

template <typename T>
class SmartPtr
{
public:
    typedef T PointerT;

    SmartPtr(T *ptr, bool owner = false);
    SmartPtr(const SmartPtr<T> &other);
    SmartPtr(const SmartPtr<T> &&other);

    template <typename T2>
    explicit SmartPtr(const SmartPtr<T2> &other);

    ~SmartPtr();

    T &operator*();
    const T &operator*() const;

    T *operator&();
    const T *operator&() const;

    T *operator->();
    const T *operator->() const;

    template <typename T2>
    SmartPtr<T> &operator=(const SmartPtr<T2> &rhs);
    SmartPtr<T> &operator=(const SmartPtr<T> &rhs);

    bool operator==(const T *other) const;
    bool operator!=(const T *other) const;
    bool operator==(const SmartPtr<T> &other) const;
    bool operator!=(const SmartPtr<T> &other) const;

    void Release();
    void Join(const SmartPtr<T> &other);
    bool IsSame(const SmartPtr<T> &other) const;

    Getter(bool, IsAlive) const;
    PropertyR(bool, IsAlive);

    Getter(unsigned, ReferenceCount) const;
    PropertyR(unsigned, ReferenceCount);

    Getter(bool, IsOwner) const;
    PropertyR(bool, IsOwner);

public:
    RefCounter *ref = nullptr;
    T *ptr = nullptr;
    bool isOwner = false;
};

#include "SmartPtr.inl"