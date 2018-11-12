#include "Matrix4.h"
#include "Vector3.h"
#include "Vector4.h"
#include "Mathf.h"
#include <cstring> // memcpy

Matrix4 Matrix4::Zero = Matrix4(0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0);
Matrix4 Matrix4::Identity = Matrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);

#define CtorSetRow(r) \
    m[r][0] = m##r##0; m[r][1] = m##r##1; m[r][2] = m##r##2; m[r][3] = m##r##3;

Matrix4::Matrix4()
{
    SetIdentity(*this);
}

//--------------------------------------------------------------------------------------------
Matrix4::Matrix4(float *v)
{
    for (unsigned int i = 0; i < 16; ++i)
    {
        this->v[i] = v[i];
    }
}

//--------------------------------------------------------------------------------------------
Matrix4::Matrix4(float m00, float m01, float m02, float m03,
    float m10, float m11, float m12, float m13,
    float m20, float m21, float m22, float m23,
    float m30, float m31, float m32, float m33)
{
    CtorSetRow(0);
    CtorSetRow(1);
    CtorSetRow(2);
    CtorSetRow(3);
}

//--------------------------------------------------------------------------------------------
Matrix4::Matrix4(const Matrix4 &rhs)
{
    operator=(rhs);
}

//--------------------------------------------------------------------------------------------
//
//  Operators
//
//--------------------------------------------------------------------------------------------

Matrix4& Matrix4::operator=(const Matrix4& rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        v[i] = rhs.v[i];
    }
    return *this;
}

//--------------------------------------------------------------------------------------------
Vector4 Matrix4::operator*(const Vector4 &rhs) const
{
    float x = (m[0][0] * rhs.x + m[1][0] * rhs.y + m[2][0] * rhs.z + m[3][0] * rhs.w);
    float y = (m[0][1] * rhs.x + m[1][1] * rhs.y + m[2][1] * rhs.z + m[3][1] * rhs.w);
    float z = (m[0][2] * rhs.x + m[1][2] * rhs.y + m[2][2] * rhs.z + m[3][2] * rhs.w);
    float w = (m[0][3] * rhs.x + m[1][3] * rhs.y + m[2][3] * rhs.z + m[3][3] * rhs.w);
    return Vector4(x, y, z, w);
}

//--------------------------------------------------------------------------------------------
Matrix4 Matrix4::operator+(const Matrix4& rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; ++i)
    {
        result.v[i] = v[i] + rhs.v[i];
    }
    return result;
}

//--------------------------------------------------------------------------------------------
Matrix4 Matrix4::operator-(const Matrix4& rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; ++i)
    {
        result.v[i] = v[i] - rhs.v[i];
    }
    return result;
}

//--------------------------------------------------------------------------------------------
Matrix4 Matrix4::operator*(const Matrix4& rhs) const
{
    Matrix4 temp;
    MultiplyMM(temp, *this, rhs);
    return temp;
}

//--------------------------------------------------------------------------------------------
Matrix4 &Matrix4::operator+=(const Matrix4& rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        v[i] += rhs.v[i];
    }
    return *this;
}

//--------------------------------------------------------------------------------------------
Matrix4 &Matrix4::operator-=(const Matrix4& rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        v[i] -= rhs.v[i];
    }
    return *this;
}

//--------------------------------------------------------------------------------------------
Matrix4 &Matrix4::operator*=(const Matrix4& rhs)
{
    Matrix4 result;
    // multiply the two matrices and store the result in a third
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            for (int x = 0; x < 4; x++)
            {
                result.m[i][j] += m[i][x] * rhs.m[x][j];
            }
        }
    }
    // apply changes to this matrix
    memcpy(v, result.v, sizeof(Matrix4));
    return *this;
}

//--------------------------------------------------------------------------------------------
Matrix4 Matrix4::operator*(const float rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; ++i)
    {
        result.v[i] = v[i] * rhs;
    }
    return result;
}

//--------------------------------------------------------------------------------------------
Matrix4 Matrix4::operator/(const float rhs) const
{
    Matrix4 result;
    for (int i = 0; i < 16; ++i)
    {
        result.v[i] = v[i] / rhs;
    }
    return result;
}

//--------------------------------------------------------------------------------------------
Vector3 Matrix4::operator*(const Vector3 &vec) const
{
	Vector3 temp;
	MultiplyMV(temp, *this, vec);
	return temp;
}

//--------------------------------------------------------------------------------------------
Matrix4 &Matrix4::operator*=(const float rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        v[i] *= rhs;
    }
    return *this;
}

//--------------------------------------------------------------------------------------------
Matrix4 &Matrix4::operator/=(const float rhs)
{
    for (int i = 0; i < 16; ++i)
    {
        v[i] /= rhs;
    }
    return *this;
}

//--------------------------------------------------------------------------------------------
bool Matrix4::operator==(const Matrix4& rhs) const
{
    for (int i = 0; i < 16; ++i)
    {
        if (abs(v[i] - rhs.v[i]) > Mathf::EPSILON)
            return false;
    }
    return true;
}

//--------------------------------------------------------------------------------------------
bool Matrix4::operator!=(const Matrix4& rhs) const
{
    return !(operator==(rhs));
}

//--------------------------------------------------------------------------------------------
void Matrix4::FromEuler(Matrix4 &out, const Vector3 &euler)
{
    float pitch = euler.x * Mathf::DEG_TO_RAD;
    float yaw = euler.y * Mathf::DEG_TO_RAD;
    float roll = euler.z * Mathf::DEG_TO_RAD;

    float ca = cosf(pitch);
    float sa = sinf(pitch);
    float ch = cosf(yaw);
    float sh = sinf(yaw);
    float cb = cosf(roll);
    float sb = sinf(roll);

    out = Matrix4::Identity;
    out.m[0][0] = ch * ca;
    out.m[0][1] = sh*sb - ch*sa*cb;
    out.m[0][2] = ch*sa*sb + sh*cb;
    out.m[1][0] = sa;
    out.m[1][1] = ca*cb;
    out.m[1][2] = -ca*sb;
    out.m[2][0] = -sh*ca;
    out.m[2][1] = sh*sa*cb + ch*sb;
    out.m[2][2] = -sh*sa*sb + ch*cb;
}

//--------------------------------------------------------------------------------------------
//
//  Static Member Functions
//
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
void Matrix4::SetIdentity(Matrix4 &out)
{
    for (int i = 0; i < 4; ++i)
    {
        for (int j = 0; j < 4; ++j)
        {
            out.m[i][j] = (i == j) ? 1.0f : 0.0f;
        }
    }
}

//--------------------------------------------------------------------------------------------
void Matrix4::MultiplyMM(Matrix4 &out, const Matrix4 &lhs, const Matrix4 &rhs)
{
    // if the out ref and the lhs ref are the same it will botch the multiplication,
    // if they are they same, use the temp buffer to store and then copy at the end
    Matrix4 temp;

    temp.v[0] = (lhs.v[0] * rhs.v[0]) + (lhs.v[4] * rhs.v[1]) + (lhs.v[8] * rhs.v[2]) + (lhs.v[12] * rhs.v[3]);
    temp.v[1] = (lhs.v[1] * rhs.v[0]) + (lhs.v[5] * rhs.v[1]) + (lhs.v[9] * rhs.v[2]) + (lhs.v[13] * rhs.v[3]);
    temp.v[2] = (lhs.v[2] * rhs.v[0]) + (lhs.v[6] * rhs.v[1]) + (lhs.v[10] * rhs.v[2]) + (lhs.v[14] * rhs.v[3]);
    temp.v[3] = (lhs.v[3] * rhs.v[0]) + (lhs.v[7] * rhs.v[1]) + (lhs.v[11] * rhs.v[2]) + (lhs.v[15] * rhs.v[3]);
    temp.v[4] = (lhs.v[0] * rhs.v[4]) + (lhs.v[4] * rhs.v[5]) + (lhs.v[8] * rhs.v[6]) + (lhs.v[12] * rhs.v[7]);
    temp.v[5] = (lhs.v[1] * rhs.v[4]) + (lhs.v[5] * rhs.v[5]) + (lhs.v[9] * rhs.v[6]) + (lhs.v[13] * rhs.v[7]);
    temp.v[6] = (lhs.v[2] * rhs.v[4]) + (lhs.v[6] * rhs.v[5]) + (lhs.v[10] * rhs.v[6]) + (lhs.v[14] * rhs.v[7]);
    temp.v[7] = (lhs.v[3] * rhs.v[4]) + (lhs.v[7] * rhs.v[5]) + (lhs.v[11] * rhs.v[6]) + (lhs.v[15] * rhs.v[7]);
    temp.v[8] = (lhs.v[0] * rhs.v[8]) + (lhs.v[4] * rhs.v[9]) + (lhs.v[8] * rhs.v[10]) + (lhs.v[12] * rhs.v[11]);
    temp.v[9] = (lhs.v[1] * rhs.v[8]) + (lhs.v[5] * rhs.v[9]) + (lhs.v[9] * rhs.v[10]) + (lhs.v[13] * rhs.v[11]);
    temp.v[10] = (lhs.v[2] * rhs.v[8]) + (lhs.v[6] * rhs.v[9]) + (lhs.v[10] * rhs.v[10]) + (lhs.v[14] * rhs.v[11]);
    temp.v[11] = (lhs.v[3] * rhs.v[8]) + (lhs.v[7] * rhs.v[9]) + (lhs.v[11] * rhs.v[10]) + (lhs.v[15] * rhs.v[11]);
    temp.v[12] = (lhs.v[0] * rhs.v[12]) + (lhs.v[4] * rhs.v[13]) + (lhs.v[8] * rhs.v[14]) + (lhs.v[12] * rhs.v[15]);
    temp.v[13] = (lhs.v[1] * rhs.v[12]) + (lhs.v[5] * rhs.v[13]) + (lhs.v[9] * rhs.v[14]) + (lhs.v[13] * rhs.v[15]);
    temp.v[14] = (lhs.v[2] * rhs.v[12]) + (lhs.v[6] * rhs.v[13]) + (lhs.v[10] * rhs.v[14]) + (lhs.v[14] * rhs.v[15]);
    temp.v[15] = (lhs.v[3] * rhs.v[12]) + (lhs.v[7] * rhs.v[13]) + (lhs.v[11] * rhs.v[14]) + (lhs.v[15] * rhs.v[15]);

    // copy if we used the temp buffer, otherwise we are done
    memcpy(out.v, temp.v, sizeof(Matrix4));
}

//--------------------------------------------------------------------------------------------
void Matrix4::MultiplyMV(Vector3 &out, const Matrix4 &lhs, const Vector3 &rhs)
{
    static Vector3 temp;
    temp.x = (lhs.m[0][0] * rhs.x + lhs.m[1][0] * rhs.y + lhs.m[2][0] * rhs.z);
    temp.y = (lhs.m[0][1] * rhs.x + lhs.m[1][1] * rhs.y + lhs.m[2][1] * rhs.z);
    temp.z = (lhs.m[0][2] * rhs.x + lhs.m[1][2] * rhs.y + lhs.m[2][2] * rhs.z);
    out = temp;
}

//--------------------------------------------------------------------------------------------
void Matrix4::MultiplyMV(Vector4 &out, const Matrix4 &lhs, const Vector4 &rhs)
{
    static Vector4 temp;
    temp.x = (lhs.m[0][0] * rhs.x + lhs.m[1][0] * rhs.y + lhs.m[2][0] * rhs.z + lhs.m[3][0] * rhs.w);
    temp.y = (lhs.m[0][1] * rhs.x + lhs.m[1][1] * rhs.y + lhs.m[2][1] * rhs.z + lhs.m[3][1] * rhs.w);
    temp.z = (lhs.m[0][2] * rhs.x + lhs.m[1][2] * rhs.y + lhs.m[2][2] * rhs.z + lhs.m[3][2] * rhs.w);
    temp.w = (lhs.m[0][3] * rhs.x + lhs.m[1][3] * rhs.y + lhs.m[2][3] * rhs.z + lhs.m[3][3] * rhs.w);
    out = temp;
}

//--------------------------------------------------------------------------------------------
bool Matrix4::Invert(Matrix4 &out, const Matrix4 &in)
{

    double inv[16], det;
    int i;

    inv[0] = in.v[5] * in.v[10] * in.v[15] -
        in.v[5] * in.v[11] * in.v[14] -
        in.v[9] * in.v[6] * in.v[15] +
        in.v[9] * in.v[7] * in.v[14] +
        in.v[13] * in.v[6] * in.v[11] -
        in.v[13] * in.v[7] * in.v[10];

    inv[4] = -in.v[4] * in.v[10] * in.v[15] +
        in.v[4] * in.v[11] * in.v[14] +
        in.v[8] * in.v[6] * in.v[15] -
        in.v[8] * in.v[7] * in.v[14] -
        in.v[12] * in.v[6] * in.v[11] +
        in.v[12] * in.v[7] * in.v[10];

    inv[8] = in.v[4] * in.v[9] * in.v[15] -
        in.v[4] * in.v[11] * in.v[13] -
        in.v[8] * in.v[5] * in.v[15] +
        in.v[8] * in.v[7] * in.v[13] +
        in.v[12] * in.v[5] * in.v[11] -
        in.v[12] * in.v[7] * in.v[9];

    inv[12] = -in.v[4] * in.v[9] * in.v[14] +
        in.v[4] * in.v[10] * in.v[13] +
        in.v[8] * in.v[5] * in.v[14] -
        in.v[8] * in.v[6] * in.v[13] -
        in.v[12] * in.v[5] * in.v[10] +
        in.v[12] * in.v[6] * in.v[9];

    inv[1] = -in.v[1] * in.v[10] * in.v[15] +
        in.v[1] * in.v[11] * in.v[14] +
        in.v[9] * in.v[2] * in.v[15] -
        in.v[9] * in.v[3] * in.v[14] -
        in.v[13] * in.v[2] * in.v[11] +
        in.v[13] * in.v[3] * in.v[10];

    inv[5] = in.v[0] * in.v[10] * in.v[15] -
        in.v[0] * in.v[11] * in.v[14] -
        in.v[8] * in.v[2] * in.v[15] +
        in.v[8] * in.v[3] * in.v[14] +
        in.v[12] * in.v[2] * in.v[11] -
        in.v[12] * in.v[3] * in.v[10];

    inv[9] = -in.v[0] * in.v[9] * in.v[15] +
        in.v[0] * in.v[11] * in.v[13] +
        in.v[8] * in.v[1] * in.v[15] -
        in.v[8] * in.v[3] * in.v[13] -
        in.v[12] * in.v[1] * in.v[11] +
        in.v[12] * in.v[3] * in.v[9];

    inv[13] = in.v[0] * in.v[9] * in.v[14] -
        in.v[0] * in.v[10] * in.v[13] -
        in.v[8] * in.v[1] * in.v[14] +
        in.v[8] * in.v[2] * in.v[13] +
        in.v[12] * in.v[1] * in.v[10] -
        in.v[12] * in.v[2] * in.v[9];

    inv[2] = in.v[1] * in.v[6] * in.v[15] -
        in.v[1] * in.v[7] * in.v[14] -
        in.v[5] * in.v[2] * in.v[15] +
        in.v[5] * in.v[3] * in.v[14] +
        in.v[13] * in.v[2] * in.v[7] -
        in.v[13] * in.v[3] * in.v[6];

    inv[6] = -in.v[0] * in.v[6] * in.v[15] +
        in.v[0] * in.v[7] * in.v[14] +
        in.v[4] * in.v[2] * in.v[15] -
        in.v[4] * in.v[3] * in.v[14] -
        in.v[12] * in.v[2] * in.v[7] +
        in.v[12] * in.v[3] * in.v[6];

    inv[10] = in.v[0] * in.v[5] * in.v[15] -
        in.v[0] * in.v[7] * in.v[13] -
        in.v[4] * in.v[1] * in.v[15] +
        in.v[4] * in.v[3] * in.v[13] +
        in.v[12] * in.v[1] * in.v[7] -
        in.v[12] * in.v[3] * in.v[5];

    inv[14] = -in.v[0] * in.v[5] * in.v[14] +
        in.v[0] * in.v[6] * in.v[13] +
        in.v[4] * in.v[1] * in.v[14] -
        in.v[4] * in.v[2] * in.v[13] -
        in.v[12] * in.v[1] * in.v[6] +
        in.v[12] * in.v[2] * in.v[5];

    inv[3] = -in.v[1] * in.v[6] * in.v[11] +
        in.v[1] * in.v[7] * in.v[10] +
        in.v[5] * in.v[2] * in.v[11] -
        in.v[5] * in.v[3] * in.v[10] -
        in.v[9] * in.v[2] * in.v[7] +
        in.v[9] * in.v[3] * in.v[6];

    inv[7] = in.v[0] * in.v[6] * in.v[11] -
        in.v[0] * in.v[7] * in.v[10] -
        in.v[4] * in.v[2] * in.v[11] +
        in.v[4] * in.v[3] * in.v[10] +
        in.v[8] * in.v[2] * in.v[7] -
        in.v[8] * in.v[3] * in.v[6];

    inv[11] = -in.v[0] * in.v[5] * in.v[11] +
        in.v[0] * in.v[7] * in.v[9] +
        in.v[4] * in.v[1] * in.v[11] -
        in.v[4] * in.v[3] * in.v[9] -
        in.v[8] * in.v[1] * in.v[7] +
        in.v[8] * in.v[3] * in.v[5];

    inv[15] = in.v[0] * in.v[5] * in.v[10] -
        in.v[0] * in.v[6] * in.v[9] -
        in.v[4] * in.v[1] * in.v[10] +
        in.v[4] * in.v[2] * in.v[9] +
        in.v[8] * in.v[1] * in.v[6] -
        in.v[8] * in.v[2] * in.v[5];

    det = in.v[0] * inv[0] + in.v[1] * inv[4] + in.v[2] * inv[8] + in.v[3] * inv[12];

    if (det == 0)
        return false;

    det = 1.0 / det;

    for (i = 0; i < 16; i++)
        out.v[i] = (float) (inv[i] * det);

    return true;
}

//--------------------------------------------------------------------------------------------
void Matrix4::Transpose(Matrix4 &out, const Matrix4 &in)
{
    Matrix4 temp;
    for (int r = 0; r < 4; ++r)
    {
        for (int c = 0; c < 4; ++c)
        {
            temp.m[r][c] = in.m[c][r];
        }
    }
    memcpy(out.v, temp.v, 16 * sizeof(float));
}

//--------------------------------------------------------------------------------------------
void Matrix4::SetScale(Matrix4 &out, float scaleX, float scaleY, float scaleZ)
{
    out.v[0] = scaleX;
    out.v[5] = scaleY;
    out.v[10] = scaleZ;
}

//--------------------------------------------------------------------------------------------
void Matrix4::SetScale(Matrix4 &out, const Vector3 &scale)
{
    out.v[0] = scale.x;
    out.v[5] = scale.y;
    out.v[10] = scale.z;
}

//--------------------------------------------------------------------------------------------
void Matrix4::SetRotation(Matrix4 &out, float rads, float x, float y, float z)
{

    if (rads && (x || y || z))
    {
        double s = sin(rads);
        double c = cos(rads);
        double t = 1.0 - c;
        double sx = s * x;
        double sy = s * y;
        double sz = s *z;
        double txz = t * x * z;
        double txy = t * x * y;
        double tyz = t * y * z;
        out.v[0] = (float) ((t * x * x) + c);
        out.v[1] = (float) (txy + sz);
        out.v[2] = (float) (txz - sy);
        out.v[3] = 0.0f;
        out.v[4] = (float) (txy - sz);
        out.v[5] = (float) ((t * y * y) + c);
        out.v[6] = (float) (tyz + sx);
        out.v[7] = 0.0f;
        out.v[8] = (float) (txz + sy);
        out.v[9] = (float) (tyz - sx);
        out.v[10] = (float) ((t * z * z) + c);
        out.v[11] = 0.0f;
        out.v[12] = 0.0f;
        out.v[13] = 0.0f;
        out.v[14] = 0.0f;
        out.v[15] = 1.0f;
    }

}

//--------------------------------------------------------------------------------------------
void Matrix4::SetRotation(Matrix4 &out, float rads, const Vector3 &axis)
{
    SetRotation(out, rads, axis.x, axis.y, axis.z);
}

//--------------------------------------------------------------------------------------------
void Matrix4::SetTranslation(Matrix4 &out, float transX, float transY, float transZ)
{
    out.v[12] = transX;
    out.v[13] = transY;
    out.v[14] = transZ;
}

//------------------------------------------------------------------------------
void Matrix4::SetTranslation(Matrix4 &out, const Vector3 &trans)
{
    out.v[12] = trans.x;
    out.v[13] = trans.y;
    out.v[14] = trans.z;
}

//------------------------------------------------------------------------------
void Matrix4::LookAt(Matrix4 &out, const Vector3 &eye, const Vector3 &center, const Vector3 &up)
{
    Vector3 xaxis, yaxis, zaxis;

    zaxis = center - eye;
    Vector3::Normalize(zaxis, zaxis);
    xaxis = Vector3::Cross(up, zaxis);
    Vector3::Normalize(xaxis, xaxis);
    yaxis = Vector3::Cross(zaxis, xaxis);

    out.v[0] = xaxis.x;
    out.v[1] = yaxis.x;
    out.v[2] = zaxis.x;
    out.v[3] = 0.0f;

    out.v[4] = xaxis.y;
    out.v[5] = yaxis.y;
    out.v[6] = zaxis.y;
    out.v[7] = 0.0f;

    out.v[8] = xaxis.z;
    out.v[9] = yaxis.z;
    out.v[10] = zaxis.z;
    out.v[11] = 0.0f;

    out.v[12] = -Vector3::Dot(xaxis, eye);
    out.v[13] = -Vector3::Dot(yaxis, eye);
    out.v[14] = -Vector3::Dot(zaxis, eye);
    out.v[15] = 1.0f;

}

//------------------------------------------------------------------------------
void Matrix4::Ortho(Matrix4 &out, float left, float right, float bottom, float top, float znear, float zfar)
{
    out.v[0] = 2.0f / (right - left);
    out.v[1] = 0.0f;
    out.v[2] = 0.0f;
    out.v[3] = 0.0f;

    out.v[4] = 0.0f;
    out.v[5] = 2.0f / (top - bottom);
    out.v[6] = 0.0f;
    out.v[7] = 0.0f;

    out.v[8] = 0.0f;
    out.v[9] = 0.0f;
    out.v[10] = -2.0f / (zfar - znear);
    out.v[11] = 0.0f;

    out.v[12] = -(right + left) / (right - left);
    out.v[13] = -(top + bottom) / (top - bottom);
    out.v[14] = (zfar + znear) / (zfar - znear);
    out.v[15] = 1.0f;
}

//------------------------------------------------------------------------------
void Matrix4::Frustum(Matrix4 &out, float left, float right, float bottom, float top, float znear, float zfar)
{
    out.v[0] = (2.0f * znear) / right - left;
    out.v[1] = 0.0f;
    out.v[2] = 0.0f;
    out.v[3] = 0.0f;

    out.v[4] = 0.0f;
    out.v[5] = (2.0f * znear) / top - bottom;
    out.v[6] = 0.0f;
    out.v[7] = 0.0f;

    out.v[8] = (right + left) / right - left;
    out.v[9] = (top + bottom) / top - bottom;
    out.v[10] = -((zfar + znear) / zfar - znear);
    out.v[11] = -1.0f;

    out.v[12] = 0.0f;
    out.v[13] = 0.0f;
    out.v[14] = -((2.0f * zfar * znear) / zfar - znear);
    out.v[15] = 0.0f;
}

//------------------------------------------------------------------------------
void Matrix4::PerspectiveFov(Matrix4 &out, float fovy, float aspect, float zn, float zf)
{
    auto yScale = 1 / tanf(fovy / 2);
    auto xScale = yScale / aspect;

    out.v[0] = xScale;
    out.v[1] = 0.0f;
    out.v[2] = 0.0f;
    out.v[3] = 0.0f;

    out.v[4] = 0.0f;
    out.v[5] = yScale;
    out.v[6] = 0.0f;
    out.v[7] = 0.0f;

    out.v[8] = 0.0f;
    out.v[9] = 0.0f;
    out.v[10] = zf / (zf - zn);
    out.v[11] = 1.0f;

    out.v[12] = 0.0f;
    out.v[13] = 0.0f;
    out.v[14] = -(zn * zf) / (zf - zn);
    out.v[15] = 0.0f;

}

void Matrix4::Viewport(Matrix4 &out, float left, float right, float bottom, float top)
{
  out.v[0] = (right - left) / 2.0f;
  out.v[1] = 0.0f;
  out.v[2] = 0.0f;
  out.v[3] = 0.0f;

  out.v[4] = 0.0f;
  out.v[5] = (top - bottom) / 2.0f;
  out.v[6] = 0.0f;
  out.v[7] = 0.0f;

  out.v[8] = 0.0f;
  out.v[9] = 0.0f;
  out.v[10] = 1.0f;
  out.v[11] = 0.0f;

  out.v[12] = (right + left) / 2.0f;
  out.v[13] = (top + bottom) / 2.0f;
  out.v[14] = 0.0f;
  out.v[15] = 1.0f;
}