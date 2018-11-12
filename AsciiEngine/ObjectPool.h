#pragma once
#include "Handle.h"
#include "Shared/ArrayList.h"
#include "IHandleContainer.h"
#include "StrictIndex.h"

template <typename ObjectT>
class PoolableObject;

//---------------------------------------------------------- Object Pool Element
//******************************************************************************
template <typename ObjectT>
class ObjectPoolElement
{
public:
    char Data[sizeof(ObjectT)];
    uint Generation = 0u;
    bool IsActive = false;
};

//------------------------------------------------------------------ Object Pool
//******************************************************************************
template <typename ObjectT>
class ObjectPool : public IHandleContainer<ObjectT, StrictIndex>
{
public:
    ObjectPool(unsigned capacity = 1);
    virtual ~ObjectPool();

    template <typename ...Args>
    typename ObjectPool<ObjectT>::HandleT New(Args ...args);

    virtual void Recycle(const HandleT &ptr);
    virtual void Reserve(unsigned count);
    void Clear();

    Getter(unsigned, Count);
    PropertyR(unsigned, Count);

    Getter(unsigned, NumberOfAliveObjects);
    PropertyR(unsigned, NumberOfAliveObjects);

    class iterator
    {
    public:
        iterator(ObjectPool<ObjectT> *container, uint index = 0u);
        iterator(const iterator &other);
        iterator &operator++();
        iterator &operator++() const;
        iterator &operator=(const iterator &other);
        typename ObjectPool<ObjectT>::HandleT operator*() const;
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
    private:
        uint current;
        ObjectPool<ObjectT> *container;
        friend class ObjectPool<ObjectT>;
    };

    iterator begin();
    iterator end();

    ObjectT *ResolveHandle(const HandleT &index) override;
    ObjectT *ResolveHandle(const HandleT &index) const override;
    typename ObjectPool<ObjectT>::HandleT ResolvePointer(const ObjectT *ptr) override;
    typename ObjectPool<ObjectT>::HandleT ResolvePointer(const ObjectT *ptr) const override;

    SmartPtr<ObjectPool<ObjectT>> Self;
    SmartPtr<IHandleContainer<ObjectT, StrictIndex>> SelfContainer;
protected:

    template <class ...Args>
    unsigned GetNextAvailableObject(Args ...args)
    {
        unsigned start = current;

        do
        {
            auto &element = objects[current];
            if (!element.IsActive)
            {
                ++numberOfAliveObjects;
                element.IsActive = true;
                new (&element.Data) ObjectT(args...);
                return current;
            }
            if (++current == objects.count)
            {
                current = 0u;
            }
        } while (start != current);

        // no more available objects, add a new object
        unsigned newIndex = objects.count;

        // add the new element
        objects.push_back(ObjectPoolElement<ObjectT>());
        auto &element = objects[newIndex];

        element.IsActive = true;
        new (&element.Data) ObjectT(args...);

        // the new object is alive
        ++numberOfAliveObjects;

        // return the index of the new object
        return newIndex;
    }

    ArrayList<ObjectPoolElement<ObjectT>> objects;
    unsigned numberOfAliveObjects = 0u;
    unsigned current = 0u;
};

//-------------------------------------------------------------- Poolable Object
//******************************************************************************
template <typename ObjectT>
class PoolableObject
{
public:
    static ObjectPool<ObjectT> Pool;

    ReflectTemplatedType(PoolableObject, ObjectT)
    {
        builder.SetTemplatedName<ObjectT>("PoolableObject");
        builder.AddTemplate("PoolableObject");
        builder.AddTemplateArguments<ObjectT>();
        builder.AddMethod("Destroy", &Destroy, { "handle" });
    }

    PoolableObject<ObjectT>();
    virtual ~PoolableObject<ObjectT>() = default;

    template <class ...Args>
    static typename ObjectPool<ObjectT>::HandleT New(Args ...args)
    {
        return Pool.New(args...);
    }

    static void Destroy(const typename ObjectPool<ObjectT>::HandleT &handle);

    typename ObjectPool<ObjectT>::HandleT Self;
};

#include "ObjectPool.inl"