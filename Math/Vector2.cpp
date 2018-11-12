#include "Vector2.h"
#include "Vector3.h"
#include "Mathf.h"

const Vector2 Vector2::Up = Vector2(0, 1);
const Vector2 Vector2::Zero = Vector2(0, 0);
const Vector2 Vector2::One = Vector2(1, 1);
const Vector2 Vector2::Epsilon = Vector2(Mathf::EPSILON, Mathf::EPSILON);

//--------------------------------------------------------------------------------------------
Vector2::Vector2(const Vector2 &rhs)
    : x(rhs.x), y(rhs.y)
{
}

//--------------------------------------------------------------------------------------------
Vector2::Vector2(float xx, float yy)
    : x(xx), y(yy)
{
}

//------------------------------------------------------------------------------
Vector2::Vector2(const Vector3 &rhs)
    : x(rhs.x), y(rhs.y)
{
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Vector2& Vector2::operator=(const Vector2& rhs)
{
    x = rhs.x;
    y = rhs.y;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector2 Vector2::operator-(void) const
{
    return Vector2(-x, -y);
}

//--------------------------------------------------------------------------------------------
Vector2 Vector2::operator+(const Vector2& rhs) const
{
    return Vector2(x + rhs.x, y + rhs.y);
}

//--------------------------------------------------------------------------------------------
Vector2 Vector2::operator-(const Vector2& rhs) const
{
    return Vector2(x - rhs.x, y - rhs.y);
}

//--------------------------------------------------------------------------------------------
Vector2 Vector2::operator*(const float rhs) const
{
    return Vector2(x * rhs, y * rhs);
}

//--------------------------------------------------------------------------------------------
Vector2 Vector2::operator/(const float rhs) const
{
    return Vector2(x / rhs, y / rhs);
}

//--------------------------------------------------------------------------------------------
Vector2 &Vector2::operator+=(const Vector2& rhs)
{
    x += rhs.x;
    y += rhs.y;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector2 &Vector2::operator-=(const Vector2& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector2 &Vector2::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector2 &Vector2::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
bool Vector2::operator==(const Vector2& rhs) const
{
    bool distX = abs(rhs.x - x) <= Mathf::EPSILON;
    bool distY = abs(rhs.y - y) <= Mathf::EPSILON;
    return (distX && distY);
}

//--------------------------------------------------------------------------------------------
bool Vector2::operator!=(const Vector2& rhs) const
{
    return !operator==(rhs);
}

float Vector2::Dot(const Vector2 &lhs, const Vector2& rhs)
{
    return lhs.x*rhs.x + lhs.y*rhs.y;
}

//--------------------------------------------------------------------------------------------
float Vector2::Length()
{
    return sqrt(x*x + y*y);
}

//--------------------------------------------------------------------------------------------
float Vector2::LengthSq()
{
    return (x*x + y*y);
}

//--------------------------------------------------------------------------------------------
void Vector2::Normalize(Vector2 &rhs)
{
    float l = rhs.Length();
    if (l != 0.0f)
    {
        rhs.x /= l;
        rhs.y /= l;
    }
}