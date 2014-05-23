#ifndef GAMESTATE_H
#define GAMESTATE_H
#include "State.h"
#include "DebugRender.h"
#include <Box2D/Box2D.h>
#include "BoxBody.h"
#include "SpriteBody.h"
#include "Animation.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include "Body.h"
#include "ContactListenner.h"

using namespace std;

class GameState : public State
{
    public:
        GameState(sf::RenderWindow& wnd);
        virtual ~GameState();
        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
    protected:
        DebugRender* m_debug_render = nullptr;
        b2World* world = nullptr;

        float rotation = 0;

        vector<Body*> bodylist;
    private:
        ContactListenner listenner;
};

#endif // GAMESTATE_H
