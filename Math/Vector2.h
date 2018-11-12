#pragma once

struct Vector3;

struct Vector2
{

    static const Vector2 Up;
    static const Vector2 Zero;
    static const Vector2 One;
    static const Vector2 Epsilon;

    union
    {
        struct
        {
            float x, y;
        };

        float v[2];
    };

    /*
    This union lets us access the data in multiple ways
    All of these are modifying the same location in memory

    Vector2 vec;
    vec.y = 1.0f;
    vec.v[1] = 3.0f;
    */

    // Non-Default constructor, self explanatory
    Vector2(float xx = 0.0f, float yy = 0.0f);

    // Copy constructor
    Vector2(const Vector2 &rhs);

    explicit Vector2(const Vector3 &rhs);

    // Assignment operator, does not need to handle self assignment
    Vector2& operator=(const Vector2& rhs);

    // Unary negation operator, negates all components and returns a copy
    Vector2 operator-(void) const;

    // Basic Vector math operations. Add Vector to Vector B, or Subtract Vector A 
    // from Vector B, or multiply a vector with a scalar, or divide a vector by 
    // that scalar
    Vector2 operator+(const Vector2& rhs) const;
    Vector2 operator-(const Vector2& rhs) const;
    Vector2 operator*(const float rhs) const;
    Vector2 operator/(const float rhs) const;

    /// Same as above, just stores the result in the original vector
    Vector2 &operator+=(const Vector2& rhs);
    Vector2 &operator-=(const Vector2& rhs);
    Vector2 &operator*=(const float rhs);
    Vector2 &operator/=(const float rhs);

    /// Comparison operators which uses epsilon to see if the value
    /// is within a certain range in which case we say they are equivalent.
    bool operator==(const Vector2& rhs) const;
    /// Comparison operators which uses epsilon to see if the value
    /// is within a certain range in which case we say they are equivalent.
    bool operator!=(const Vector2& rhs) const;

    /// Computes the true length of the vector 
    float Length();

    /// Computes the squared length of the vector
    float LengthSq();

    /// Computes the dot product with the other vector.
    static float Dot(const Vector2 &lhs, const Vector2 &rhs);

    /// Normalizes the vector to make the final vector be of length 1. If the length is zero
    /// then this function should not modify anything.
    static void Normalize(Vector2 &rhs);

};

typedef Vector2 Vec2;
typedef const Vector2 &Vec2Param;