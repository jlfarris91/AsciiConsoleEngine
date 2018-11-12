#include "GameObjectSerializer.h"
#include "GameObject.h"

string GameObjectSerializer::Serialize(void *object)
{
    GameObject *gameObject = (GameObject*) object;

    for (auto &&child : gameObject->Components)
    {

    }

    return string();
}