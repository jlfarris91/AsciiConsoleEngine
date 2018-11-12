#include "Vector4.h"
#include "Vector3.h"
#include <iostream>
#include "Mathf.h"

Vector4 Vector4::Up = Vector4(0, 1, 0, 0);
Vector4 Vector4::Zero = Vector4(0, 0, 0, 0);
Vector4 Vector4::One = Vector4(1, 1, 1, 1);
Vector4 Vector4::Epsilon = Vector4(Mathf::EPSILON, Mathf::EPSILON);

//--------------------------------------------------------------------------------------------
Vector4::Vector4(const Vector4 &rhs)
    : x(rhs.x), y(rhs.y), z(rhs.z), w(rhs.w)
{
}

//--------------------------------------------------------------------------------------------
Vector4::Vector4(float xx, float yy, float zz, float ww)
    : x(xx), y(yy), z(zz), w(ww)
{
}

//--------------------------------------------------------------------------------------------
Vector4::Vector4(const Vector3 &xyz, float w)
    : x(xyz.x), y(xyz.y), z(xyz.z), w(1.0f)
{
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Vector4& Vector4::operator=(const Vector4& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    w = rhs.w;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::operator-(void) const
{
    return Vector4(-x, -y, -z, -w);
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::operator+(const Vector4& rhs) const
{
    return Vector4(x + rhs.x, y + rhs.y, z + rhs.z, w + rhs.w);
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::operator-(const Vector4& rhs) const
{
    return Vector4(x - rhs.x, y - rhs.y, z - rhs.z, w - rhs.w);
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::operator*(const float rhs) const
{
    return Vector4(x * rhs, y * rhs, z * rhs, w * rhs);
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::operator/(const float rhs) const
{
    return Vector4(x / rhs, y / rhs, z / rhs, w / rhs);
}

//--------------------------------------------------------------------------------------------
Vector4 &Vector4::operator+=(const Vector4& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    w += rhs.w;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector4 &Vector4::operator-=(const Vector4& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    w -= rhs.w;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector4 &Vector4::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    w *= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector4 &Vector4::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    w /= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
bool Vector4::operator==(const Vector4& rhs) const
{
    bool distX = abs(rhs.x - x) <= Mathf::EPSILON;
    bool distY = abs(rhs.y - y) <= Mathf::EPSILON;
    bool distZ = abs(rhs.z - z) <= Mathf::EPSILON;
    bool distW = abs(rhs.w - w) <= Mathf::EPSILON;
    return (distX && distY && distZ && distW);
}

//--------------------------------------------------------------------------------------------
bool Vector4::operator!=(const Vector4& rhs) const
{
    return !operator==(rhs);
}

float Vector4::Dot(const Vector4& rhs) const
{
    return x*rhs.x + y*rhs.y + z*rhs.z + w*rhs.w;
}

//--------------------------------------------------------------------------------------------
Vector4 Vector4::Cross(const Vector4& rhs) const
{
    return Vector4((y*rhs.z - z*rhs.y), (z*rhs.x - x*rhs.z), (x*rhs.y - y*rhs.x), 0.0f);
}

//--------------------------------------------------------------------------------------------
float Vector4::Length(void) const
{
    return sqrt(x*x + y*y + z*z + w*w);
}

//--------------------------------------------------------------------------------------------
float Vector4::LengthSq(void) const
{
    return (x*x + y*y + z*z + w*w);
}

//--------------------------------------------------------------------------------------------
void Vector4::Normalize(void)
{
    float l = Length();
    if (l != 0.0f)
    {
        x /= l;
        y /= l;
        z /= l;
        w /= l;
    }
}