#ifndef MENUSTATE_H
#define MENUSTATE_H

#include "State.h"
#include "UiButton.h"

class MenuState : public State
{
public:
    MenuState(sf::RenderWindow &wnd);

    // State interface
public:
    void load(int stack);
    int unload();
    eStateType update(float dt);
    void render();
    void events(sf::Event &event);
private:
    UiButton startBtn;
    UiButton optionsBtn;
    UiButton exitBtn;
};

#endif // MENUSTATE_H
