#include <string>
#include "Math/Vector2.h"
#include "Math/Vector3.h"
#include "Math/Matrix4.h"

#include "Math/Mathf.h"
#include "AsciiEngine/Input.h"
#include "AsciiEngine/ConsoleEventHandler.h"

#include "AsciiEngine/GameObject.h"
#include "AsciiEngine/Messages.h"

#include "AsciiEngine/UnitySceneLoader.h"
#include "AsciiEngine/Renderer.h"

#include "ConsoleGL\Console.h"
#include "ConsoleGL\DepthBuffer.h"
#include "ConsoleGL\RenderUtility.h"

#include <fstream>
#include <AsciiEngine/Reflections.h>
#include <AsciiEngine/Camera.h>
#include <AsciiEngine/RenderContext.h>
#include <AsciiEngine/Transform.h>
#include "TestComponent.h"

const uint WIDTH = 640;
const uint HEIGHT = 480;

ConsoleGL::Buffer *gPixelBuffer;
ConsoleGL::DepthBuffer *gDepthBuffer;

void UpdateGameObjects();
void DrawCube(Vec3Param pos, Vec3Param scale, Vec3Param euler);
void OnConsoleResize();
void OnKeyTriggered(Message *message);
void Initialize();

float angle = Mathf::PI;

Vector3 *gVertices;
Vector3 *gNormals;
Vector2 *gTexCoords;
CharAttr *gAttributes;
Char *gChars;
uint *gIndices;

Matrix4 gViewMtx, gProjMtx, gViewportMtx;

//0x00ed9564
COLORREF palette[16] =
{
    0x00000000, 0x00ed9564, 0x00008000, 0x00808000,
    0x00000080, 0x00800080, 0x00008080, 0x00c0c0c0,
    0x00808080, 0x00ff0000, 0x0000ff00, 0x00ffff00,
    0x000000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff
};

COLORREF palette2[16] =
{
    0x00000000, 0xFFFFFFFF, 0x00008000, 0x00808000,
    0x00000080, 0x00800080, 0x00008080, 0x00c0c0c0,
    0x00808080, 0x00ff0000, 0x0000ff00, 0x00ffff00,
    0x000000ff, 0x00ff00ff, 0x0000ffff, 0x00ffffff
};

int paletteIndex = 0;

void main()
{
    Reflections::RegisterTypes(*Meta::gLibrary);
    Meta::gLibrary->RegisterType<TestComponent>();

    gDispatcher->Register(MessageId::KeyTriggered, OnKeyTriggered);
	gInput = new Input(gDispatcher);

	auto eventHandler = new ConsoleEventHandler(gInput, gDispatcher);

	gConsole = new ConsoleGL::Console(eventHandler);
    gConsole->Initialize();
    gConsole->Resize(Size(WIDTH, HEIGHT));
    gConsole->SetPalette(palette);
 	gConsole->ResizedCallback = OnConsoleResize;

    Initialize();

    gPixelBuffer = new ConsoleGL::Buffer(WIDTH, HEIGHT);
	gDepthBuffer = new ConsoleGL::DepthBuffer(WIDTH, HEIGHT);

    //ConsoleGL::RenderUtility::sTex1 = texture;
    ConsoleGL::RenderUtility::sAttr1 = FOREGROUND_GREEN;

    Renderer::GetInstance().SetRenderTarget(gPixelBuffer);
    Renderer::GetInstance().SetDepthBuffer(gDepthBuffer);

    UnitySceneLoader loader(*Meta::gLibrary);
    loader.FromFile("Assets/Resources/Scenes/main.unity");

    while (true)
    {
        gPixelBuffer->Clear(ConsoleGL::RenderUtility::sDefaultAlphaMask, BACKGROUND_BLUE);
        gDepthBuffer->Clear(0.0f);

        Time::Update();
		gDispatcher->Update();
        gConsole->Update();
        gInput->Update();

        UpdateGameObjects();

        Renderer::GetInstance().Render();

        char line[256];
        sprintf_s(line, "FPS: %.1f", Time::fps);
        ConsoleGL::RenderUtility::DrawText(gPixelBuffer, line, 0, 0, FOREGROUND_RED);

        gConsole->FillBuffer(gPixelBuffer);
        gConsole->SwapBuffers();
        gConsole->Run();
        //while (gConsole->writing);

        if (gInput->IsKeyTriggered(Keys::Escape))
        {
            break;
        }
    }

}

void UpdateGameObjects()
{
    for (auto &&gameObject : GameObject::Pool)
    {
        if (!gameObject->Initialized)
        {
            auto &components = gameObject->Components;
            for (auto &component : components)
            {
                if (component->IsEnabled)
                {
                    component->Start();
                }
            }
            gameObject->Initialized = true;
        }
    }

    for (auto &&gameObject : GameObject::Pool)
    {
        if (!gameObject->IsEnabled)
        {
            continue;
        }
        
        auto &components = gameObject->Components;
        for (auto &component : components)
        {
            if (component->IsEnabled)
            {
                component->Update();            
            }
        }
    }

    for (auto &&gameObject : GameObject::Pool)
    {
        if (!gameObject->IsEnabled)
        {
            continue;
        }
        
        ComponentList &components = gameObject->Components;
        for (auto &&component : components)
        {
            if (component->IsEnabled)
            {
                component->LateUpdate();
            }
        }
    }
}

void Initialize()
{
    Matrix4::LookAt(gViewMtx, Vector3(0, 0, 50.0f), Vector3::Zero, Vector3::Up);
    ConsoleGL::RenderUtility::sViewMatrix = gViewMtx;

    float buffWidth = WIDTH / 2.0f;
    float buffHeight = HEIGHT / 2.0f;
    Matrix4::PerspectiveFov(gProjMtx, 45.0f, buffWidth / buffHeight, 1.0f, 1000.0f);
    ConsoleGL::RenderUtility::sProjectionMatrix = gProjMtx;

    Matrix4::Viewport(gViewportMtx, 0, (float)WIDTH, 0, (float)HEIGHT);
    ConsoleGL::RenderUtility::sViewportMatrix = gViewportMtx;
}

void OnConsoleResize()
{
	uint width = gConsole->BufferSize.x;
	uint height = gConsole->BufferSize.y;
    gPixelBuffer->Resize(width, height);
	gDepthBuffer->Resize(width, height);

	float buffWidth = (float)gPixelBuffer->width;
	float buffHeight = (float)gPixelBuffer->height;
	Matrix4::PerspectiveFov(gProjMtx, 45.0f, buffWidth / buffHeight, 1.0f, 1000.0f);
    ConsoleGL::RenderUtility::sProjectionMatrix = gProjMtx;

	Matrix4::Viewport(gViewportMtx, 0, buffWidth, 0, buffHeight);
    ConsoleGL::RenderUtility::sViewportMatrix = gViewportMtx;
}

void OnKeyTriggered(Message *message)
{
    auto &&keyboardMessage = (KeyboardMessage*) message;
    if (keyboardMessage->Key == Keys::Q)
    {
        PostQuitMessage(0);
    }
}