#pragma once
#include <vector>
#include <functional>

#include "Variant.h"
#include "Type.h"

namespace Meta
{

class GenericFunction
{
public:

    template <typename T, typename ReturnT, typename ...Args>
    std::function<void(void *, byte *)> Wrap(ReturnT(T::*func)(Args...))
    {
        auto f = [=](T& obj, Args... args) -> ReturnT
        {
            return (obj.*func)(std::forward<Args>(args)...);
        };
        return std::function(f);
    }

};

class InvokerFunctions
{

    template <typename T, typename ReturnT, typename Arg0>
    object Invoker(void *context, ReturnT T::*MethodPtr(Arg0), byte *params)
    {
        auto &&thisptr = static_cast<T*>(context);
        auto arg0 = (Arg0) params;
        return thisptr->*MethodPtr(arg0);
    }

    template <typename T, typename ReturnT, typename Arg0, typename Arg1>
    object Invoker(void *context, ReturnT T::*MethodPtr(Arg0, Arg1), byte *params)
    {
        auto &&thisptr = static_cast<T*>(context);
        auto arg0 = *static_cast<Arg0>(params);
        auto arg1 = *static_cast<Arg1>(params + sizeof(Arg0));
        return thisptr->*MethodPtr(arg0, arg1);
    }

};

}