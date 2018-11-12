#pragma once
#include "Meta/Interface.h"
#include "IHandleContainer.h"

template <typename ObjectT, typename DataT>
class IHandleContainer;

template <typename ObjectT, typename DataT = unsigned>
class Handle
{
public:
    typedef IHandleContainer<ObjectT, DataT> ContainerT;
    typedef SmartPtr<ContainerT> ContainerPtr;

    ReflectTemplatedType(Handle, ObjectT, DataT);

    Handle();
    Handle(ContainerPtr container, const DataT &data);
    Handle(const Handle<ObjectT, DataT> &other);
    Handle(const Handle<ObjectT, DataT> &&other);

    template <typename DerivedT, typename = std::enable_if<std::is_base_of<ObjectT, DerivedT>::value>>
    Handle(const Handle<DerivedT, DataT> &other);

    bool IsAlive_get();
    PropertyR(bool, IsAlive);
    
    ObjectT *operator*();
    ObjectT *operator->();
    const ObjectT *operator->() const;

    ObjectT *Resolve();
    const ObjectT *Resolve() const;

    bool operator==(const Handle<ObjectT, DataT> &other) const;
    bool operator!=(const Handle<ObjectT, DataT> &other) const;
    operator bool();

    Handle<ObjectT, DataT> &operator=(const Handle<ObjectT, DataT> &rhs);

    template <typename DerivedT>
    Handle<ObjectT, DataT> &operator=(const Handle<DerivedT, DataT> &rhs);

    static Handle<ObjectT, DataT> InvalidHandle;

//private:
    ObjectT *__ptr = nullptr;
    ContainerPtr container;
    DataT data;
};

template <typename DerivedT, typename BaseT, typename DataT>
Handle<BaseT, DataT> UpCastHandle(const Handle<DerivedT, DataT> &handle);

template <typename DerivedT, typename BaseT, typename DataT>
Handle<DerivedT, DataT> DownCastHandle(const Handle<BaseT, DataT> &handle);

#include "Handle.inl"

struct StrictIndex;

#define DefineStrictClassHandleAs(type, name) \
    class type; \
    typedef Handle<type, StrictIndex> name##Handle; \
    typedef const name##Handle &name##HandleParam

#define DefineStrictClassHandle(type) \
    DefineStrictClassHandleAs(type, type)