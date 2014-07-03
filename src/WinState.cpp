#include "WinState.h"
#include "State.h"
#include "Effects.h"
#include "Engine.h"

WinState::WinState(sf::RenderWindow& wnd)
: State(wnd)
{
    //ctor
}

WinState::~WinState()
{
    //dtor
}

void WinState::events(sf::Event& )
{

}

void WinState::load(int )
{
    mStack = 1;
}

int WinState::unload()
{
    return mStack;
}


eStateType WinState::update(float )
{
    if(this->m_timer.getElapsedTime().asSeconds() > 5)
        this->mStado = GST_MAP;

    return mStado;
}


void WinState::render()
{
    sf::Text text("YOU WIN!!!", Engine::EngineControl.getFont(), 70);
    text.setColor(sf::Color::Red);
    text.setPosition(400 - text.getGlobalBounds().width/2, 300);

    this->window.draw(text);
}
