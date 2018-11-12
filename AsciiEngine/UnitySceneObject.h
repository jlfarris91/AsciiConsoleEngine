#pragma once
#include "UnitySceneLoaderCommon.h"

class UnitySceneBlock;

struct UnitySceneObject
{
    ObjectHandle Object;
    FileIdT FileId = 0;
    string Name;
    UnitySceneBlock *Block = nullptr;
    void *Data = nullptr;
    bool Handled = false;
};
