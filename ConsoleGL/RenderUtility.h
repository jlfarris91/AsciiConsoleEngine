#pragma once
#include "ConsoleGfx.h"

struct Vector2;
struct Vector3;
struct Matrix4;

namespace ConsoleGL
{

class Console;
class Buffer;
class DepthBuffer;
class ITexture;

#ifdef DrawText
#undef DrawText
#endif

class RenderUtility
{
public:
    static Char sDefaultAlphaMask;

    static Vector3 *sVertexArray;
    static uint sVertexArraySize;

    static Vector3 *sNormalArray;
    static uint sNormalArraySize;

    static Vector2 *sTexCoordsArray;
    static uint sTexCoordsArraySize;

    static uint *sVertexIndexArray;
    static uint sVertexIndexArraySize;

    static uint *sUVIndexArray;
    static uint sUVIndexArraySize;

    static uint *sNormalIndexArray;
    static uint sNormalIndexArraySize;

    static Char *sCharArray;
    static uint sCharArraySize;

    static CharAttr *sAttrArray;
    static uint sAttrArraySize;

    static Matrix4 sWorldMatrix;
    static Matrix4 sViewMatrix;
    static Matrix4 sProjectionMatrix;
    static Matrix4 sViewportMatrix;
    static Matrix4 sNormalMatrix;

    static ITexture *sTex1;
    static CharAttr sAttr1;

    static void VertexArray(Vector3 *verts, uint count);
    static void NormalArray(Vector3 *normals, uint count);
    static void TexCoordArray(Vector2 *uvs, uint count);
    static void VertexIndexArray(uint *indices, uint count);
    static void UVIndexArray(uint *indices, uint count);
    static void NormalIndexArray(uint *indices, uint count);

    static void DrawImage(Buffer *buffer, const Buffer *image, uint left, uint top);
    static void DrawTri(Buffer *buffer, const Vector3 &p0, const Vector3 &p1, const Vector3 &p2, CharAttr attr);
    static void DrawText(Buffer *buffer, StringParam text, uint left, uint top, CharAttr attr);

    static void DrawTriangles(Buffer *buffer, DepthBuffer *depth);

    static ITexture *LoadTexture(StringParam path);

private:

    static void DrawIndexedTri(Buffer *buffer, DepthBuffer *depth, uint index, uint *vi, uint *vti, uint *vni);
};

}