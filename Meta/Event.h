#pragma once
#include <functional>
#include <vector>
#include "Generic.h"
#include <list>

namespace Meta
{

template <typename ...Args>
class Event
{
public:
    typedef std::function<void(Args...)> FuncT;

    Event &operator+=(void(*func)(Args...))
    {
        auto f = Generic::Wrapper::Wrap(func);
        Function function;
        function.Func = f;
        return *this;
    }

    template <typename T>
    Event &operator+=(void(T::*func)(Args...), T *obj)
    {
        auto f = Generic::Wrapper::Wrap(func);
        Function function;
        function.Func = f;
        function.Object = obj;
        return *this;
    }

    Event &operator-=(void(*func)(Args...))
    {
        funcs.remove_if([=](Function &f) -> bool
        {
            return f.Func == Generic::Wrapper::Wrap(func);
        });
        return *this;
    }

    template <typename T>
    Event &operator-=(void(T::*func)(Args...))
    {
        funcs.remove_if([=](Function &f) -> bool
        {
            return f.Func == Generic::Wrapper::Wrap(func);
        });
        return *this;
    }

    void operator()(Args &&args)
    {
        for (auto &&func : funcs)
        {
            if (func.Object == nullptr)
            {
                Generic::Invoke(func, std::forward<Args...>(args));
            }
            else
            {
                Generic::Invoke(func, func.Object, std::forward<Args...>(args));
            }
        }
    }

    size_t size() const
    {
        return funcs.size();
    }

    void clear()
    {
        funcs.clear();
    }

private:

    struct Function
    {
        void(*Func)(void*, void **) = nullptr;
        void *Object = nullptr;
    };

    std::list<Function> funcs;

};

}
