/* Start Header -------------------------------------------------------
Copyright (C) 2011 DigiPen Institute of Technology.
Reproduction or disclosure of this file or its contents without the prior written
consent of DigiPen Institute of Technology is prohibited.
File Name: Matrix4.h
Purpose: Basic matrix class.
Language: C++, msvc
Platform: Visual Studio 2012, Windows 7
Project: james.farris_CS300_3
Author: James Farris, james.farris, 50010011
Creation date: 10/20/2013
End Header --------------------------------------------------------*/

#pragma once

struct Vector3;
struct Vector4;

struct Matrix4
{

    static Matrix4 Zero;
    static Matrix4 Identity;

    union
    {
        float m[4][4];
        float v[16];
    };

    /*
    This union lets us access the data in multiple ways
    All of these are modifying the same location in memory

    Matrix4 mtx;
    mtx.m[2][2] = 1.0f;
    mtx.v[10] = 2.0f;
    */

    // Default constructor should initialize to zeroes
    Matrix4(void);

    // Non-default constructor, self-explanatory
    Matrix4(float *v);

    // Non-default constructor, self-explanatory
    Matrix4(float m00, float m01, float m02, float m03,
        float m10, float m11, float m12, float m13,
        float m20, float m21, float m22, float m23,
        float m30, float m31, float m32, float m33);

    // Copy constructor, copies every entry from the other matrix.
    Matrix4(const Matrix4& rhs);

    // Assignment operator, does not need to handle self-assignment
    Matrix4 &operator=(const Matrix4& rhs);

    // Multiplying a Matrix4 with a Vector4
    Vector4 operator*(const Vector4& rhs) const;

    // Basic Matrix4 arithmetic operations
    Matrix4 operator+(const Matrix4& rhs) const;
    Matrix4 operator-(const Matrix4& rhs) const;
    Matrix4 operator*(const Matrix4& rhs) const;

    // Similar to the three above except they modify
    // the original 
    Matrix4 &operator+=(const Matrix4& rhs);
    Matrix4 &operator-=(const Matrix4& rhs);
    Matrix4 &operator*=(const Matrix4& rhs);

    // Scale/Divide the entire matrix by a float
    Matrix4 operator*(const float rhs) const;
    Matrix4 operator/(const float rhs) const;

	// Multiply Vector3
	Vector3 operator*(const Vector3 &vec) const;

    // Same as previous 
    Matrix4 &operator*=(const float rhs);
    Matrix4 &operator/=(const float rhs);

    // Comparison operators which use epsilon
    bool operator==(const Matrix4& rhs) const;
    bool operator!=(const Matrix4& rhs) const;

    // public static helper functions
    static void SetIdentity(Matrix4 &out);
    static void MultiplyMM(Matrix4 &out, const Matrix4 &lhs, const Matrix4 &rhs);
    static void MultiplyMV(Vector3 &out, const Matrix4 &lhs, const Vector3 &rhs);
    static void MultiplyMV(Vector4 &out, const Matrix4 &lhs, const Vector4 &rhs);
    static bool Invert(Matrix4 &out, const Matrix4 &in);
    static void Transpose(Matrix4 &out, const Matrix4 &in);

    static void SetScale(Matrix4 &out, float scaleX, float scaleY, float scaleZ);
    static void SetScale(Matrix4 &out, const Vector3 &scale);
    static void SetRotation(Matrix4 &out, float rads, float x, float y, float z);
    static void SetRotation(Matrix4 &out, float rads, const Vector3 &axis);
    static void SetTranslation(Matrix4 &out, float transX, float transY, float transZ);
    static void SetTranslation(Matrix4 &out, const Vector3 &trans);

    static void LookAt(Matrix4 &out, const Vector3 &eye, const Vector3 &center, const Vector3 &up);
    static void Ortho(Matrix4 &out, float left, float right, float bottom, float top, float near, float far);
    static void Frustum(Matrix4 &out, float left, float right, float bottom, float top, float near, float far);
    static void PerspectiveFov(Matrix4 &out, float fovy, float aspect, float zn, float zf);
    static void Viewport(Matrix4 &out, float left, float right, float bottom, float top);
    static void FromEuler(Matrix4 &out, const Vector3 &euler);

};

typedef const Matrix4 &MatrixParam;