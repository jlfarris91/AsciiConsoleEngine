#include "Rect.h" 

Rect::Rect(float left, float top, float right, float bottom)
    : left(left), top(top),
      right(right), bottom(bottom)
{
}

Rect::Rect(const Rect &other)
    : left(other.left), top(other.top),
      right(other.right), bottom(other.bottom)
{
}

Rect::Rect(const Rect &&other)
    : left(other.left), top(other.top),
      right(other.right), bottom(other.bottom)
{
}

Rect &Rect::operator=(const Rect &rhs)
{
    left = rhs.left;
    top = rhs.top;
    right = rhs.right;
    bottom = rhs.bottom;
    return *this;
}

bool Rect::operator==(const Rect &rhs)
{
    return left == rhs.left &&
           top == rhs.top &&
           right == rhs.right &&
           bottom == rhs.bottom;
}

bool Rect::operator!=(const Rect &rhs)
{
    return !operator==(rhs);
}

float Rect::width() const
{
    return right - left;
}

float Rect::height() const
{
    return top - bottom;
}

void Rect::expand(float size)
{
    left -= size;
    right += size;
    bottom -= size;
    top -= size;
}

bool Rect::overlaps(const Rect &other)
{
    return !(other.left > right &&
             other.right < left &&
             other.top < bottom &&
             other.bottom > top);
}

bool Rect::contains(const Rect &other)
{
    return (other.left > left &&
            other.right < right &&
            other.top < top &&
            other.bottom > bottom);
}

bool Rect::contains(Vec2Param point)
{
    return (point.x > left &&
            point.x < right &&
            point.y < top &&
            point.y > bottom);
}