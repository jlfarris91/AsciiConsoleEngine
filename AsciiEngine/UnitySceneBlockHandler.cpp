#include "UnitySceneBlockHandler.h"

bool initialized = false;

extern uchar OrderFirst         = 0x00;
extern uchar OrderLast          = 0xFE;
extern uchar OrderResource      = 0x0A;
extern uchar OrderComponent     = OrderResource + 0x0A;
extern uchar OrderGameObject    = OrderComponent + 0x0A;

UnitySceneBlockHandlerBase::UnitySceneBlockHandlerBase(StringParam targetName, uchar order)
    : targetName(targetName), order(order)
{
}

Getter(uchar, UnitySceneBlockHandlerBase::Order) const
{
    return order;
}

Getter(string, UnitySceneBlockHandlerBase::TargetName) const
{
    return targetName;
}

struct ComparePred
{
    bool operator ()(UnitySceneBlockHandlerBase *lhs, UnitySceneBlockHandlerBase *rhs)
    {
        return lhs->Order < rhs->Order;
    }
};

void UnitySceneHandlers::RegisterHandler(UnitySceneBlockHandlerBase *handler)
{
    Handlers.push_back(handler);
    Handlers.sort(ComparePred());
}

void UnitySceneHandlers::UnregisterHandler(UnitySceneBlockHandlerBase *handler)
{
    Handlers.remove(handler);
}