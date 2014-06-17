#include "GameManager.h"

#include "TestState.h"
#include "GameState.h"
#include "MapState.h"
#include "Engine.h"
GameManager::GameManager()
{
    //ctor
    stack = 0;
    mEstadoAtual = nullptr;
}

GameManager::~GameManager()
{
    if(mEstadoAtual != nullptr)
    {
        mEstadoAtual->unload();
        delete mEstadoAtual;
    }
    //dtor
}

int GameManager::run(int , char*[])
{
    sf::RenderWindow& window = Engine::EngineControl.getWindowReference();
    mEstadoAtual = new MapState(window);
    mEstadoAtual->load();

    window.setFramerateLimit(60);
    sf::Clock tempoDecorrido;
    while(window.isOpen())
    {
        window.clear(sf::Color(255,255,255));
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
                break;
            }
            mEstadoAtual->events(event);
        }

        //Update
        float dt = tempoDecorrido.getElapsedTime().asSeconds();
        tempoDecorrido.restart();

        switch(mEstadoAtual->update(dt))
        {
            case GST_GAME:
            {
                stack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new GameState(window);
                mEstadoAtual->load(stack);
                break;
            }
            case GST_TESTE:
            {
                stack = mEstadoAtual->unload();
                delete mEstadoAtual;
                mEstadoAtual = new TestState(window);
                mEstadoAtual->load(stack);
                break;
            }
            case GST_MENU:
                break;
            case GST_MAP:
                break;
            case GST_NONE:
                break;
        }

        //Draw
        mEstadoAtual->render();
        window.display();

    }

    return 0;
}

void GameManager::executeTests()
{
}

void GameManager::loadMainTextures()
{

}
