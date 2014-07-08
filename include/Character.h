#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"


class Character : public Entity
{
    public:
        Character();
        Character(b2World *world, float x, float y);
        virtual ~Character();

        void update(float dt = 0) = 0;

        virtual void onAI() = 0;

        virtual void moveLeft() = 0;
        virtual void moveRight() = 0;


        virtual void startContact(Body * body, b2Contact * contact) = 0;
        virtual void endContact(Body * body, b2Contact * contact) = 0;
        virtual void preSolve(Body * body, b2Contact *contact, const b2Manifold *manifold) = 0;
        virtual void postSolve(Body * body, b2Contact* contact, const b2ContactImpulse* impulse) = 0;

    protected:
        float m_attack_period = 1;
        sf::Clock m_timer;
        sf::Clock m_timer_attack;

        float lastImpulse;
        bool firstImpulse = true;
};

#endif // CHARACTER_H
