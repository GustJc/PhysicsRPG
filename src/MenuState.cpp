#include "MenuState.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Engine.h"
MenuState::MenuState(sf::RenderWindow &wnd) :
    State(wnd)
{
}

void MenuState::load(int )
{
    TextureManager::TextureControl.load("menu", "data/menu_bg.png");
    TextureManager::TextureControl.load("menu btn", "data/menu_btn_start.png");
    TextureManager::TextureControl.load("menu btn option", "data/menu_btn_option.png");
    TextureManager::TextureControl.load("menu btn exit", "data/menu_btn_exit.png");

    startBtn.setup( sf::Vector2i(176,100), TextureManager::TextureControl.get("menu btn") );
    startBtn.setPosition(280, 170);

    optionsBtn.setup( sf::Vector2i(193,100), TextureManager::TextureControl.get("menu btn option") );
    optionsBtn.setPosition(296,283);

    exitBtn.setup( sf::Vector2i(160,50), TextureManager::TextureControl.get("menu btn exit") );
    exitBtn.setPosition(302,367);

    sf::View& view = Engine::EngineControl.getViewGame();
    view.reset(sf::FloatRect(0, 0, 800, 600));
    view.setCenter(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    window.setView(view);
}

int MenuState::unload()
{
    //TextureManager::TextureControl.unload("menu");
    //TextureManager::TextureControl.unload("menu btn");
    //TextureManager::TextureControl.unload("menu btn on");

    return mStack;
}

eStateType MenuState::update(float )
{
    startBtn.update(sf::Mouse::getPosition(window));
    optionsBtn.update(sf::Mouse::getPosition(window));
    exitBtn.update(sf::Mouse::getPosition(window));

    return mStado;
}

void MenuState::render()
{
    window.draw(sf::Sprite(TextureManager::TextureControl.get("menu")));

    startBtn.render(window);
    optionsBtn.render(window);
    exitBtn.render(window);
}

void MenuState::events(sf::Event &event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Q)
        {
            mStado = GST_MAP;
        }
    }
    else
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            if(startBtn.isOver( mouse ) )
                mStado = GST_MAP;
            if(optionsBtn.isOver( mouse ) )
                mStado = GST_GAME;
            if(exitBtn.isOver( mouse ) )
                mStado = GST_EXIT;

        }
    }
}
