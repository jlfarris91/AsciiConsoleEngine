#pragma once
#include "Generic.h"

namespace Meta
{
    
template <typename ReturnT, typename T, typename ...Args>
ReturnT Method::Invoke(T &obj, Args... args)
{
    return Generic::Invoke<ReturnT>(func, obj, std::forward<Args>(args)...);
}

template <typename ReturnT, typename ...Args>
ReturnT Method::Invoke(Args... args)
{
    return Generic::Invoke<ReturnT>(func, std::forward<Args>(args)...);
}

}
