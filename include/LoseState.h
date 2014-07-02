#ifndef LOSESTATE_H
#define LOSESTATE_H

#include "State.h"

class LoseState : public State
{
    public:
        LoseState(sf::RenderWindow& wnd);
        virtual ~LoseState();

        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
    protected:
        sf::Clock m_timer;
        sf::Sprite sp_dot;
    private:
    protected:
    private:
};

#endif // LOSESTATE_H
