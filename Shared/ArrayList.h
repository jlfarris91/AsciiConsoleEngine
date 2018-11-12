#pragma once

template <typename T>
class ArrayList
{
public:

    ArrayList();
    ArrayList(const ArrayList &other);
    ArrayList(const ArrayList &&other);
    ~ArrayList();

    T &operator[](unsigned index);
    const T &operator[](unsigned index) const;

    ArrayList<T> &operator=(const ArrayList<T> &other);
    ArrayList<T> &operator=(const ArrayList<T> &&other);

    void push_back(const T &item);

    template <int N, typename = typename std::enable_if<std::is_constructible<T>::value, T>::type>
    void push_range(T const(&items)[N]);
    void push_range(const T *items, unsigned num);
    void push_range(const ArrayList<T> &other);

    template <int N>
    void move_range(T const(&items)[N]);
    void move_range(const T *items, unsigned num);
    void move_range(const ArrayList<T> &other);

    void remove(const T &item);

    typedef bool(*ArrayListPred)(const T &a, const T &b);
    void insert(const T &item, ArrayListPred comp = [](const T &a, const T &b) {return a < b; });

    void reserve(unsigned capacity);

    void clear();

    class iterator
    {
    public:
        iterator(ArrayList<T> *container, unsigned index = 0u);
        iterator(const iterator &other);
        iterator &operator++();
        iterator &operator++() const;
        iterator &operator=(const iterator &other);
        T &operator*() const;
        bool operator==(const iterator &other) const;
        bool operator!=(const iterator &other) const;
    private:
        unsigned current;
        ArrayList<T> *container;
        friend class ArrayList<T>;
    };

    iterator begin();
    iterator end();

//private:
	T *data = nullptr;
	unsigned count = 0u;
    unsigned capacity = 0u;

private:
    void grow(unsigned inc);
};

#include "ArrayList.inl"