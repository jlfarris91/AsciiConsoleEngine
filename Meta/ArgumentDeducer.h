#pragma once
#include "Collections.h"

namespace Meta
{

class Method;
    
class IArgumentDeducer
{
public:
    virtual ~IArgumentDeducer() = default;
    virtual const Method *DeduceMethod(const MethodCollection &methods, const VariantList &args) const = 0;
    virtual int ScoreMethod(const Method *method, const VariantList &args) const = 0;
};

namespace ArgumentDeducer
{
    extern IArgumentDeducer *Strict;
    extern IArgumentDeducer *Loose;
}

}