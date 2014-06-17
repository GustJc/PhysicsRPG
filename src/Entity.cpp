#include "Entity.h"

Entity::Entity()
{
    //ctor
    is_dead = false;
}

Entity::~Entity()
{
    //dtor
}

void Entity::die()
{
    is_dead = true;
}

bool Entity::isDead()
{
    return is_dead;
}
