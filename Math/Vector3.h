#pragma once

struct Vector2;
struct Vector4;

struct Vector3
{

    static Vector3 Forward;
    static Vector3 Up;
    static Vector3 Right;
    static Vector3 Zero;
    static Vector3 One;
    static Vector3 Epsilon;
    static Vector3 cMin;
    static Vector3 cMax;

    union
    {
        struct
        {
            float x, y, z;
        };

        struct
        {
            float r, g, b;
        };

        float v[3];
    };

    /*
    This union lets us access the data in multiple ways
    All of these are modifying the same location in memory

    Vector3 vec;
    vec.z = 1.0f;
    vec.b = 2.0f;
    vec.v[2] = 3.0f;
    */

    // Non-Default constructor, self explanatory
    Vector3(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f);

    // Copy constructor
    Vector3(const Vector3 &other);

    // Move constructor
    Vector3(const Vector3 &&other);

    Vector3(const Vector2 &other);
    Vector3(const Vector4 &other);

    // Assignment operator, does not need to handle self assignment
    Vector3 &operator=(const Vector3& rhs);

    // Unary negation operator, negates all components and returns a copy
    Vector3 operator-(void) const;

    // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
    // from Vector B, or multiply a vector with a scalar, or divide a vector by 
    // that scalar
    Vector3 operator+(const Vector3& rhs) const;
    Vector3 operator-(const Vector3& rhs) const;
    Vector3 operator*(const float rhs) const;
    Vector3 operator*(const Vector3 &rhs) const;
    Vector3 operator/(const float rhs) const;

    // Same as above, just stores the result in the original vector
    Vector3 &operator+=(const Vector3& rhs);
    Vector3 &operator-=(const Vector3& rhs);
    Vector3 &operator*=(const float rhs);
    Vector3 &operator/=(const float rhs);

    // Returns this vector normalized
    Vector3 Normalized() const;

    // Computes the true length of the vector 
    float Length() const;

    // Computes the squared length of the vector
    float LengthSq() const;

    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
    bool operator==(const Vector3& rhs) const;
    bool operator!=(const Vector3& rhs) const;

    // Computes the dot product with the other vector.
    static float Dot(const Vector3 &lhs, const Vector3& rhs);

    // Computes the cross product with the other vector.
    static Vector3 Cross(const Vector3 &lhs, const Vector3& rhs);

    // Normalizes the vector to make the final vector be of length 1. If the length is zero
    // then this function should not modify anything.
    static void Normalize(Vector3 &out, const Vector3 &in);

    //
    static void Negate(Vector3 &out);

    static Vector3 Min(const Vector3 &a, const Vector3 &b);
    static Vector3 Max(const Vector3 &a, const Vector3 &b);

    bool operator<(const Vector3 & n) const
    {
        //return (this->x < n.x && this->y < n.y && this->z < n.z);
        return this < &n;
    }

    static Vector3 &&All(float val);

};

typedef Vector3 Vec3;
typedef const Vector3 &Vec3Param;