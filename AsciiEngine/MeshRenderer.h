#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Material.h"
#include "MeshFilter.h"

class RenderContext;
DefineStrictClassHandle(RenderContext);

typedef std::vector<MaterialHandle> MaterialList;

//---------------------------------------------------------------- Mesh Renderer
//******************************************************************************
DefineComponentClass(MeshRenderer)
{
public:
    DeclareNameProperty(MeshRenderer);
    ReflectType(MeshRenderer);

    MeshRenderer();

    Getter(MaterialList &, Materials);
    PropertyR(MaterialList, Materials);

    void Start() override;
    void OnDestroy() override;

private:
    MaterialList materials;
    RenderContextHandle context;
    MeshFilterHandle meshFilter;
};

DefineStrictClassHandle(MeshRenderer);