#include "ECS.h"

using namespace GAlpha;

void Entity::AddGroup(Group group)
{
    group_bit_set[group] = true;
    manager.AddToGroup(this, group);
}