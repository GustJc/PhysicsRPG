#ifndef WINSTATE_H
#define WINSTATE_H

#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;

class WinState : public State
{
    public:
        WinState(sf::RenderWindow& wnd);
        virtual ~WinState();

        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
    protected:
        sf::Clock m_timer;
        sf::Sprite sp_dot;
    private:
};

#endif // WINSTATE_H
