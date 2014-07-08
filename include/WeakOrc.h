#ifndef WEAKORC_H
#define WEAKORC_H

#include "Character.h"


class WeakOrc : public Character
{
    public:
        WeakOrc();
        WeakOrc(b2World *world, float x, float y);
        virtual ~WeakOrc();

        void update(float dt = 0);

        void onAI();

        void moveLeft();
        void moveRight();


        virtual void startContact(Body * body, b2Contact * contact);
        virtual void endContact(Body * body, b2Contact * contact);
        virtual void preSolve(Body * body, b2Contact *contact, const b2Manifold *manifold);
        virtual void postSolve(Body * body, b2Contact* contact, const b2ContactImpulse* impulse);
    protected:
    private:
};

#endif // WEAKORC_H
