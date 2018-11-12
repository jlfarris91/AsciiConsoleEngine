#include "ObjResourceLoader.h"
#include "Mesh.h"

MeshHandle LoadObj(StringParam path);

ObjResourceLoader::ObjResourceLoader()
    : ResourceLoader("Mesh", ".obj")
{
}

AssetHandle ObjResourceLoader::Load(StringParam filename)
{
    if (!filename.EndsWith(DataType))
    {

    }
    return LoadObj(filename);
}

#include <fstream>
#include "Math/Vector2.h"
#include "Math/Vector3.h"

MeshHandle LoadObj(StringParam path)
{
    std::ifstream file;
    file.open(path.c_str(), std::ios_base::in);

    if (file.is_open() == false)
    {
        //DebugPrintf(LOG_DEBUG, "DEBUG", "Failed to load %s", filename);
        return MeshHandle::InvalidHandle;
    }

    auto &&mesh = Mesh::New();

    std::string line = "";
    auto x = 0.0f, y = 0.0f, z = 0.0f;

    auto providedNormals = false;
    auto providedUVs = false;

    while (!file.eof())
    {
        std::getline(file, line);

        if (line.length() == 0)
            continue;

        // object
        if (line[0] == 'o')
        {
            char name[128];
            sscanf_s(line.c_str(), "o %s", name);
            mesh->Name = name;
        }
        // object group
        else if (line[0] == 'g')
        {
            char name[128];
            sscanf_s(line.c_str(), "g %s", name);
            mesh->Name = name;
        }
        // vertex data
        else if (line[0] == 'v')
        {
            if (line[1] == 'n')
            {
                providedNormals = true;
                sscanf_s(line.c_str(), "vn %f %f %f", &x, &y, &z);
                mesh->Normals.push_back(Vector3(x, y, z));
            }
            else if (line[1] == 't')
            {
                providedUVs = true;
                sscanf_s(line.c_str(), "vt %f %f", &x, &y);
                mesh->UVs.push_back(Vector2(x, y));
            }
            else
            {
                sscanf_s(line.c_str(), "v %f %f %f", &x, &y, &z);
                mesh->Vertices.push_back(Vector3(x, y, z));
            }
        }
        // faces
        else if (line[0] == 'f')
        {
            unsigned v[3];
            unsigned vt[3];
            unsigned vn[3];
            if (providedNormals && providedUVs)
            {
                sscanf_s(line.c_str(), "f %u/%u/%u %u/%u/%u %u/%u/%u",
                    &v[0], &vt[0], &vn[0], &v[1], &vt[1], &vn[1], &v[2], &vt[2], &vn[2]);
                --v[0]; --v[1]; --v[2];
                --vt[0]; --vt[1]; --vt[2];
                --vn[0]; --vn[1]; --vn[2];
                mesh->VertexIndices.push_range(v);
                mesh->UVIndices.push_range(vt);
                mesh->NormalIndices.push_range(vn);
            }
            else if (providedNormals)
            {
                sscanf_s(line.c_str(), "f %u//%u  %u//%u %u//%u",
                    &v[0], &vn[0], &v[1], &vn[1], &v[2], &vn[2]);
                --v[0]; --v[1]; --v[2];
                --vn[0]; --vn[1]; --vn[2];
                mesh->VertexIndices.push_range(v);
                mesh->NormalIndices.push_range(vn);
            }
            else if (providedUVs)
            {
                sscanf_s(line.c_str(), "f %u/%u  %u/%u %u/%u",
                    &v[0], &vt[0], &v[1], &vt[1], &v[2], &vt[2]);
                --v[0]; --v[1]; --v[2];
                --vt[0]; --vt[1]; --vt[2];
                mesh->VertexIndices.push_range(v);
                mesh->UVIndices.push_range(vt);
            }
            else
            {
                sscanf_s(line.c_str(), "f %u  %u %u",
                    &v[0], &v[1], &v[2]);
                --v[0]; --v[1]; --v[2];
                mesh->VertexIndices.push_range(v);
            }
        }
    }

    return mesh;
}