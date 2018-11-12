#include "RenderContext.h"
#include "Transform.h"
#include "GameObject.h"

bool RenderContext::operator==(const RenderContext &rhs) const
{
    return mesh == rhs.mesh && renderer == rhs.renderer && transform == rhs.transform;
}