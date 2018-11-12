#pragma once
#include "Meta/Interface.h"

struct StrictIndex
{
    unsigned index;
    unsigned index2;

    StrictIndex &operator=(const StrictIndex &rhs)
    {
        this->index = rhs.index;
        this->index2 = rhs.index2;
        return *this;
    }

    bool operator==(const StrictIndex &rhs) const
    {
        return this->index == rhs.index && this->index2 == rhs.index2;
    }

    ReflectType(StrictIndex)
    {
        builder.SetName("StrictIndex");
        builder.AddField("index", &StrictIndex::index);
        builder.AddField("index2", &StrictIndex::index2);
        builder.AddMethod("Assign", &StrictIndex::operator=, { "other" });
        builder.AddMethod("Equals", &StrictIndex::operator==, { "other" });
    }
};