#pragma once
#include <unordered_map>
#include "UnitySceneBlock.h"
#include "UnitySceneObject.h"
#include "UnitySceneBlockHandler.h"
#include "Component.h"

struct UnitySceneObject;
typedef std::unordered_map<FileIdT, UnitySceneObject> ObjectMap;

class UnitySceneLoader
{
public:
    UnitySceneLoader(Meta::Library &library);

    void FromFile(StringParam filename);

    void AddObject(const UnitySceneObject &object);
    UnitySceneObject *GetObject(FileIdT fileId);

    void StartComponent(ComponentHandle component);

    UnitySceneHandlers Handlers;
    UnitySceneHandlers AssetHandlers;
    Meta::Library &MetaLibrary;

private:
    void FromFileInternal(StringParam filename, const UnitySceneHandlers &handlers);

    void HandleBlocks(const UnitySceneHandlers &handlers);
    void HandleObjects(const UnitySceneHandlers &handlers);
    void StartComponents();

    BlockList blocks;
    ObjectMap objects;

    typedef std::vector<ComponentHandle> ComponentList;
    ComponentList startComponents;
};