#pragma once
#include "TypeQualifier.h"
#include <vector>

namespace Meta
{

class Type;

class Variant
{
public:
    static const size_t DataMaxSize = 64;

    Variant();
    ~Variant();

    template <typename T>
    explicit Variant(T obj);

    template <typename T>
    explicit Variant(T &obj);

    template <typename T>
    explicit Variant(T *obj);

    Variant(void *ptr, const Type *type);

    bool operator==(const Variant &rhs);
    bool operator!=(const Variant &rhs);

    template <typename T>
    T As() const;

    template <typename T>
    T *AsPtr() const;

    template <typename T>
    T &AsRef() const;

    Getter(const Meta::Type *, Type) const;
    PropertyR(Meta::Type *, Type);

private:
    
    const Meta::Type *type = nullptr;
    byte stackData[DataMaxSize];
    byte *heapData = nullptr;
    bool isConst = false;
};

typedef Variant object;

}

typedef std::vector<Meta::Variant> VariantList;

#include "Variant.inl"