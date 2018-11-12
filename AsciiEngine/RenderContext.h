#pragma once
#include "MeshFilter.h"
#include "MeshRenderer.h"

class RenderContext : public PoolableObject<RenderContext>
{
public:
    MeshFilterHandle mesh;
    MeshRendererHandle renderer;
    TransformHandle transform;

    bool operator==(const RenderContext &rhs) const;
};

DefineStrictClassHandle(RenderContext);