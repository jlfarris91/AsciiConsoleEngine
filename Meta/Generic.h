#pragma once
#include <functional>

typedef std::function<void(void*, void**)> GenericFuncT;

namespace Meta
{

namespace Internal
{

template <size_t idx>
static void UnrollArgs(void **)
{
}

template <size_t idx, typename T, typename ...Args>
static void UnrollArgs(void **argStorage, T&& arg, Args&&... args)
{
    argStorage[idx] = static_cast<void*>(&arg);
    UnrollArgs<idx + 1, Args...>(argStorage, std::forward<Args>(args)...);
}

template <typename ...Args>
static void UnrollArgs(void **argStorage, Args&&... args)
{
    UnrollArgs<0, Args...>(argStorage, std::forward<Args>(args)...);
}

template <int idx, typename T>
inline T&& ForwardCastArg(void **args)
{
    //auto arg = (T*) args[idx];
    //return std::forward<T>(arg);
    return std::forward<T>(*(reinterpret_cast<typename std::remove_reference<T>::type*>(args[idx])));
}

template<int ...>
struct Sequence
{

};

template<int N, int ...S>
struct Generator : Generator<N - 1, N - 1, S...>
{

};

template<int ...S>
struct Generator<0, S...>
{
    typedef Sequence<S...> type;
};

template <typename T = void, typename ReturnT = void, typename ...Args>
struct FunctionWrapper
{
    // Void return type
    template <typename ReturnT2, int... S>
    static typename std::enable_if<std::is_void<ReturnT2>::value, void>::type
    Call(const std::function<ReturnT(Args...)> &func, void *, void **args, Sequence<S...>)
    {
        func(ForwardCastArg<S, Args>(args)...);
        return;
    }

    // Return type
    template <typename ReturnT2, int... S>
    static typename std::enable_if<!std::is_void<ReturnT2>::value && !std::is_reference<ReturnT2>::value, void>::type
    Call(const std::function<ReturnT(Args...)> &func, void *ret, void **args, Sequence<S...>)
    {
        new (ret) ReturnT(func(ForwardCastArg<S, Args>(args)...));
        return;
    }

    template <typename ReturnT2, int... S>
    static typename std::enable_if<!std::is_void<ReturnT2>::value && std::is_reference<ReturnT2>::value, void>::type
    Call(const std::function<ReturnT(Args...)> &func, void *ret, void **args, Sequence<S...>)
    {
        typedef typename std::remove_reference<ReturnT2>::type Ret;
        *(Ret **) ret = &func(ForwardCastArg<S, Args>(args)...);
        return;
    }

    static std::function<void(void*, void**)> Generate(std::function<ReturnT(Args...)> && f)
    {
        return [f](void* ret, void** args)
        {
            Call<ReturnT>(f, ret, args, Generator<sizeof...(Args)>::type());
        };
    }
};

};

struct Generic
{
    template <typename ReturnT, typename ...Args>
    static
    typename std::enable_if<!std::is_void<ReturnT>::value, ReturnT>::type
    Invoke(const GenericFuncT &func, Args&&... args)
    {
        // Allocate space on the stack for the return value
        auto returnStorage = alloca(sizeof(ReturnT));
        // Allocate space for the arguments
        auto argCount = sizeof...(Args);
        auto argStorage = (void**) alloca(argCount * sizeof(void*));
        // Unroll the variadic template arguments into the storage
        Internal::UnrollArgs(argStorage, std::forward<Args>(args)...);
        // Invoke using generic storage
        func(returnStorage, argStorage);
        // Cast and return
        return std::move(*reinterpret_cast<ReturnT*>(returnStorage));
    }

    template <typename ReturnT, typename ...Args>
    static
    typename std::enable_if<std::is_void<ReturnT>::value, ReturnT>::type 
    Invoke(const GenericFuncT &func, Args&&... args)
    {
        // Allocate space for the arguments
        auto argCount = sizeof...(Args);
        auto argStorage = (void**) alloca(argCount * sizeof(void*));
        // Unroll the variadic template arguments into the storage
        Internal::UnrollArgs(argStorage, std::forward<Args>(args)...);
        // Invoke using generic storage
        func(nullptr, argStorage);
        return;
    }

    struct Wrapper
    {

#pragma region Wrap

        // Regular functions
        template <typename ReturnT>
        static GenericFuncT Wrap(std::function<ReturnT()> func)
        {
            auto f = [=]() -> ReturnT
            {
                return func();
            };
            return Internal::FunctionWrapper<void, ReturnT>::Generate(f);
        }

        template <typename ReturnT, typename ...Args>
        static GenericFuncT Wrap(ReturnT(*func)(Args...))
        {
            auto f = [=](Args... args) -> ReturnT
            {
                return func(std::forward<Args>(args)...);
            };
            return Internal::FunctionWrapper<void, ReturnT, Args...>::Generate(f);
        }

        template <typename ReturnT, typename ...Args>
        static GenericFuncT Wrap(std::function<ReturnT(Args...)> func)
        {
            auto f = [=](Args... args) -> ReturnT
            {
                return func(std::forward<Args>(args)...);
            };
            return Internal::FunctionWrapper<void, ReturnT, Args...>::Generate(f);
        }

        // Member functions
        template <typename T, typename ReturnT, typename ...Args>
        static GenericFuncT Wrap(ReturnT(T::*func)(Args...))
        {
            auto f = [=](T &obj, Args... args) -> ReturnT
            {
                return (obj.*func)(std::forward<Args>(args)...);
            };
            // Wrap the member function by adding an argument for the object
            //                   v
            return Wrap<ReturnT, T&, Args...>(f);
        }

        template <typename T, typename ReturnT, typename ...Args>
        static GenericFuncT Wrap(ReturnT(T::*func)(Args...) const)
        {
            auto f = [=](T &obj, Args... args) -> ReturnT
            {
                return (obj.*func)(std::forward<Args>(args)...);
            };
            // Wrap the member function by adding an argument for the object
            //                   v
            return Wrap<ReturnT, T&, Args...>(f);
        }

#pragma endregion

#pragma region Getter/Setter

        template <typename T, typename FieldT>
        static typename std::enable_if<!std::is_array<FieldT>::value, GenericFuncT>::type
        WrapGetter(FieldT T::*fieldPtr)
        {
            typedef typename std::remove_all_extents<FieldT>::type ReturnT;
            auto f = [=](T *obj) -> ReturnT
            {
                return obj->*fieldPtr;
            };
            // Wrap the member function by adding an argument for the object
            //                  v
            return Wrap<FieldT, T *>(f);
        }

        template <typename T, typename FieldT>
        static typename std::enable_if<std::is_array<FieldT>::value, GenericFuncT>::type
        WrapGetter(FieldT T::*fieldPtr)
        {
            typedef typename std::remove_all_extents<FieldT>::type ReturnT;
            auto f = [=](T *obj) -> ReturnT *
            {
                return obj->*fieldPtr;
            };
            // Wrap the member function by adding an argument for the object
            //                     v
            return Wrap<ReturnT *, T *>(f);
        }


        template <typename FieldT>
        static typename std::enable_if<!std::is_array<FieldT>::value, GenericFuncT>::type
        WrapGetter(FieldT *fieldPtr)
        {
            auto f = [=]() -> FieldT
            {
                return *fieldPtr;
            };
            return Wrap<FieldT>(f);
        }

        template <typename FieldT>
        static typename std::enable_if<std::is_array<FieldT>::value, GenericFuncT>::type
        WrapGetter(FieldT *fieldPtr)
        {
            typedef typename std::remove_all_extents<FieldT>::type ReturnT;
            auto f = [=]() -> ReturnT *
            {
                return *fieldPtr;
            };
            return Wrap<ReturnT *>(f);
        }

        template <typename T, typename FieldT>
        static GenericFuncT WrapSetter(FieldT T::*fieldPtr)
        {
            auto f = [=](T *obj, FieldT value)
            {
                obj->*fieldPtr = value;
            };
            // Wrap the member function by adding an argument for the object
            //                v
            return Wrap<void, T *, FieldT>(f);
        }

        template <typename FieldT>
        static GenericFuncT WrapSetter(FieldT *fieldPtr)
        {
            auto f = [=](FieldT value)
            {
                *fieldPtr = value;
            };
            return Wrap<void, FieldT>(f);
        }

#pragma endregion

#pragma region Constructor

        template <typename T>
        static GenericFuncT WrapDefaultConstructor()
        {
            auto f = [](T *obj)
            {
                new (obj) T();
            };
            return Wrap<void, T *>(f);
        }

        template <typename T, typename ...Args>
        static GenericFuncT WrapConstructor()
        {
            auto f = [](T *obj, Args&& ...args)
            {
                new (obj) T(std::forward<Args>(args)...);
            };
            return Wrap<void, T *, Args...>(f);
        }

#pragma endregion

        template <typename T>
        static GenericFuncT WrapDestructor()
        {
            auto f = [=](T *obj)
            {
                obj->~T();
            };
            // Wrap the member function by adding an argument for the object
            //                v
            return Wrap<void, T *>(f);
        }

    };

};

}