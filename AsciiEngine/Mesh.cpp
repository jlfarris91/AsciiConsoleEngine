#include "Mesh.h"
#include "Math/Vector2.h"
#include "Math/Vector3.h"

DefineReflectedType(Mesh)
{
    builder.AddBase<PoolableObject<Mesh>>();
    ReflectProperty(Vertices);
    ReflectProperty(UVs);
    ReflectProperty(Normals);
    ReflectProperty(VertexIndices);
    ReflectProperty(UVIndices);
    ReflectProperty(NormalIndices);
}

GetterRef(Vector3List, Mesh::Vertices)
{
	return vertices;
}

SetterRef(Vector3List, Mesh::Vertices)
{
	vertices = value;
	dirty = true;
}

GetterRef(Vector2List, Mesh::UVs)
{
	return uvs;
}

SetterRef(Vector2List, Mesh::UVs)
{
	uvs = value;
	dirty = true;
}

GetterRef(Vector3List, Mesh::Normals)
{
	return normals;
}

SetterRef(Vector3List, Mesh::Normals)
{
	normals = value;
	dirty = true;
}

GetterRef(UnsignedList, Mesh::VertexIndices)
{
    return vertexIndices;
}

SetterRef(UnsignedList, Mesh::VertexIndices)
{
    vertexIndices = value;
    dirty = true;
}

GetterRef(UnsignedList, Mesh::UVIndices)
{
    return uvIndices;
}

SetterRef(UnsignedList, Mesh::UVIndices)
{
    uvIndices = value;
    dirty = true;
}

GetterRef(UnsignedList, Mesh::NormalIndices)
{
    return normalIndices;
}

SetterRef(UnsignedList, Mesh::NormalIndices)
{
    normalIndices = value;
    dirty = true;
}