#ifndef WALL_H
#define WALL_H

#include "Entity.h"

class Wall : public Entity
{
public:
    Wall(int id = 0, float px = 0, float py = 0);

    virtual void startContact(Body* body, b2Contact* contact);

};

#endif // WALL_H
