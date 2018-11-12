#pragma once
#include "Shared/ArrayList.h"
#include "ConsoleGL\RenderUtility.h"

class Camera;
typedef Handle<Camera, StrictIndex> CameraHandle;

class RenderContext;
typedef Handle<RenderContext, StrictIndex> RenderContextHandle;

class Renderer
{
public:
    typedef ArrayList<RenderContextHandle> RenderContextList;
    typedef ArrayList<CameraHandle> CameraList;

    static Renderer &GetInstance()
    {
        static Renderer instance;
        return instance;
    }

    void Render();
    void RenderMesh(RenderContextHandle context) = delete;

    void SetRenderTarget(ConsoleGL::Buffer *buffer);
    void SetDepthBuffer(ConsoleGL::DepthBuffer *depthBuffer);

    void Register(RenderContextHandle context);
    void Unregister(RenderContextHandle contextId);

    void Register(CameraHandle context);
    void Unregister(CameraHandle context);

    void DrawText(uint x, uint y, StringParam text, CharAttr attr);

private:
    Renderer() = default;

    void RenderScene();
    void RenderCamera(CameraHandle camera);

    ConsoleGL::Buffer *buffer = nullptr;
    ConsoleGL::DepthBuffer *depthBuffer = nullptr;
    RenderContextList contexts;
    CameraList cameras;
    uint batches = 0;
    uint calls = 0;
};
