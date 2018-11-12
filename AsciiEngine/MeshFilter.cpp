#include "MeshFilter.h"
#include "GameObject.h"

//------------------------------------------------------------------ Mesh Filter
//******************************************************************************
DefineReflectedType(MeshFilter)
{
    builder.AddBase<Component>();
    ReflectProperty(Mesh);
}

//******************************************************************************
Getter(MeshHandle, MeshFilter::Mesh)
{
    return mesh;
}

//******************************************************************************
Setter(MeshHandle, MeshFilter::Mesh)
{
    mesh = value;
}