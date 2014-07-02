#ifndef EDITORSTATE_H
#define EDITORSTATE_H

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

class EditorState : public State
{
public:
    EditorState(sf::RenderWindow& wnd);
    virtual ~EditorState();
    void load(int stack = 0);
    int unload();
    eStateType update(float dt);
    void events(sf::Event& event);
    void render();
protected:
    DebugRender* m_debug_render = nullptr;
    b2World* world = nullptr;

    float rotation = 0;

    bool isDebug = true;
    bool isGrid = true;
    bool isSnap = false;

    int selectedId = 1;

    void saveMap(string filename);

    void createWallObject();
private:
    int b_width=16, b_height=16;
    ContactListenner listenner;
};

#endif // EDITORSTATE_H
