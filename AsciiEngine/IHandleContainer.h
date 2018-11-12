#pragma once

template <typename ObjectT, typename DataT>
class Handle;

template <typename ObjectT, typename DataT>
class IHandleContainer
{
public:
    virtual ~IHandleContainer() = default;

    typedef DataT HandleDataT;
    typedef Handle<ObjectT, HandleDataT> HandleT;
    virtual ObjectT *ResolveHandle(const HandleT &data) = 0;
    virtual ObjectT *ResolveHandle(const HandleT &data) const = 0;
    virtual HandleT ResolvePointer(const ObjectT *ptr) = 0;
    virtual HandleT ResolvePointer(const ObjectT *ptr) const = 0;
};