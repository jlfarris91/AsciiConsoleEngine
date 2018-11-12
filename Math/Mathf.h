#pragma once
#include <cmath>
#include "Vector2.h"
#include "Vector3.h"
#include "Vector4.h"

struct Mathf
{

    static const float EPSILON;
    static const float PI;
    static const float DEG_TO_RAD;
    static const float RAD_TO_DEG;

    //**************************************************************************
    static float Min(float a, float b)
    {
        return (a < b) ? a : b;
    }

    //**************************************************************************
    static float Max(float a, float b)
    {
        return (a > b) ? a : b;
    }

    //**************************************************************************
    static float Clamp(float value, float min, float max)
    {
        return Max(Min(value, max), min);
    }

    //**************************************************************************
    static float Clamp01(float value)
    {
        return Max(Min(value, 1.0f), 0.0f);
    }

    //**************************************************************************
    static float Abs(float value)
    {
        return (value < 0.0f) ? -value : value;
    }

    //**************************************************************************
    static float SmoothDamp(float current, float target, float& currentVelocity,
        float smoothTime, float maxSpeed, float deltaTime)
    {
        smoothTime = Max(0.0001f, smoothTime);
        float num = 2.0f / smoothTime;
        float num2 = num * deltaTime;
        float num3 = 1.0f / (1.0f + num2 + 0.48f * num2 * num2 + 0.235f * num2 * num2 * num2);
        float num4 = current - target;
        float num5 = target;
        float num6 = maxSpeed * smoothTime;
        num4 = Clamp(num4, -num6, num6);
        target = current - num4;
        float num7 = (currentVelocity + num * num4) * deltaTime;
        currentVelocity = (currentVelocity - num * num7) * num3;
        float num8 = target + (num4 + num7) * num3;
        if (num5 - current > 0.0f == num8 > num5)
        {
            num8 = num5;
            currentVelocity = (num8 - num5) / deltaTime;
        }
        return num8;
    }

    //**************************************************************************
    static int Round(float val)
    {
        return (int) floor(val + 0.5f);
    }

    //
    //static Vector3 EulerFromQuaternion(Vec4Param q)
    //{
    //    //float a = q.x;
    //    //float b = q.y;
    //    //float c = q.z;
    //    //float d = q.w;
    //    //float a2 = a * a;
    //    //float b2 = b * b;
    //    //float c2 = c * c;
    //    //float d2 = d * d;
    //    //
    //    //// theta
    //    //float x = -asinf(2 * (b*d - a*c));
    //    //// psi
    //    //float y = atanf((2 * (a*d + b*c)) / ((a2 + b2) - (c2 - d2)));
    //    //// phi
    //    //float z = atanf((2 * (a*b + c*d)) / ((a2 - b2) - (c2 + d2)));
    //    //return Vector3(x, y, z);
    //
    //    auto x = asin(2 * q.x * q.y + 2 * q.z * q.w);
    //    auto y = atan2f(2 * q.y * q.w - 2 * q.x * q.z, 1 - 2 * q.y * q.y - 2 * q.z * q.z);
    //    auto z = atan2f(2 * q.x * q.w - 2 * q.y * q.z, 1 - 2 * q.x * q.x - 2 * q.z * q.z);
    //    return Vector3(x, y, z);
    //}

    static Vector3 EulerFromQuaternion(Vec4Param q1)
    {
        float heading;
        float attitude;
        auto bank = 0.0f;
        auto sqx = q1.x*q1.x;
        auto sqy = q1.y*q1.y;
        auto sqz = q1.z*q1.z;
        auto sqw = q1.w*q1.w;
        auto unit = sqx + sqy + sqz + sqw; // if normalised is one, otherwise is correction factor
        auto test = q1.x*q1.y + q1.z*q1.w;
        if (test > 0.499f*unit)
        {
            // singularity at north pole
            heading = 2 * atan2(q1.x, q1.w);
            attitude = Mathf::PI / 2;
        }
        else if (test < -0.499f*unit)
        {
            // singularity at south pole
            heading = -2 * atan2(q1.x, q1.w);
            attitude = -Mathf::PI / 2;
        }
        else
        {
            heading = atan2(2 * q1.y*q1.w - 2 * q1.x*q1.z, sqx - sqy - sqz + sqw);
            attitude = asin(2 * test / unit);
            bank = atan2(2 * q1.x*q1.w - 2 * q1.y*q1.z, -sqx + sqy - sqz + sqw);
        }
        return Vector3(bank, heading, attitude) * RAD_TO_DEG;
    }

    static Vector3 EulerFromQuaternion2(Vec4Param q1)
    {
        float heading;
        float attitude;
        auto bank = 0.0f;
        auto test = q1.x*q1.y + q1.z*q1.w;
        if (test > 0.499)
        {
            // singularity at north pole
            heading = 2 * atan2f(q1.x, q1.w);
            attitude = PI / 2;
        }
        else if (test < -0.499)
        {
            // singularity at south pole
            heading = -2 * atan2f(q1.x, q1.w);
            attitude = -PI / 2;
        }
        else
        {
            auto sqx = q1.x*q1.x;
            auto sqy = q1.y*q1.y;
            auto sqz = q1.z*q1.z;
            heading = atan2f(2 * q1.y*q1.w - 2 * q1.x*q1.z, 1 - 2 * sqy - 2 * sqz);
            attitude = asinf(2 * test);
            bank = atan2f(2 * q1.x*q1.w - 2 * q1.y*q1.z, 1 - 2 * sqx - 2 * sqz);
        }
        return Vector3(bank, heading, attitude) * RAD_TO_DEG;
    }

    static Vector3 AxisAngleToEuler(Vector3 axis, float angle)
    {
        Vector3 result;
        auto s = sinf(angle);
        auto c = cosf(angle);
        auto t = 1 - c;
        //  if axis is not already normalised then uncomment this
        axis = axis.Normalized();
        if ((axis.x*axis.y*t + axis.z*s) > 0.998)
        {
            // north pole singularity detected
            result.y = 2 * atan2(axis.x*sinf(angle / 2), cosf(angle / 2));
            result.z = PI / 2;
            result.x = 0;
            return result;
        }
        if ((axis.x*axis.y*t + axis.z*s) < -0.998)
        {
            // south pole singularity detected
            result.y = -2 * atan2(axis.x*sinf(angle / 2), cosf(angle / 2));
            result.z = -PI / 2;
            result.x = 0;
            return result;
        }
        result.y = atan2(axis.y * s - axis.x * axis.z * t, 1 - (axis.y*axis.y + axis.z*axis.z) * t);
        result.z = asinf(axis.x * axis.y * t + axis.z * s);
        result.x = atan2(axis.x * s - axis.y * axis.z * t, 1 - (axis.x*axis.x + axis.z*axis.z) * t);
        return result * Mathf::RAD_TO_DEG;
    }

};

#define max3(a, b, c) max(a, max(b, c))
#define min3(a, b, c) min(a, min(b, c))
#define roundf(val) ((int)floor(val+0.5f))

