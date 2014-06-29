#ifndef CHARACTER_H
#define CHARACTER_H

#include "Entity.h"


class Character : public Entity
{
    public:
        Character();
        virtual ~Character();

        void update(float dt = 0);

        void onAI();

        void moveLeft();
        void moveRight();

        virtual void startContact(Body * body);
        virtual void postSolve(Body *body, const b2ContactImpulse *impulse);
        virtual bool preSolve(Body *body, b2Contact *contact);

    protected:

        sf::Clock m_timer;
        sf::Clock m_timer_attack;
    private:
};

#endif // CHARACTER_H
