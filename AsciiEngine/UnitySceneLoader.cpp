#include "UnitySceneLoader.h"
#include "UnitySceneBlockHandler.h"
#include "Component.h"
#include "RenderContext.h"

#include <fstream>
#include <sstream>
#include <stack>
#include <Shared/Path.h>

const std::string cBlockPrefix = "---";

void ReadBlocks(std::fstream &file, BlockList &blocks);
UnitySceneBlock DeserializeBlock(StringParam block);

void RegisterDefaults(UnitySceneLoader *loader);

UnitySceneLoader::UnitySceneLoader(Meta::Library &library)
    : MetaLibrary(library)
{
    RegisterDefaults(this);
}

void UnitySceneLoader::FromFile(StringParam filename)
{
    blocks.clear();
    objects.clear();
    startComponents.clear();

    auto &&withoutExt = Path::GetPathWithoutExtension(filename);
    // load assets first
    FromFileInternal(withoutExt + ".assets", AssetHandlers);
    // then load scene objects
    FromFileInternal(withoutExt + ".unity", Handlers);

    // Start components
    StartComponents();
}

void UnitySceneLoader::FromFileInternal(StringParam filename, const UnitySceneHandlers &handlers)
{
    std::fstream file = std::fstream(filename, std::ios_base::in);
    
    if (!file.is_open())
    {
        throw std::exception("Could not open unity scene file.");
    }

    ReadBlocks(file, blocks);

    HandleBlocks(handlers);
    HandleObjects(handlers);
}

void UnitySceneLoader::HandleBlocks(const UnitySceneHandlers &handlers)
{
    for (auto &&handler : handlers.Handlers)
    {
        for (UnitySceneBlock &block : blocks)
        {
            if (block.Handled)
            {
                continue;
            }
            if (handler->TargetName == block.Name)
            {
                handler->Handle(*this, block);
                block.Handled = true;
            }
        }
    }
}

void UnitySceneLoader::HandleObjects(const UnitySceneHandlers &handlers)
{
    for (auto &&handler : handlers.Handlers)
    {
        for (auto &&object : objects)
        {
            if (object.second.Handled)
            {
                continue;
            }
            if (handler->TargetName == object.second.Name)
            {
                handler->PostHandle(*this, object.second);
                object.second.Handled = true;
            }
        }
    }
}

void UnitySceneLoader::StartComponents()
{
    for (auto &&component : startComponents)
    {
        auto &&type = component->GetType();
        if (type->IsSubclassOf(Meta::GetType<Component>()))
        {
            component->Start();
        }
    }
}

size_t GetIndentLevel(StringParam line)
{
    for (size_t i = 0; i < line.Length(); i += 2)
    {
        bool firstCharIsSpace = line[i + 0] == ' ' || line[i + 0] == '-';
        bool secCharIsSpace = line[i + 1] == ' ';
        if (!firstCharIsSpace || !secCharIsSpace)
            return i / 2;
    }
    return string::npos;
}

void UnitySceneLoader::AddObject(const UnitySceneObject &object)
{
    objects[object.FileId] = object;
}

UnitySceneObject *UnitySceneLoader::GetObject(FileIdT fileId)
{
    IfContainerContainsKey(pair, objects, fileId)
    {
        return &pair->second;
    }
    return nullptr;
}

void UnitySceneLoader::StartComponent(ComponentHandle component)
{
    startComponents.push_back(component);
}

void ReadBlocks(std::fstream &file, BlockList &blocks)
{
    std::string line;
    std::string blockString;

    std::getline(file, line);
    std::getline(file, line);

    // Read in each block and deserialize them into UnitySceneBlocks
    while (std::getline(file, line))
    {
        // start of a new block
        if (line.substr(0, 3) == cBlockPrefix)
        {
            // serialize last block
            if (blockString != std::string())
            {
                auto &&block = DeserializeBlock(blockString);
                blocks.push_back(block);
                blockString = std::string();
            }
        }
        blockString += line;
        blockString += '\n';
    }

    if (blockString.size() > 0)
    {
        auto &&block = DeserializeBlock(blockString);
        blocks.push_back(block);
    }
}

UnitySceneBlock DeserializeBlock(StringParam blockString)
{
    std::stringstream stream(blockString);

    UnitySceneBlock root;

    std::stack<UnitySceneBlock*> blocks;
    blocks.push(&root);

    ushort typeId;
    ulong fileId;
    UnitySceneBlock *curr = blocks.top();
    UnitySceneBlock *last = curr;

    string line;
    std::string rawLine;
    while (getline(stream, rawLine))
    {
        line = rawLine;
        // header
        if (line.Substring(0, 3) == cBlockPrefix)
        {
            sscanf_s(line.c_str(), "--- !u!%hu &%lu", &typeId, &fileId);
            getline(stream, rawLine);
            line = rawLine;

            auto &&top = blocks.top();
            top->Name = line.Substring(0, line.Find(':'));
            top->FileId = fileId;
            top->TypeId = typeId;
            continue;
        }

        auto indentLevel = GetIndentLevel(line);
        auto currentIndent = blocks.size();
        if (indentLevel < currentIndent)
        {
            while (blocks.size() > indentLevel)
            {
                blocks.pop();
                curr = last = blocks.top();
            }
        }
        else
        {
            auto strings = line.SplitByFirst(':');
            auto name = strings[0];
            auto value = strings.count == 2 ? strings[1] : string();

            name = name.Remove(' ');
            value = value.Remove(' ');

            UnitySceneBlock child;
            child.Name = name;
            child.Value = value;
            child.Line = line;

            if (indentLevel > currentIndent)
            {
                blocks.push(last);
                curr = blocks.top();
            }

            auto index = curr->Children.size();
            curr->Children.push_back(child);
            last = &curr->Children[index];
        }
    }

    return root;
}

#include "UnitySceneBlockHandlers.h"

#define RegisterObjectHandler(type) \
    loader->Handlers.RegisterHandler(new type())

#define RegisterAssetHandler(type) \
    loader->AssetHandlers.RegisterHandler(new type())

void RegisterDefaults(UnitySceneLoader *loader)
{
    // Scene object handlers
    RegisterObjectHandler(GameObjectBlockHandler);
    RegisterObjectHandler(GameObjectBlockHandler);
    RegisterObjectHandler(TransformBlockHandler);
    RegisterObjectHandler(MeshFilterBlockHandler);
    RegisterObjectHandler(MeshRendererBlockHandler);
    RegisterObjectHandler(CameraBlockHandler);
    RegisterObjectHandler(MonoBehaviourBlockHandler);

    // Resource handlers
    RegisterAssetHandler(TextureBlockHandler);
    RegisterAssetHandler(ObjBlockHandler);
    RegisterAssetHandler(MaterialBlockHandler);
    RegisterAssetHandler(MonoBehaviourAssetHandler);
}