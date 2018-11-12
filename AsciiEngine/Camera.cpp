#include "Camera.h"
#include "Renderer.h"
#include "RenderContext.h"
#include "Transform.h"
#include "ConsoleGL\Console.h"

// TODO: remove
#include "GameObject.h"
#include "Game\FpsCamera.h"

#undef far
#undef near

DefineEnum2(ProjectionMode, Orthographic, Perspective);

//----------------------------------------------------------------------- Camera
//******************************************************************************
DefineReflectedType(Camera)
{
    ReflectPropertyRO(ViewMatrix);
    ReflectPropertyRO(ViewportMatrix);
    ReflectPropertyRO(ProjectionMatrix);
    ReflectProperty(Fov);
    ReflectProperty(Near);
    ReflectProperty(Far);
    ReflectProperty(Projection);
    ReflectProperty(Size);
    ReflectMethod(Start);
    ReflectMethod(UpdateCamera);
}

//******************************************************************************
Getter(MatrixParam, Camera::ViewMatrix)
{
    return viewMatrix;
}

//******************************************************************************
Getter(MatrixParam, Camera::ViewportMatrix)
{
    return viewportMatrix;
}

//******************************************************************************
Getter(MatrixParam, Camera::ProjectionMatrix)
{
    return projectionMatrix;
}

//******************************************************************************
Getter(float, Camera::Fov)
{
    return fov;
}

//******************************************************************************
Setter(float, Camera::Fov)
{
    fov = value;
}

//******************************************************************************
Getter(float, Camera::Near)
{
    return near;
}

//******************************************************************************
Setter(float, Camera::Near)
{
    near = value;
}

//******************************************************************************
Getter(float, Camera::Far)
{
    return far;
}

//******************************************************************************
Setter(float, Camera::Far)
{
    far = value;
}

//******************************************************************************
Getter(ProjectionMode, Camera::Projection)
{
    return projection;
}

//******************************************************************************
Setter(ProjectionMode, Camera::Projection)
{
    projection = value;
}

//******************************************************************************
Getter(Rect, Camera::Size)
{
    return size;
}

//******************************************************************************
Setter(Rect, Camera::Size)
{
    size = value;
}

//******************************************************************************
void Camera::Start()
{

    Owner->AddComponent<FpsCamera>();

    Renderer::GetInstance().Register(Self);
}

//******************************************************************************
void Camera::UpdateCamera()
{
    ::Transform *trans = *Transform;
    if (trans == nullptr)
        return;

    auto &&position = trans->Position;
    auto &&forward = trans->Forward;

    float screenWidth = (float)gConsole->BufferSize.x;
    float screenHeight = (float)gConsole->BufferSize.y;

    float left = size.left * screenWidth;
    float right = size.right * screenWidth;
    float top = size.top * screenHeight;
    float bottom = size.bottom * screenHeight;

    Matrix4::LookAt(viewMatrix, position, position + forward, Vector3::Up);
    Matrix4::Viewport(viewportMatrix, left, right, bottom, top);

    float aspect = screenWidth / screenHeight;
    Matrix4::PerspectiveFov(projectionMatrix, fov, aspect, near, far);
}