#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Math/Matrix4.h"
#include "Math/Rect.h"

//--------------------------------------------------------------- ProjectionMode
//******************************************************************************
DeclareEnum2(ProjectionMode, Orthographic, Perspective);

#undef near
#undef far

//----------------------------------------------------------------------- Camera
//******************************************************************************
DefineComponentClass(Camera)
{
public:
    DeclareNameProperty(Camera);
    ReflectType(Camera);

    Getter(MatrixParam, ViewMatrix);
    PropertyR(Matrix4, ViewMatrix);

    Getter(MatrixParam, ViewportMatrix);
    PropertyR(Matrix4, ViewportMatrix);

    Getter(MatrixParam, ProjectionMatrix);
    PropertyR(Matrix4, ProjectionMatrix);

    GetSet(float, Fov);
    PropertyRW(float, Fov);

    GetSet(float, Near);
    PropertyRW(float, Near);

    GetSet(float, Far);
    PropertyRW(float, Far);

    GetSet(float, AspectRatio);
    PropertyRW(float, AspectRatio);

    GetSet(ProjectionMode, Projection);
    PropertyRW(ProjectionMode, Projection);

    GetSet(Rect, Size);
    PropertyRW(Rect, Size);

    void Start() override;
    void UpdateCamera();

private:
    Matrix4 viewMatrix;
    Matrix4 viewportMatrix;
    Matrix4 projectionMatrix;
    float fov = 16.0f / 9.0f;
    float near = 0.1f;
    float far = 1000.0f;
    ProjectionMode projection;
    Rect size;
};

DefineStrictClassHandle(Camera);