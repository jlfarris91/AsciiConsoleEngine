#include "MeshRenderer.h"
#include "Renderer.h"
#include "GameObject.h"
#include "MeshFilter.h"
#include "RenderContext.h"
#include "Transform.h"
#include "Camera.h"

//---------------------------------------------------------------- Mesh Renderer
//******************************************************************************
DefineReflectedType(MeshRenderer)
{
    builder.AddBase<Component>();
    ReflectPropertyRO(Materials);
}

//******************************************************************************
MeshRenderer::MeshRenderer()
{
    context = RenderContext::New();
}


//******************************************************************************
Getter(MaterialList &, MeshRenderer::Materials)
{
    return materials;
}

//******************************************************************************
void MeshRenderer::Start()
{
    auto meshFilter = Owner->GetComponent<MeshFilter>();
    auto transform = Owner->Transform;
    if (!meshFilter.IsAlive || !transform.IsAlive)
    {
        return;
    }

    context->renderer = Self;
    context->mesh = meshFilter;
    context->transform = transform;
    Renderer::GetInstance().Register(std::move(context));
}

//******************************************************************************
void MeshRenderer::OnDestroy()
{
    Renderer::GetInstance().Unregister(context);
}