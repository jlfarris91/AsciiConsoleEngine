#pragma once
#include <list>

struct UnitySceneObject;
class UnitySceneLoader;
class UnitySceneBlock;
class UnitySceneHandlers;

class UnitySceneBlockHandlerBase
{
public:
    UnitySceneBlockHandlerBase(StringParam targetName, uchar order = 0);
    virtual ~UnitySceneBlockHandlerBase() = default;
    virtual void Handle(UnitySceneLoader &loader, UnitySceneBlock &block) = 0;
    virtual void PostHandle(UnitySceneLoader &loader, UnitySceneObject &object) {}

    Getter(uchar, Order) const;
    PropertyR(uchar, Order);

    Getter(string, TargetName) const;
    PropertyR(string, TargetName);

protected:
    string targetName;
    uchar order;
    friend class UnitySceneLoader;
    friend class UnitySceneHandlers;
};

class UnitySceneHandlers
{
public:
    typedef std::list<UnitySceneBlockHandlerBase*> BlockHandlerList;
    
    void RegisterHandler(UnitySceneBlockHandlerBase *handler);
    void UnregisterHandler(UnitySceneBlockHandlerBase *handler);

    BlockHandlerList Handlers;
};

extern uchar OrderFirst;
extern uchar OrderLast;
extern uchar OrderComponent;
extern uchar OrderGameObject;
extern uchar OrderResource;

#define DefineUnitySceneBlockHandler(name) \
    class name##BlockHandler : public UnitySceneBlockHandlerBase

#define RegisterUnitySceneBlockHandler(name) \
    static name##BlockHandler _##name##BlockHandler(#name);

#define DefineUnitySceneBlockHandlerConstructor(name) \
    name##BlockHandler(StringParam targetName) \
        : UnitySceneBlockHandlerBase(targetName) {}
