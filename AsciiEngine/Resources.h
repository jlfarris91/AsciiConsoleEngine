#pragma once
#include <unordered_map>
#include <list>
#include "Asset.h"

class ResourceCreator;
class ResourceLoader;

class Resources
{
public:
    Resources();

    void AddAsset(StringParam typeName, AssetHandle asset);

    AssetHandle GetAsset(StringParam typeName, StringParam name);

    template <typename T>
    Handle<T, StrictIndex> GetAsset(StringParam name);

    AssetHandle LoadAsset(StringParam typeName, StringParam filename);

    void RegisterLoader(ResourceLoader *loader);
    void UnregisterLoader(ResourceLoader *loader);

    void RegisterCreator(ResourceCreator *creator);
    void UnregisterCreator(ResourceCreator *creator);

private:
    std::unordered_map<string, std::unordered_map<string, AssetHandle>> assetTypeMap;
    std::unordered_map<string, ResourceCreator *> resourceCreators;
    std::list<ResourceLoader *> resourceLoaders;
};

extern Resources *gResources;

#include "Resources.inl"