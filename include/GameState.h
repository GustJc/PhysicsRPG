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
#include "Flag.h"
#include "ContactListenner.h"

class PlayerEntity;

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

        bool isDebug = false;
        bool isGrid  = false;

        int selectedId = 1;

        PlayerEntity* player;
        Flag* flag;

        void loadMap(string filename);

        void renderUI();

        Body* mock;

    private:
        ContactListenner listenner;
};

#endif // GAMESTATE_H
