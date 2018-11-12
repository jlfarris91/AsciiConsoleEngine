#include "Resources.h"
#include "ResourceCreator.h"
#include "ResourceLoader.h"
#include "Shared/Exception.h"
#include <fstream>

#include "TextureResourceLoader.h"
#include "ObjResourceLoader.h"

#include <Shared/Path.h>

Resources *gResources = new Resources();

void RegisterDefaults(Resources *);

Resources::Resources()
{
    RegisterDefaults(this);
}

void Resources::AddAsset(StringParam typeName, AssetHandle asset)
{
    auto &&assetMap = assetTypeMap[typeName];
    auto &&assetName = asset->Name;
    IfContainerContainsKey(iter2, assetMap, assetName)
    {
        throw Exception("Resources already contains asset of the type '%s' with the name '%s'.", typeName.c_str(), assetName.c_str());
    }
    assetMap[assetName] = asset;
}

AssetHandle Resources::GetAsset(StringParam typeName, StringParam name)
{
    IfContainerContainsKey(iter, assetTypeMap, typeName)
    {
        auto &&assetMap = assetTypeMap[typeName];
        IfContainerContainsKey(iter2, assetMap, name)
        {
            return iter2->second;
        }
        return AssetHandle::InvalidHandle;
    }
    return AssetHandle::InvalidHandle;
}

AssetHandle Resources::LoadAsset(StringParam typeName, StringParam filename)
{
    auto &&ext = Path::GetExtension(filename);
    if (ext == string())
    {
        throw Exception("Asset file path '%s' has no extension.", filename.c_str());
    }

    ResourceLoader *matchingLoader = nullptr;
    for (auto &&loader : resourceLoaders)
    {
        if (loader->TypeName == typeName && loader->DataType == ext)
        {
            matchingLoader = loader;
            break;
        }
    }

    if (matchingLoader == nullptr)
    {
        throw Exception("Could not find ResourceLoader for type '%s' and extension '%s'.",
            typeName.c_str(), ext.c_str());
    }

    auto &&asset = matchingLoader->Load(filename);
    this->AddAsset(typeName, asset);
    return asset;
}

void Resources::RegisterCreator(ResourceCreator *creator)
{
    if (creator == nullptr)
    {
        throw Exception("ResourceCreator is null.");
    }
    resourceCreators[creator->TypeName] = creator;
}

void Resources::UnregisterCreator(ResourceCreator *creator)
{
    if (creator == nullptr)
    {
        throw Exception("ResourceCreator is null.");
    }
    resourceCreators.erase(creator->TypeName);
}

void Resources::RegisterLoader(ResourceLoader *loader)
{
    if (loader == nullptr)
    {
        throw Exception("ResourceLoader is null.");
    }
    resourceLoaders.push_back(loader);
}

void Resources::UnregisterLoader(ResourceLoader *loader)
{
    if (loader == nullptr)
    {
        throw Exception("ResourceLoader is null.");
    }
    resourceLoaders.remove(loader);
}

template <typename T>
class TypedResourceCreator : public ResourceCreator
{
public:
    TypedResourceCreator(StringParam typeName)
        : ResourceCreator(typeName) {}

    AssetHandle Create()
    {
        return T::New();
    }
};

#include "Mesh.h"
#include "Texture.h"

#define RegisterTypeLoader(type) \
    RegisterLoader(new type##ResourceLoader())

#define RegisterTypeCreator(type) \
    RegisterCreator(new TypedResourceCreator<type>(#type))

void RegisterDefaults(Resources *resources)
{
    resources->RegisterTypeLoader(Texture);
    resources->RegisterTypeLoader(Obj);

    resources->RegisterTypeCreator(Mesh);
    resources->RegisterTypeCreator(Texture);
}