#include "Renderer.h"
#include "IMesh.h"
#include "MeshFilter.h"
#include "Shared/ArrayList.h"
#include "Camera.h"
#include "RenderContext.h"
#include "Transform.h"
#include "GameObject.h"

#include "ConsoleGL\DepthBuffer.h"

using namespace ConsoleGL;

void SetMeshAttributes(MeshHandle mesh)
{
    RenderUtility::VertexArray(mesh->Vertices.data, mesh->Vertices.count);
    RenderUtility::NormalArray(mesh->Normals.data, mesh->Normals.count);
    RenderUtility::TexCoordArray(mesh->UVs.data, mesh->UVs.count);
    RenderUtility::VertexIndexArray(mesh->VertexIndices.data, mesh->VertexIndices.count);
    RenderUtility::UVIndexArray(mesh->UVIndices.data, mesh->UVIndices.count);
    RenderUtility::NormalIndexArray(mesh->NormalIndices.data, mesh->NormalIndices.count);
}

void SetMatrices(MatrixParam world)
{
    RenderUtility::sWorldMatrix = world;
}

void Renderer::Render()
{
    if (buffer == nullptr || depthBuffer == nullptr)
    {
        return;
    }

    uint batches = 0;
    uint calls = 0;

    for (auto &&camera : cameras)
    {
        if (!camera->IsEnabled)
            continue;
    
        RenderCamera(camera);
    }

    //RenderScene();

    char line[128];
    sprintf_s(line, "Calls: %d Batches: %d", calls, batches);
    RenderUtility::DrawText(buffer, line, 0, 5, FOREGROUND_RED);
}

void Renderer::RenderCamera(CameraHandle cameraHandle)
{
    auto &&camera = *cameraHandle;
    if (camera == nullptr || !camera->IsEnabled)
    {
        // TODO: this should not be null
        return;
    }

    camera->UpdateCamera();
    RenderUtility::sProjectionMatrix = camera->ProjectionMatrix;
    RenderUtility::sViewMatrix = camera->ViewMatrix;
    RenderUtility::sViewportMatrix = camera->ViewportMatrix;
    RenderScene();
}

void Renderer::RenderScene()
{
    MeshHandle currentMesh;
    batches = calls = 0u;

    for (auto &&context : contexts)
    {
        if (!context || !context->mesh.IsAlive || !context->mesh->Mesh.IsAlive)
        {
            continue;
        }

        auto &&mesh = context->mesh->Mesh;
        if (currentMesh != mesh)
        {
            ++batches;
            currentMesh = mesh;
        }

        SetMeshAttributes(currentMesh);
        SetMatrices(context->transform->WorldMtx);

        auto &&material = context->renderer->Materials[0];
        for (auto &&texture : material->Textures)
        {
            RenderUtility::sTex1 = texture->RawTexture;
            RenderUtility::DrawTriangles(buffer, depthBuffer);
            ++calls;
        }
    }
}

void Renderer::SetRenderTarget(Buffer *buffer)
{
    this->buffer = buffer;
}

void Renderer::SetDepthBuffer(DepthBuffer *depthBuffer)
{
    this->depthBuffer = depthBuffer;
}

bool MeshBatchingPred(const RenderContextHandle &lhs, const RenderContextHandle &rhs)
{
    auto &&lhsCasted = const_cast<RenderContextHandle&>(lhs);
    auto &&rhsCasted = const_cast<RenderContextHandle&>(rhs);
    return lhsCasted->mesh->Mesh < rhsCasted->mesh->Mesh;
}

void Renderer::Register(RenderContextHandle context)
{    
    if (!context->mesh.IsAlive || !context->transform.IsAlive)
    {
        return;
    }
    contexts.insert(context, &MeshBatchingPred);
}

void Renderer::Unregister(RenderContextHandle context)
{
    contexts.remove(context);
}

void Renderer::Register(CameraHandle camera)
{
    cameras.push_back(camera);
}

void Renderer::Unregister(CameraHandle camera)
{
    cameras.remove(camera);
}

void Renderer::DrawText(uint x, uint y, StringParam text, CharAttr attr)
{
    RenderUtility::DrawText(buffer, text, x, y, attr);
}