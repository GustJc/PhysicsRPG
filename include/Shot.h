#ifndef SHOT_H
#define SHOT_H

#include "SpriteBody.h"

class Shot : public SpriteBody
{
public:
    Shot(int id = 0, float px = 0, float py = 0, b2Vec2 force = b2Vec2(0,0), int limit = 1 );

    void update(float dt = 0);

    virtual void startContact(Body* body, b2Contact * contact);

    int getAtk();
protected:
    int atk = 5;
};

#endif // SHOT_H
