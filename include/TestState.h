#ifndef TESTSTATE_H
#define TESTSTATE_H

#include "State.h"

#include "DebugRender.h"
#include <Box2D/Box2D.h>
#include "BoxBody.h"
#include "SpriteBody.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>

class TestState : public State
{
    public:
        TestState(sf::RenderWindow& wnd);
        virtual ~TestState();
        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
    protected:
        DebugRender* m_debug_render = nullptr;
        b2World* world = nullptr;

        float rotation = 0;

        BoxBody* body = nullptr;
        SpriteBody sp_body;
        Animation an_sp;
        sf::Sprite* sp = nullptr;
    private:
};

#endif // TESTSTATE_H
