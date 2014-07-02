#include "LoseState.h"
#include "State.h"
#include "Effects.h"
#include "Engine.h"

LoseState::LoseState(sf::RenderWindow& wnd)
: State(wnd)
{
    //ctor
}

LoseState::~LoseState()
{
    //dtor
}

void LoseState::events(sf::Event& )
{

}

void LoseState::load(int )
{

}

int LoseState::unload()
{
    return mStack;
}


eStateType LoseState::update(float )
{
    if(this->m_timer.getElapsedTime().asSeconds() > 5)
        this->mStado = GST_MENU;

    return mStado;
}


void LoseState::render()
{
    sf::Text text("YOU LOSE!!!", Engine::EngineControl.getFont(), 70);
    text.setColor(sf::Color::Red);
    text.setPosition(400 - text.getGlobalBounds().width/2, 300);

    this->window.draw(text);
}
