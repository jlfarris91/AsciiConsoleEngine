#pragma once
#include <functional>

template <typename T>
class Lazy
{
public:
    typedef std::function<T(void)> FuncT;

    explicit Lazy(const FuncT &func)
        : func(func)
    {
    }

    T Value() const
    {
        return func();
    }

    operator T() const
    {
        return Value();
    }

private:
    FuncT func;
};