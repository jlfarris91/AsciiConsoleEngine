#include "Vector3.h"
#include "Vector2.h"
#include "Vector4.h"
#include "Mathf.h"
#include <cfloat>
#include <utility>

Vector3 Vector3::Forward = Vector3(0, 0, 1);
Vector3 Vector3::Up = Vector3(0, 1, 0);
Vector3 Vector3::Right = Vector3(1, 0, 0);
Vector3 Vector3::Zero = Vector3(0, 0, 0);
Vector3 Vector3::One = Vector3(1, 1, 1);
Vector3 Vector3::Epsilon = Vector3(Mathf::EPSILON, Mathf::EPSILON, Mathf::EPSILON);
Vector3 Vector3::cMin = Vector3(FLT_MIN, FLT_MIN, FLT_MIN);
Vector3 Vector3::cMax = Vector3(FLT_MAX, FLT_MAX, FLT_MAX);

//--------------------------------------------------------------------------------------------
Vector3::Vector3(float xx, float yy, float zz)
    : x(xx), y(yy), z(zz)
{
}

//--------------------------------------------------------------------------------------------
Vector3::Vector3(const Vector3 &rhs)
    : x(rhs.x), y(rhs.y), z(rhs.z)
{
}

//--------------------------------------------------------------------------------------------
Vector3::Vector3(const Vector3 &&other)
    : x(other.x), y(other.y), z(other.z)
{
}

//--------------------------------------------------------------------------------------------
Vector3::Vector3(const Vector2 &other)
    : x(other.x), y(other.y), z(0.0f)
{
}

//--------------------------------------------------------------------------------------------
Vector3::Vector3(const Vector4 &other)
    : x(other.x), y(other.y), z(other.z)
{
}

//------------------------------------------------------------------------------
// Public Functions:
//------------------------------------------------------------------------------

Vector3& Vector3::operator=(const Vector3& rhs)
{
    x = rhs.x;
    y = rhs.y;
    z = rhs.z;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator-(void) const
{
    return Vector3(-x, -y, -z);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator+(const Vector3& rhs) const
{
    return Vector3(x + rhs.x, y + rhs.y, z + rhs.z);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator-(const Vector3& rhs) const
{
    return Vector3(x - rhs.x, y - rhs.y, z - rhs.z);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator*(const float rhs) const
{
    return Vector3(x * rhs, y * rhs, z * rhs);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator*(const Vector3 &rhs) const
{
    return Vector3(x * rhs.x, y * rhs.y, z * rhs.z);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::operator/(const float rhs) const
{
    return Vector3(x / rhs, y / rhs, z / rhs);
}

//--------------------------------------------------------------------------------------------
Vector3 &Vector3::operator+=(const Vector3& rhs)
{
    x += rhs.x;
    y += rhs.y;
    z += rhs.z;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector3 &Vector3::operator-=(const Vector3& rhs)
{
    x -= rhs.x;
    y -= rhs.y;
    z -= rhs.z;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector3 &Vector3::operator*=(const float rhs)
{
    x *= rhs;
    y *= rhs;
    z *= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector3 &Vector3::operator/=(const float rhs)
{
    x /= rhs;
    y /= rhs;
    z /= rhs;
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::Normalized() const
{
    Vector3 out;
    float l = sqrt(x*x + y*y + z*z);
    if (l != 0.0f)
    {
        out.x = x / l;
        out.y = y / l;
        out.z = z / l;
    }
    return out;
}

//--------------------------------------------------------------------------------------------
float Vector3::Length() const
{
    return sqrt(x*x + y*y + z*z);
}

//--------------------------------------------------------------------------------------------
float Vector3::LengthSq() const
{
    return (x*x + y*y + z*z);
}

//--------------------------------------------------------------------------------------------
bool Vector3::operator==(const Vector3& rhs) const
{
    bool distX = abs(rhs.x - x) <= Mathf::EPSILON;
    bool distY = abs(rhs.y - y) <= Mathf::EPSILON;
    bool distZ = abs(rhs.z - z) <= Mathf::EPSILON;
    return (distX && distY && distZ);
}

//--------------------------------------------------------------------------------------------
bool Vector3::operator!=(const Vector3& rhs) const
{
    return !operator==(rhs);
}

float Vector3::Dot(const Vector3 &lhs, const Vector3 &rhs)
{
    return (lhs.x*rhs.x + lhs.y*rhs.y + lhs.z*rhs.z);
}

//--------------------------------------------------------------------------------------------
Vector3 Vector3::Cross(const Vector3 &lhs, const Vector3 &rhs)
{
    Vector3 temp;
    temp.x = (lhs.y*rhs.z - lhs.z*rhs.y);
    temp.y = (lhs.z*rhs.x - lhs.x*rhs.z);
    temp.z = (lhs.x*rhs.y - lhs.y*rhs.x);
    return temp;
}

//--------------------------------------------------------------------------------------------
void Vector3::Normalize(Vector3 &out, const Vector3 &in)
{
    float l = sqrt(in.x*in.x + in.y*in.y + in.z*in.z);
    if (l != 0.0f)
    {
        out.x = in.x / l;
        out.y = in.y / l;
        out.z = in.z / l;
    }
}

//--------------------------------------------------------------------------------------------
void Vector3::Negate(Vector3 &out)
{
    out *= -1.0f;
}

//--------------------------------------------------------------------------------------------
Vec3 Vector3::Min(Vec3Param a, Vec3Param b)
{
    return Vec3(Mathf::Min(a.x, b.x), Mathf::Min(a.y, b.y), Mathf::Min(a.z, b.z));
}

//--------------------------------------------------------------------------------------------
Vec3 Vector3::Max(Vec3Param a, Vec3Param b)
{
    return Vec3(Mathf::Max(a.x, b.x), Mathf::Max(a.y, b.y), Mathf::Max(a.z, b.z));
}

//--------------------------------------------------------------------------------------------
Vector3 &&Vector3::All(float val)
{
    return std::move(Vector3(val, val, val));
}