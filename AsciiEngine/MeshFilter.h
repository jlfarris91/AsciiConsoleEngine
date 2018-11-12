#pragma once
#include "Component.h"
#include "ObjectPool.h"
#include "Mesh.h"

//------------------------------------------------------------------ Mesh Filter
//******************************************************************************
DefineComponentClass(MeshFilter)
{
public:
    DeclareNameProperty(MeshFilter);
    ReflectType(MeshFilter);

    Getter(MeshHandle, Mesh);
    Setter(MeshHandle, Mesh);
    PropertyRW(MeshHandle, Mesh);
private:
    MeshHandle mesh;
};

DefineStrictClassHandle(MeshFilter);