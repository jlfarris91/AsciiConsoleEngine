
template <typename ObjectT>
ObjectPool<ObjectT>::ObjectPool(unsigned capacity)
    : Self(this, false), SelfContainer(this, false)
{
    objects.reserve(capacity);
    for (unsigned i = 0u; i < capacity; ++i)
    {
        ObjectPoolElement<ObjectT> element;
        objects.push_back(element);
    }
}

template <typename ObjectT>
ObjectPool<ObjectT>::~ObjectPool()
{
}

template <typename ObjectT>
template <typename ...Args>
typename ObjectPool<ObjectT>::HandleT ObjectPool<ObjectT>::New(Args ...args)
{
    auto &&index = GetNextAvailableObject(args...);

    StrictIndex data;
    data.index = index;
    data.index2 = objects[index].Generation;

    return typename ObjectPool<ObjectT>::HandleT(SelfContainer, data);
}

template <typename ObjectT>
void ObjectPool<ObjectT>::Recycle(const HandleT &handle)
{
    if (auto && object = ResolveHandle(handle))
    {
        // call object's destructor
        object->~ObjectT();
        // increase the generation
        auto &element = objects[handle.data.index];
        element.IsActive = false;
        ++element.Generation;
        // one less object alive in the pool
        --numberOfAliveObjects;
    }
    else
    {
        throw std::exception("Trying to recycle an invalid object.");
    }
}

template <typename ObjectT>
void ObjectPool<ObjectT>::Reserve(unsigned count)
{

}

template <typename ObjectT>
void ObjectPool<ObjectT>::Clear()
{
    objects.clear();
    numberOfAliveObjects = 0;
    // there should be at least one
    ObjectPoolElement<ObjectT> element;
    objects.push_back(element);
}

template <typename ObjectT>
Getter(unsigned, ObjectPool<ObjectT>::Count)
{
    return objects.count;
}

template <typename ObjectT>
Getter(unsigned, ObjectPool<ObjectT>::NumberOfAliveObjects)
{
    return numberOfAliveObjects;
}

template <typename ObjectT>
ObjectT *ObjectPool<ObjectT>::ResolveHandle(const typename ObjectPool<ObjectT>::HandleT &handle)
{
    if (handle.container != SelfContainer)
    {
        return nullptr;
    }
    return (ObjectT*) objects[handle.data.index].Data;
}

template <typename ObjectT>
ObjectT *ObjectPool<ObjectT>::ResolveHandle(const typename ObjectPool<ObjectT>::HandleT &handle) const
{
    if (handle.container != SelfContainer)
    {
        return nullptr;
    }
    return (ObjectT*) objects[handle.data.index].Data;
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::HandleT ObjectPool<ObjectT>::ResolvePointer(const ObjectT *ptr)
{
    for (unsigned i = 0; i < objects.count; ++i)
    {
        ObjectT *object = (ObjectT*) objects[i].Data;
        if (object == ptr)
        {
            StrictIndex data;
            data.index = i;
            data.index2 = objects[i].Generation;
            return HandleT(SelfContainer, data);
        }
    }
    return HandleT::InvalidHandle;
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::HandleT ObjectPool<ObjectT>::ResolvePointer(const ObjectT *ptr) const
{
    return this->ResolvePointer(ptr);
}

template <typename ObjectT>
ObjectPool<ObjectT>::iterator::iterator(ObjectPool<ObjectT> *container, uint index)
    : current(index), container(container)
{
}

template <typename ObjectT>
ObjectPool<ObjectT>::iterator::iterator(const iterator &other)
    : current(other.current), container(other.container)
{
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::iterator &ObjectPool<ObjectT>::iterator::operator++()
{
    while (++current < container->objects.count && !container->objects[current].IsActive);
    return *this;
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::iterator &ObjectPool<ObjectT>::iterator::operator++() const
{
    while (++current < container->objects.count && !container->objects[current].IsActive);
    return *this;
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::iterator &ObjectPool<ObjectT>::iterator::operator=(const iterator &other)
{
    container = other.container;
    current = other.current;
}

template <typename ObjectT>
bool ObjectPool<ObjectT>::iterator::operator==(const iterator &other) const
{
    return current == other.current && container == other.container;
}

template <typename ObjectT>
bool ObjectPool<ObjectT>::iterator::operator!=(const iterator &other) const
{
    return !operator==(other);
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::HandleT ObjectPool<ObjectT>::iterator::operator*() const
{
    StrictIndex data;
    data.index = current;
    data.index2 = container->objects[current].Generation;
    return typename ObjectPool<ObjectT>::HandleT(container->SelfContainer, data);
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::iterator ObjectPool<ObjectT>::begin()
{
    return iterator(this, 0);
}

template <typename ObjectT>
typename ObjectPool<ObjectT>::iterator ObjectPool<ObjectT>::end()
{
    return iterator(this, objects.count);
}

template <typename ObjectT>
ObjectPool<ObjectT> PoolableObject<ObjectT>::Pool;

template <typename ObjectT>
PoolableObject<ObjectT>::PoolableObject()
    : Self(Pool.ResolvePointer((ObjectT*)this))
{
}

template <typename ObjectT>
void PoolableObject<ObjectT>::Destroy(const typename ObjectPool<ObjectT>::HandleT &handle)
{
    Pool.Recycle(handle);
}
