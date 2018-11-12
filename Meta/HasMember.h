#pragma once

namespace Meta
{

class Type;
class TypeBuilder;

namespace Internal
{

template <typename T, typename U>
struct HasMemberHelper
{
    typedef char matched;
    typedef long unmatched;

    template <typename C>
    static matched func(typename U::template get<C>*);

    template <typename C>
    static unmatched func(...);

    static const bool has = (sizeof(func<T>(0)) == sizeof(matched));
    static const bool missing = (sizeof(func<T>(0)) == sizeof(unmatched));
};

template <typename T, typename U>
struct HasMember : public std::integral_constant<bool, HasMemberHelper<T, U>::has>
{
};

template <typename T, typename U>
struct MissingMember : public std::integral_constant<bool, HasMemberHelper<T, U>::missing>
{
};

struct HashMember_InitializeMeta
{
    /// <summary>
    /// The compiler attempts to create this struct using the function
    /// InitializeMethod() as a default. If T doesn't have InitializeMethod(), it will be
    /// nullptr which tells HasMember that T doesn't have the method.
    /// </summary>
    template <typename T, void (*)(TypeBuilder &) = &T::InitializeMeta>
    struct get
    {
        // We use a struct because default template parameters are
        // only allowed in templatized classes and structs
    };
};

}

}