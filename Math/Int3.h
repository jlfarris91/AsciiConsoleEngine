#pragma once

struct Int3;
typedef const Int3 &Int3Param;

struct Int3
{
    int x;
    int y;
    int z;

    Int3(int x = 0, int y = 0, int z = 0)
        : x(x), y(y), z(0)
    {
    }

    bool operator==(const Int3 &rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }

    bool operator!=(const Int3 &rhs) const
    {
        return !(x == rhs.x && y == rhs.y);
    }

    static Int3Param cZero;
};