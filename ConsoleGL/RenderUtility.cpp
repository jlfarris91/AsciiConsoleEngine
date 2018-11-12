#include "RenderUtility.h"
#include "DepthBuffer.h"
#include "Math/Mathf.h"
#include "Math/Int3.h"
#include "Math/Matrix4.h"
#include "Math/Vector2.h"
#include "Math/Vector4.h"
#include "Texture.h"
#include "Buffer.h"

#include <fstream>
#include <vector>

namespace ConsoleGL
{

Char RenderUtility::sDefaultAlphaMask = 255;

Vector3 *RenderUtility::sVertexArray = NULL;
uint RenderUtility::sVertexArraySize = 0u;

Vector3 *RenderUtility::sNormalArray = NULL;
uint RenderUtility::sNormalArraySize = 0u;

Vector2 *RenderUtility::sTexCoordsArray = NULL;
uint RenderUtility::sTexCoordsArraySize = 0u;

uint *RenderUtility::sVertexIndexArray = NULL;
uint RenderUtility::sVertexIndexArraySize = 0u;

uint *RenderUtility::sUVIndexArray = NULL;
uint RenderUtility::sUVIndexArraySize = 0u;

uint *RenderUtility::sNormalIndexArray = NULL;
uint RenderUtility::sNormalIndexArraySize = 0u;

Char *RenderUtility::sCharArray = NULL;
uint RenderUtility::sCharArraySize = 0u;

CharAttr *RenderUtility::sAttrArray = NULL;
uint RenderUtility::sAttrArraySize = 0u;

ITexture *RenderUtility::sTex1 = NULL;
CharAttr RenderUtility::sAttr1 = 0;

Matrix4 RenderUtility::sWorldMatrix;
Matrix4 RenderUtility::sViewMatrix;
Matrix4 RenderUtility::sProjectionMatrix;
Matrix4 RenderUtility::sViewportMatrix;
Matrix4 RenderUtility::sNormalMatrix;

void RenderUtility::VertexArray(Vector3 *verts, uint count)
{
    sVertexArray = verts;
    sVertexArraySize = count;
}

void RenderUtility::NormalArray(Vector3 *normals, uint count)
{
    sNormalArray = normals;
    sNormalArraySize = count;
}

void RenderUtility::TexCoordArray(Vector2 *uvs, uint count)
{
    sTexCoordsArray = uvs;
    sTexCoordsArraySize = count;
}

void RenderUtility::VertexIndexArray(uint *indices, uint count)
{
    sVertexIndexArray = indices;
    sVertexIndexArraySize = count;
}

void RenderUtility::UVIndexArray(uint *indices, uint count)
{
    sUVIndexArray = indices;
    sUVIndexArraySize = count;
}

void RenderUtility::NormalIndexArray(uint *indices, uint count)
{
    sNormalIndexArray = indices;
    sNormalIndexArraySize = count;
}

void RenderUtility::DrawImage(Buffer *buffer, const Buffer *image, uint left, uint top)
{

    for (uint y = 0; y < image->height; ++y)
    {
        for (uint x = 0; x < image->width; ++x)
        {
            uint newX = left + x;
            uint newY = top + y;
            if (!buffer->InBounds(newX, newY))
                continue;

            uint ci = x + image->width * y;
            const uchar &c = (uchar &) image->data[ci].Char.AsciiChar;

            if (c == buffer->alphaMask)
                continue;

            uint index = newX + buffer->width * newY;
            buffer->data[index] = image->data[ci];
        }
    }

}

void GetChar(float val, Char &c, CharAttr &attr)
{
    static CharAttr white = attr | FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE;
    static CharAttr black = attr;
    Char asd [] = { 0xDB, 178, 177, 176, c, 176, 177, 178, 0xDB };
    CharAttr asd2 [] = { black, black, black, black, attr, white, white, white, white };
    val = min(max(val, -1), 1);
    int index = Mathf::Round(val * 4) + 4;
    c = asd[index];
    attr = asd2[index];
}

#define round3(v) roundf(v.x), roundf(v.y), roundf(v.z)
#define orient2d(a, b, p) \
    ((b.x - a.x)*(p.y - a.y) - (b.y - a.y)*(p.x - a.x))

std::vector<Vector4> verts;
std::vector<Vector4> normals;
std::vector<float> homogenousW;

inline bool OutsideFrustum(const Vector4 &projVert)
{
    return (projVert.x < -projVert.w || projVert.x > projVert.w ||
        projVert.y < -projVert.w || projVert.y > projVert.w ||
        projVert.z < -projVert.w || projVert.z > projVert.w);
}

void RenderUtility::DrawTriangles(Buffer *buffer, DepthBuffer *depth)
{
    verts.resize(sVertexArraySize * 2);
    normals.resize(sNormalArraySize);
    homogenousW.resize(sVertexArraySize);

    Matrix4 worldToProj;
    Matrix4::MultiplyMM(worldToProj, sViewMatrix, sWorldMatrix);
    Matrix4::MultiplyMM(worldToProj, sProjectionMatrix, worldToProj);

    for (uint i = 0; i < sVertexArraySize; ++i)
    {
        Vector4 &projVert = verts[i * 2 + 0];
        Vector4 &viewPortVert = verts[i * 2 + 1];

        Matrix4::MultiplyMV(projVert, worldToProj, sVertexArray[i]);

        //if (OutsideFrustum(projVert))
        //{
        //    continue;
        //}

        homogenousW[i] = projVert.w;
        projVert /= projVert.w;

        Matrix4::MultiplyMV(viewPortVert, sViewportMatrix, projVert);
    }

    sNormalMatrix = sWorldMatrix;
    Matrix4::Invert(sNormalMatrix, sNormalMatrix);
    Matrix4::Transpose(sNormalMatrix, sNormalMatrix);

    for (uint i = 0; i < sNormalArraySize; ++i)
    {
        Matrix4::MultiplyMV(normals[i], sNormalMatrix, Vector4(sNormalArray[i]));
    }

    for (uint i = 0; i < sVertexIndexArraySize; i += 3)
    {
        DrawIndexedTri(buffer, depth, i / 3,
            &sVertexIndexArray[i],
            &sUVIndexArray[i],
            &sNormalIndexArray[i]);
    }
}

void RenderUtility::DrawIndexedTri(BufferPtr buffer, DepthBufferPtr depth, uint index, uint *vi, uint *vti, uint *vni)
{
    //Vector4 *n0 = nullptr;
    //Vector4 *n1 = nullptr;
    //Vector4 *n2 = nullptr;
    //bool useNormals = sNormalArray && sNormalArraySize > 0;
    //if (useNormals)
    //{
    //    n0 = &normals[vni[0]];
    //    n1 = &normals[vni[1]];
    //    n2 = &normals[vni[2]];
    //}

    Vector2 uv0, uv1, uv2;
    if (sTexCoordsArray && sTexCoordsArraySize > 0)
    {
        uv0 = sTexCoordsArray[vti[0]];
        uv1 = sTexCoordsArray[vti[1]];
        uv2 = sTexCoordsArray[vti[2]];
    }

#define wrap(u) u = ((u < 0.0f) ? 1.0f - (u - (int)u) : (u > 1.0f) ? u - (int)u : u)
    wrap(uv0.x);
    wrap(uv0.y);
    wrap(uv1.x);
    wrap(uv1.y);
    wrap(uv2.x);
    wrap(uv2.y);

    CharAttr attr = sAttr1;//sAttrArray[0];
    //Char c = sCharArray[index];

    Vector4 p0 = verts[vi[0] * 2 + 0];
    Vector4 p1 = verts[vi[1] * 2 + 0];
    Vector4 p2 = verts[vi[2] * 2 + 0];

    //if (p0.z < 0.0f || p1.z < 0.0f || p2.z < 0.0f)
    //    return;

    if (OutsideFrustum(p0) && OutsideFrustum(p1) && OutsideFrustum(p2))
    {
        return;
    }

    float p0w = 1.0f / homogenousW[vi[0]];
    float p1w = 1.0f / homogenousW[vi[1]];
    float p2w = 1.0f / homogenousW[vi[2]];

    p0 = verts[vi[0] * 2 + 1];
    p1 = verts[vi[1] * 2 + 1];
    p2 = verts[vi[2] * 2 + 1];

    Int3 v0 = Int3(round3(p0));
    Int3 v1 = Int3(round3(p1));
    Int3 v2 = Int3(round3(p2));

    // Compute triangle bounding box
    int minX = min3(v0.x, v1.x, v2.x);
    int minY = min3(v0.y, v1.y, v2.y);
    int maxX = max3(v0.x, v1.x, v2.x);
    int maxY = max3(v0.y, v1.y, v2.y);

    // Clip against screen bounds
    minX = max(minX, 0);
    minY = max(minY, 0);
    maxX = min(maxX, (int) buffer->width - 1);
    maxY = min(maxY, (int) buffer->height - 1);

    // Triangle setup
    int A12 = v1.y - v2.y, B12 = v2.x - v1.x;
    int A01 = v0.y - v1.y, B01 = v1.x - v0.x;
    int A20 = v2.y - v0.y, B20 = v0.x - v2.x;
    int area = orient2d(v0, v1, v2);

    if (area == 0.0f)
        return;

    float invArea = 1.0f / area;

    // Barycentric coordinates at minX/minY corner
    Int3 p(minX, minY);
    int w0_row = orient2d(v1, v2, p);
    int w1_row = orient2d(v2, v0, p);
    int w2_row = orient2d(v0, v1, p);

    uint texW = sTex1->Width;
    uint texH = sTex1->Height;
    uint texL = texW * texH;
    CharInfo *texData = sTex1->Data;

    // Rasterize
    for (p.y = minY; p.y <= maxY; p.y++)
    {
        // Barycentric coordinates at start of row
        int w0 = w0_row;
        int w1 = w1_row;
        int w2 = w2_row;

        for (p.x = minX; p.x <= maxX; p.x++)
        {
            // If p is on or inside all edges, render pixel.
            if (w0 >= 0 && w1 >= 0 && w2 >= 0)
            {
                float d0 = orient2d(v1, v2, p) * invArea;
                float d1 = orient2d(v2, v0, p) * invArea;
                float d2 = orient2d(v0, v1, p) * invArea;

                float d = d0 * p0w + d1 * p1w + d2 * p2w;

                if (d > depth->GetDepthAt(p.x, p.y))
                {
                    float w = d0 * p0w + d1 * p1w + d2 * p2w;
                    float u = d0 * uv0.x * p0w + d1 * uv1.x * p1w + d2 * uv2.x * p2w;
                    float v = d0 * uv0.y * p0w + d1 * uv1.y * p1w + d2 * uv2.y * p2w;

                    u /= w;
                    v /= w;

                    int tCol = (int) ((1.0f - u) * texW);
                    int tRow = (int) (v * texH);
                    int textureIndex = max(0, min(texL-1, tRow * texW + tCol));
                    char c = texData[textureIndex].Char.AsciiChar;

                    buffer->Plot(c, attr, Split2(p));
                    depth->Plot(d, Split2(p));
                }
            }

            // One step to the right
            w0 += A12;
            w1 += A20;
            w2 += A01;
        }

        // One row step
        w0_row += B12;
        w1_row += B20;
        w2_row += B01;
    }
}

void RenderUtility::DrawText(Buffer *buffer, StringParam text, uint left, uint top, CharAttr attr)
{
    uint extentX = min(buffer->width, left + (uint) text.Length());
    for (uint x = left; x >= 0 && x < extentX; ++x)
    {
        if (buffer->InBounds(x, top))
        {
            uint index = top * buffer->width + x;
            CharInfo &info = buffer->data[index];
            info.Char.AsciiChar = text[x - left];
            info.Attributes |= attr;
        }
    }
}

ITexture *RenderUtility::LoadTexture(StringParam string)
{
    std::ifstream file;
    file.open(string.c_str(), std::ios_base::in);

    Texture *texture = new Texture();
    file >> texture->width;
    file >> texture->height;

    unsigned length = texture->width * texture->height;
    texture->data = new CharInfo[length];

    for (uint i = 0; i < length; ++i)
    {
        file >> texture->data[i].Char.AsciiChar;
        //file >> texture->data[i].Attributes;
    }

    file.close();
    return texture;
}

}