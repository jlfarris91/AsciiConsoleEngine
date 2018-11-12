#pragma once
#include "ArrayList.h"

template <typename T>
ArrayList<T>::ArrayList()
{
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &other)
{
    this->operator=(other);
}

template <typename T>
ArrayList<T>::ArrayList(const ArrayList<T> &&other)
{
    this->operator=(other);
}

template <typename T>
ArrayList<T>::~ArrayList()
{
    clear();
    free(data);
    data = nullptr;
}

template <typename T>
T &ArrayList<T>::operator[](unsigned index)
{
    return data[index];
}

template <typename T>
const T &ArrayList<T>::operator[](unsigned index) const
{
    return data[index];
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &other)
{
    clear();
    if (capacity < other.capacity)
    {
        grow(other.capacity - capacity);
    }
    push_range(other);
    return *this;
}

template <typename T>
ArrayList<T> &ArrayList<T>::operator=(const ArrayList<T> &&other)
{
    clear();
    if (capacity < other.capacity)
    {
        grow(other.capacity - capacity);
    }
    push_range(other);
    return *this;
}

template <typename T>
void ArrayList<T>::push_back(const T &item)
{
    if (count == capacity)
    {
        grow(1);
    }

    new (data + count) T(item);
    count++;
}

template <typename T>
template <int N, typename>
void ArrayList<T>::push_range(T const(&items)[N])
{
    if (count + N >= capacity)
    {
        grow(N);
    }
    for (unsigned i = 0; i < N; ++i)
    {
        push_back(items[i]);
    }
}

template <typename T>
void ArrayList<T>::push_range(const T *items, unsigned num)
{
    if (count + num > capacity)
    {
        grow(num);
    }
    for (unsigned i = 0; i < num; ++i)
    {
        push_back(items[i]);
    }
}

template <typename T>
void ArrayList<T>::push_range(const ArrayList<T> &other)
{
    push_range(other.data, other.count);
}

template <typename T>
template <int N>
void ArrayList<T>::move_range(T const(&items)[N])
{
    if (count + N >= capacity)
    {
        grow(N);
    }
    memcpy(data + count, items, sizeof(T) * N);
    count += N;
}

template <typename T>
void ArrayList<T>::move_range(const T *items, unsigned num)
{
    if (count + num >= capacity)
    {
        grow(num);
    }
    memcpy(data + count, items, sizeof(T) * num);
    count += num;
}

template <typename T>
void ArrayList<T>::move_range(const ArrayList<T> &other)
{
    move_range(other.data, other.count);
}

template <typename T>
void ArrayList<T>::remove(const T &item)
{
    int index = -1;
    for (unsigned i = 0; i < count; ++i)
    {
        if (item == data[i])
            index = i;
    }

    if (index == -1)
        return;

    T *ptr = data + index;

    // delete the element
    data[index].~T();

    // copy the end of the array up by one
    if (count != 1)
    {
        memcpy(ptr, ptr + 1, sizeof(T) * (count - (index + 1)));
    }

    // one less item now
    --count;
}

template <typename T>
void ArrayList<T>::insert(const T &item, ArrayListPred comp)
{
    if (count == 0)
    {
        push_back(item);
        return;
    }

    if (comp == nullptr)
    {
        return;
    }

    unsigned index = 0;
    for (; index < count; ++index)
    {
        if (comp(item, data[index]))
            break;
    }

    if (index == count)
    {
        push_back(item);
        return;
    }

    if (count == capacity)
    {
        grow(1);
    }

    T *ptr = data + index;

    // copy the end of the array up by one
    if (count != 1)
    {
        memcpy(ptr + 1, ptr, sizeof(T) * (count - index));
    }

    data[index] = item;
    ++count;
}

template <typename T>
void ArrayList<T>::reserve(unsigned capacity)
{
    if (capacity < this->capacity)
    {
        return;
    }
    grow((capacity - this->capacity) + 1);
}

template <typename T>
void ArrayList<T>::clear()
{
    // destruct all objects
    for (unsigned i = 0; i < count; ++i)
    {
        data[i].~T();
    }
    // reset values
    count = 0;
}

template <typename T>
void ArrayList<T>::grow(unsigned inc)
{
    // incease the capacity
    while (capacity < count + inc)
    {
        capacity = (capacity == 0) ? 2 : (int) (capacity * 1.5f);
    }

    // create a new data array of the new capacity
    data = (T*)realloc(data, sizeof(T) * capacity);
}

template <typename T>
ArrayList<T>::iterator::iterator(ArrayList<T> *container, unsigned index)
    : current(index), container(container)
{
}

template <typename T>
ArrayList<T>::iterator::iterator(const iterator &other)
    : current(other.current), container(other.container)
{
}

template <typename T>
typename ArrayList<T>::iterator &ArrayList<T>::iterator::operator++()
{
    ++current;
    return *this;
}

template <typename T>
typename ArrayList<T>::iterator &ArrayList<T>::iterator::operator++() const
{
    ++current;
    return *this;
}

template <typename T>
typename ArrayList<T>::iterator &ArrayList<T>::iterator::operator=(const iterator &other)
{
    container = other.container;
    current = other.current;
}

template <typename T>
bool ArrayList<T>::iterator::operator==(const iterator &other) const
{
    return current == other.current && container == other.container;
}

template <typename T>
bool ArrayList<T>::iterator::operator!=(const iterator &other) const
{
    return !(operator==(other));
}

template <typename T>
T &ArrayList<T>::iterator::operator*() const
{
    return container->data[current];
}

template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::begin()
{
    return iterator(this, 0);
}

template <typename T>
typename ArrayList<T>::iterator ArrayList<T>::end()
{
    return iterator(this, count);
}