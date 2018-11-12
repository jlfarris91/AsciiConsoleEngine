#pragma once
#include "IMesh.h"
#include "Asset.h"
#include "ObjectPool.h"

class Mesh : public Asset, public IMesh, public PoolableObject<Mesh>
{
public:
    ReflectType(Mesh);
    
	GetterRef(Vector3List, Vertices) override;
	SetterRef(Vector3List, Vertices) override;

	GetterRef(Vector2List, UVs) override;
	SetterRef(Vector2List, UVs) override;

	GetterRef(Vector3List, Normals) override;
	SetterRef(Vector3List, Normals) override;

    GetterRef(UnsignedList, VertexIndices) override;
    SetterRef(UnsignedList, VertexIndices) override;

    GetterRef(UnsignedList, UVIndices) override;
    SetterRef(UnsignedList, UVIndices) override;

    GetterRef(UnsignedList, NormalIndices) override;
    SetterRef(UnsignedList, NormalIndices) override;

private:
	Vector3List vertices;
	Vector2List uvs;
	Vector3List normals;

    UnsignedList vertexIndices;
    UnsignedList uvIndices;
    UnsignedList normalIndices;

	bool dirty = false;
};

DefineStrictClassHandle(Mesh);
