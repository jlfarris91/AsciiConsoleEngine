#pragma once

#include "UnitySceneBlockHandler.h"
#include "UnitySceneLoader.h"
#include "UnitySceneLoaderException.h"

#include "Camera.h"
#include "GameObject.h"
#include "Math/Mathf.h"
#include "MeshFilter.h"
#include "MeshRenderer.h"
#include "Resources.h"
#include "Texture.h"
#include "Transform.h"
#include "Script.h"

//==============================================================================
// GameObject
//==============================================================================
class GameObjectBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    GameObjectBlockHandler() : UnitySceneBlockHandlerBase("GameObject", OrderGameObject)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&gameObject = GameObject::New();

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = gameObject;
        object.Block = &block;

        gameObject->Name = block.GetChildValue("m_Name", string());
        gameObject->IsEnabled = block.GetChildValue("m_IsActive", true);

        loader.AddObject(object);
    }

    void PostHandle(UnitySceneLoader &loader, UnitySceneObject &object) override
    {
        auto &&gameObjectHandle = (GameObjectHandle) object.Object;
        auto &&gameObject = *gameObjectHandle;

        if (object.Block == nullptr)
        {
            throw UnitySceneLoaderException("Block pointer is null.");
        }

        auto &&prop = object.Block->FindChild("m_Component");
        if (prop == nullptr)
        {
            // TODO: log warning
            return;
            //throw UnitySceneLoaderException("Missing required Component array.");
        }

        for (auto &&comp : prop->Children)
        {
            FileIdT fileId = comp.GetFileId();

            auto &&componentObject = loader.GetObject(fileId);
            if (componentObject == nullptr)
            {
                // TODO: warning
                continue;
                //throw UnitySceneLoaderException("Failed to find component with file id %lu.", fileId);
            }

            // Skip adding the Transform component since the GameObject has one by default
            if (componentObject->Name == "Transform")
            {
                continue;
            }

            auto &&componentHandle = (ComponentHandle) componentObject->Object;
            gameObject->AddComponent(componentHandle);
        }
    }
};

//==============================================================================
// Transform
//==============================================================================
class TransformBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    TransformBlockHandler() : UnitySceneBlockHandlerBase("Transform", OrderGameObject + 1)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&gameObjectFileId = block.GetChildValue("m_GameObject", (FileIdT) -1);
        auto &&gameObjectObject = loader.GetObject(gameObjectFileId);
        if (gameObjectObject == nullptr)
        {
            throw Exception("Missing Transform's GameObject.");
        }

        auto &&gameObject = (GameObjectHandle) gameObjectObject->Object;
        auto &&transformHandle = gameObject->Transform;
        auto &&transform = *transformHandle;

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = transformHandle;
        object.Block = &block;

        auto &&quat = block.GetChildValue("m_LocalRotation", Vector4::Zero);
        auto &&eulers = Mathf::EulerFromQuaternion2(quat);
        //eulers.x = 360.0f - eulers.x;
        //eulers.y = 360.0f - eulers.y;
        //eulers.z = 360.0f - eulers.z;
        transform->LocalRotation = eulers;

        transform->LocalPosition = block.GetChildValue("m_LocalPosition", Vector3::Zero);
        transform->LocalScale = block.GetChildValue("m_LocalScale", Vector3::Zero);

        loader.StartComponent(transformHandle);
        loader.AddObject(object);
    }

    void PostHandle(UnitySceneLoader &loader, UnitySceneObject &object) override
    {
        auto &&transform = (TransformHandle) object.Object;

        auto &&block = object.Block;
        if (block == nullptr)
        {
            throw UnitySceneLoaderException("Block pointer is null.");
        }

        auto parentId = block->GetChildValue("m_Father", (FileIdT) -1);

        if (auto &&parentObject = loader.GetObject(parentId))
        {
            auto &&parent = (TransformHandle) parentObject->Object;
            transform->Parent = parent;
        }
    }
};

//==============================================================================
// Camera
//==============================================================================
class CameraBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    CameraBlockHandler() : UnitySceneBlockHandlerBase("Camera", OrderComponent)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&cameraHandle = Camera::New();
        auto &&camera = *cameraHandle;

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = cameraHandle;
        object.Block = &block;

        camera->Near = block.GetChildValue("nearclipplane", 1.0f);
        camera->Far = block.GetChildValue("farclipplane", 1000.0f);
        camera->Fov = block.GetChildValue("fieldofview", 60.0f);
        camera->Projection = ProjectionMode::Perspective;

        if (auto &&viewportRect = block.FindChild("m_NormalizedViewPortRect"))
        {
            Rect rect;
            rect.left = viewportRect->GetChildValue("x", 0.0f);
            rect.top = viewportRect->GetChildValue("y", 0.0f);
            rect.right = rect.left + viewportRect->GetChildValue("width", 1.0f);
            rect.bottom = rect.top + viewportRect->GetChildValue("height", 1.0f);
            camera->Size = rect;
        }

        loader.StartComponent(cameraHandle);
        loader.AddObject(object);
    }
};

//==============================================================================
// MeshFilter
//==============================================================================
class MeshFilterBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    MeshFilterBlockHandler() : UnitySceneBlockHandlerBase("MeshFilter", OrderComponent)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&meshFilter = MeshFilter::New();

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = meshFilter;
        object.Block = &block;

        auto &&meshFileId = block.GetChildValue("m_Mesh", (FileIdT) -1);
        if (meshFileId == (FileIdT) -1)
        {
            throw Exception("MeshFilter block missing m_Mesh property.");
        }

        if (auto &&meshObject = loader.GetObject(meshFileId))
        {
            meshFilter->Mesh = (MeshHandle) meshObject->Object;
        }

        loader.StartComponent(meshFilter);
        loader.AddObject(object);
    }
};

//==============================================================================
// MeshRenderer
//==============================================================================
class MeshRendererBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    MeshRendererBlockHandler() : UnitySceneBlockHandlerBase("MeshRenderer", OrderComponent)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&meshRenderer = MeshRenderer::New();

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = meshRenderer;
        object.Block = &block;

        auto &&materials = block.FindChild("m_Materials");
        if (materials == nullptr)
        {
            throw Exception("MeshRenderer block missing m_Materials property.");
        }

        for (auto &&material : materials->Children)
        {
            material.Value = material.Line.Substring(4, material.Line.Length());
            auto fileId = material.GetFileId();

            auto &&materialObject = loader.GetObject(fileId);
            if (materialObject == nullptr)
            {
                // TODO: log warning
                continue;
                //throw UnitySceneLoaderException("Failed to find child transform with file id %lu.", fileId);
            }

            auto &&materialHandle = static_cast<MaterialHandle>(materialObject->Object);
            meshRenderer->Materials.push_back(materialHandle);
        }

        loader.StartComponent(meshRenderer);
        loader.AddObject(object);
    }
};

//==============================================================================
// Texture
//==============================================================================
class TextureBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    TextureBlockHandler() : UnitySceneBlockHandlerBase("Texture", OrderResource)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&path = block.GetChildValue("path", string());
        auto &&texture = gResources->LoadAsset("Texture", path + ".asc");

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = texture;
        object.Block = &block;

        loader.AddObject(object);
    }
};

#include "Material.h"

//==============================================================================
// Material
//==============================================================================
class MaterialBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    MaterialBlockHandler() : UnitySceneBlockHandlerBase("Material", OrderResource + 1)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&name = block.GetChildValue("name", string());
        auto &&textureFileId = block.GetChildValue<FileIdT>("texture", -1);

        auto &&material = Material::New();
        material->Name = name;

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = material;
        object.Block = &block;

        if (auto &&textureObject = loader.GetObject(textureFileId))
        {
            auto &&texture = (TextureHandle) textureObject->Object;
            material->Textures.push_back(texture);
        }

        gResources->AddAsset("Material", material);
        loader.AddObject(object);
    }

    void PostHandle(UnitySceneLoader &loader, UnitySceneObject &object) override
    {

    }
};

#include "ObjResourceLoader.h"
#include "Mesh.h"

//==============================================================================
// Obj
//==============================================================================
class ObjBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    ObjBlockHandler() : UnitySceneBlockHandlerBase("Mesh", OrderResource)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&ext = block.GetChildValue("ext", string());
        if (ext != ".obj")
        {
            return;
        }

        auto &&path = block.GetChildValue("path", string());
        auto &&mesh = gResources->LoadAsset("Mesh", path + ext);
        mesh->Name = block.GetChildValue("name", string());

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = mesh;
        object.Block = &block;

        loader.AddObject(object);
    }
};

//==============================================================================
// MonoBehaviour (asset)
// - Uses reflection to find appropriate component
//==============================================================================
class MonoBehaviourAssetHandler : public UnitySceneBlockHandlerBase
{
public:
    MonoBehaviourAssetHandler() : UnitySceneBlockHandlerBase("MonoBehaviour", OrderComponent)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&scriptName = block.GetChildValue("name", string());

        auto script = Script::New();
        script->Name = scriptName;

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = script;
        object.Block = &block;

        gResources->AddAsset("Script", script);
        loader.AddObject(object);
    }
};

//==============================================================================
// MonoBehaviour (component)
// - Uses reflection to find appropriate component
//==============================================================================
class MonoBehaviourBlockHandler : public UnitySceneBlockHandlerBase
{
public:
    MonoBehaviourBlockHandler() : UnitySceneBlockHandlerBase("MonoBehaviour", OrderComponent)
    {
    }

    void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) override
    {
        auto &&scriptFileId = block.GetChildValue("m_Script", (FileIdT) -1);
        if (scriptFileId == (FileIdT) -1)
        {
            throw Exception("MonoBehaviour block missing m_Script property.");
        }

        auto &&scriptObject = loader.GetObject(scriptFileId);
        auto &&scriptAsset = (ScriptHandle)scriptObject->Object;
        auto &&scriptName = scriptAsset->Name;

        auto &&componentType = loader.MetaLibrary.GetType(scriptName);

        auto &&newMethod = componentType->GetMethod("New");
        auto &&component = newMethod->Invoke<ComponentHandle>();

        UnitySceneObject object;
        object.Name = block.Name;
        object.FileId = block.FileId;
        object.Object = component;
        object.Block = &block;

        loader.StartComponent(component);
        loader.AddObject(object);
    }
};