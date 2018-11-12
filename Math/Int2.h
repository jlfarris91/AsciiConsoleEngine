#pragma once

struct Int2
{
    int x;
    int y;
    
    Int2(int x = 0, int y = 0)
        : x(x), y(y)
    {
    }

    Int2(const Int2 &other)
        : x(other.x), y(other.y)
    {
    }

    Int2(const Int2 &&other)
        : x(other.x), y(other.y)
    {
    }

	Int2 operator-(const Int2 &rhs)
	{
		return Int2(x - rhs.x, y - rhs.y);
	}

    Int2 operator+(const Int2 &rhs)
    {
        return Int2(x + rhs.x, y + rhs.y);
    }

    Int2 operator/(const Int2 &rhs)
    {
        return Int2(x / rhs.x, y / rhs.y);
    }

    Int2 operator/(int rhs)
    {
        return Int2(x / rhs, y / rhs);
    }

    Int2 &operator/=(const Int2 &rhs)
    {
        x /= rhs.x;
        y /= rhs.y;
        return *this;
    }

    Int2 &operator/=(int rhs)
    {
        x /= rhs;
        y /= rhs;
        return *this;
    }

    Int2 operator*(const Int2 &rhs)
    {
        return Int2(x * rhs.x, y * rhs.y);
    }

    Int2 operator*(int rhs)
    {
        return Int2(x * rhs, y * rhs);
    }

    Int2 &operator*=(const Int2 &rhs)
    {
        x *= rhs.x;
        y *= rhs.y;
        return *this;
    }

    Int2 &operator*=(int rhs)
    {
        x *= rhs;
        y *= rhs;
        return *this;
    }

    bool operator==(const Int2 &rhs) const
    {
        return (x == rhs.x && y == rhs.y);
    }

    bool operator!=(const Int2 &rhs) const
    {
        return !(x == rhs.x && y == rhs.y);
    }

    Int2 &operator=(const Int2 &rhs)
    {
        this->x = rhs.x;
        this->y = rhs.y;
        return *this;
    }

    static const Int2 &cZero;
};

typedef Int2 Size;
typedef const Size &SizeParam;

#define ToSize(a) (Size{a.X, a.Y})