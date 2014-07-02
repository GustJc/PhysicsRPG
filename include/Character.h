#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"


class Character : public Entity
{
    public:
        Character();
        Character(b2World *world, float x, float y);
        virtual ~Character();

        void update(float dt = 0);

        void onAI();

        void moveLeft();
        void moveRight();


        virtual void startContact(Body * body, b2Contact * contact);
        virtual void preSolve(Body * body, b2Contact *contact, const b2Manifold *manifold);
        virtual void postSolve(Body * body, b2Contact* contact, const b2ContactImpulse* impulse);

    protected:
        float m_attack_period = 1;
        sf::Clock m_timer;
        sf::Clock m_timer_attack;
    private:
        float lastImpulse;
        bool firstImpulse = true;
};

#endif // CHARACTER_H
