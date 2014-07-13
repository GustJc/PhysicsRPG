#ifndef SHOTARROW_H
#define SHOTARROW_H

#include "Shot.h"

struct StickyInfo {
    b2Body* arrowBody;
    b2Body* targetBody;
    b2Joint* joint;
    bool active = false;
    bool operator<(StickyInfo other) const { return arrowBody < other.arrowBody; }
    bool operator==(StickyInfo other) { return arrowBody == other.arrowBody; }
};

class ShotArrow : public Shot
{
public:
    ShotArrow(int id = 0, float px = 0, float py = 0, b2Vec2 force = b2Vec2(0,0));

    virtual void update(float dt = 0);

    virtual void startContact(Body * body, b2Contact *contact);

    virtual void postSolve(Body *body, b2Contact *contact, const b2ContactImpulse *impulse);

private:
    bool hasCollided = false;
    bool glued = false;

    StickyInfo m_collisionToMakeSticky;
};

#endif // SHOTARROW_H
