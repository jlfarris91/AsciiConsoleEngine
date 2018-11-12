#pragma once
#include "Shared/ArrayList.h"

struct Vector2;
struct Vector3;

typedef ArrayList<Vector2> Vector2List;
typedef ArrayList<Vector3> Vector3List;
typedef ArrayList<uint> UnsignedList;

class IMesh
{
public:
    IGetterRef(Vector3List, Vertices);
    ISetterRef(Vector3List, Vertices);
	PropertyR(Vector3List, Vertices);

    IGetterRef(Vector2List, UVs);
    ISetterRef(Vector2List, UVs);
	PropertyR(Vector2List, UVs);

    IGetterRef(Vector3List, Normals);
    ISetterRef(Vector3List, Normals);
	PropertyR(Vector3List, Normals);

    IGetterRef(UnsignedList, VertexIndices);
    ISetterRef(UnsignedList, VertexIndices);
    PropertyR(UnsignedList, VertexIndices);

    IGetterRef(UnsignedList, UVIndices);
    ISetterRef(UnsignedList, UVIndices);
    PropertyR(UnsignedList, UVIndices);

    IGetterRef(UnsignedList, NormalIndices);
    ISetterRef(UnsignedList, NormalIndices);
    PropertyR(UnsignedList, NormalIndices);
};