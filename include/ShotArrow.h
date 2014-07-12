#ifndef SHOTARROW_H
#define SHOTARROW_H

#include "Shot.h"

class ShotArrow : public Shot
{
public:
    ShotArrow(int id = 0, float px = 0, float py = 0, b2Vec2 force = b2Vec2(0,0));

    virtual void update(float dt = 0);

    virtual void startContact(Body * body, b2Contact *contact);

private:
    bool hasCollided = false;
};

#endif // SHOTARROW_H
