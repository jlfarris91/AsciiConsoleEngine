#pragma once
#include "Vector3.h"

struct Vector4
{

    static Vector4 Up;
    static Vector4 Zero;
    static Vector4 One;
    static Vector4 Epsilon;

    union
    {
        struct
        {
            float x, y, z, w;
        };

        struct
        {
            float r, g, b, a;
        };

        float v[4];
    };

    /*
    This union lets us access the data in multiple ways
    All of these are modifying the same location in memory

    Vector4 vec;
    vec.z = 1.0f;
    vec.b = 2.0f;
    vec.v[2] = 3.0f;
    */

    // Non-Default constructor, self explanatory
    Vector4(float xx = 0.0f, float yy = 0.0f, float zz = 0.0f, float ww = 0.0f);

    Vector4(const Vector3 &xyz, float w = 0.0f);

    // Copy constructor
    Vector4(const Vector4 &rhs);

    // Assignment operator, does not need to handle self assignment
    Vector4& operator=(const Vector4& rhs);

    // Unary negation operator, negates all components and returns a copy
    Vector4 operator-(void) const;

    // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
    // from Vector B, or multiply a vector with a scalar, or divide a vector by 
    // that scalar
    Vector4 operator+(const Vector4& rhs) const;
    Vector4 operator-(const Vector4& rhs) const;
    Vector4 operator*(const float rhs) const;
    Vector4 operator/(const float rhs) const;

    // Same as above, just stores the result in the original vector
    Vector4& operator+=(const Vector4& rhs);
    Vector4& operator-=(const Vector4& rhs);
    Vector4& operator*=(const float rhs);
    Vector4& operator/=(const float rhs);

    // Comparison operators which should use an epsilon defined in 
    // Utilities.h to see if the value is within a certain range
    // in which case we say they are equivalent.
    bool operator==(const Vector4& rhs) const;
    bool operator!=(const Vector4& rhs) const;

    // Computes the dot product with the other vector. Treat it as 3D vector.
    float Dot(const Vector4& rhs) const;

    // Computes the cross product with the other vector. Treat it as a 3D vector.
    Vector4 Cross(const Vector4& rhs) const;

    // Computes the true length of the vector 
    float Length(void) const;

    // Computes the squared length of the vector
    float LengthSq(void) const;

    // Normalizes the vector to make the final vector be of length 1. If the length is zero
    // then this function should not modify anything.
    void Normalize(void);
};

typedef Vector4 Vec4;
typedef const Vector4 &Vec4Param;