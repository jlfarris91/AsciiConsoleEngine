#include "FPSCamera.h"
#include "AsciiEngine/Input.h"
#include "AsciiEngine/Transform.h"
#include "AsciiEngine/Renderer.h"
#include "AsciiEngine/Camera.h"
#include "AsciiEngine/GameObject.h"
#include "ConsoleGL\Console.h"
#include "Math/Vector2.h"
#include "AsciiEngine/RenderContext.h"

//-------------------------------------------------------------------- FpsCamera
//******************************************************************************
DefineReflectedType(FpsCamera)
{
    builder.AddBase<Component>();
    ReflectField(MouseButton);
    ReflectField(DeadZone);
}

//******************************************************************************
void FpsCamera::Start()
{
    wasDown = false;
}

//******************************************************************************
void FpsCamera::Update()
{
    if (!gInput->IsMouseButtonDown(MouseButtons::Left))
    {
        wasDown = false;
        return;
    }

    auto &&trans = *Transform;
    if (trans == nullptr)
        return;

    auto &&camera = *Owner->GetComponent<Camera>();
    if (camera == nullptr)
        return;

    auto &&position = trans->LocalPosition;
    auto y = position.y;

    if (gInput->IsKeyDown(Keys::W))
    {
        position += trans->Forward;
    }
    else if (gInput->IsKeyDown(Keys::S))
    {
        position -= trans->Forward;
    }

    if (gInput->IsKeyDown(Keys::D))
    {
        position += trans->Right;
    }
    else if (gInput->IsKeyDown(Keys::A))
    {
        position -= trans->Right;
    }

    position.y = y;
    trans->LocalPosition = position;

    auto &&windowRect = gConsole->WindowRect;

    POINT screenPos;
    GetCursorPos(&screenPos);

    Vector2 windowScreenCenter;
    windowScreenCenter.x = windowRect.left + (windowRect.right - windowRect.left) / 2.0f;
    windowScreenCenter.y = windowRect.top + (windowRect.bottom - windowRect.top) / 2.0f;

    auto delta = Vector2((float)screenPos.x, (float)screenPos.y) - windowScreenCenter;
    delta *= 0.1f;

    if (delta.Length() > DeadZone*DeadZone)
    {
        if (wasDown)
        {
            // Rotate the camera
            auto &&rot = trans->LocalRotation;
            rot.x += delta.y;
            rot.y += delta.x;
            rot.z = 0.0f;
            trans->LocalRotation = rot;
        }
        // Move the mouse to the center of the window
        SetCursorPos((int)roundf(windowScreenCenter.x), (int)roundf(windowScreenCenter.y));
    }

    char line[64];
    sprintf_s(line, "Delta: %.2f, %.2f", Split2(delta));
    Renderer::GetInstance().DrawText(0, 6, line, FOREGROUND_RED);    

    wasDown = true;
}