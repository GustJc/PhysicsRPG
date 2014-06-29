#include "Engine.h"
#include "Globals.h"
Engine Engine::EngineControl;
std::vector<Body*> Engine::bodylist;
std::vector<Body*> Engine::effectslist;
b2World* Engine::world;

Engine::Engine() :
mWindow(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT), WINDOW_NAME, sf::Style::Close)
{
    mFont.loadFromFile("arial.ttf");

    mViewGame.reset(sf::FloatRect(0, 0, 800, 600));
    mViewGame.setCenter(WINDOW_WIDTH/2.f, WINDOW_HEIGHT/2.f);

    mWindow.setView(mViewGame);

    mEventsPaused = false;
}
Engine::~Engine()
{
    //dtor
}

sf::RenderWindow& Engine::getWindowReference()
{
    return mWindow;
}

sf::Font& Engine::getFont()
{
    return mFont;
}

sf::View& Engine::getViewGame()
{
    return mViewGame;
}

bool Engine::isEventsPaused()
{
    return mEventsPaused;
}

void Engine::setEventsPaused(bool pause)
{
    mEventsPaused = pause;
}

//Draws
void Engine::drawRectVertex(int x, int y, int w, int h, sf::Color color)
{
    sf::VertexArray quad(sf::Quads, 4);
    quad[0].color = color;
    quad[1].color = color;
    quad[2].color = color;
    quad[3].color = color;
    quad[0].position = sf::Vector2f(x,y);
    quad[1].position = sf::Vector2f(x+w,y);
    quad[2].position = sf::Vector2f(x+w,y+h);
    quad[3].position = sf::Vector2f(x,y+h);

    mWindow.draw(quad);
}

void Engine::drawLine(int x, int y, int x2, int y2, sf::Color color)
{
    sf::VertexArray line(sf::Lines, 2);
    line[0].color = color;
    line[1].color = color;
    line[0].position = sf::Vector2f(x,y);
    line[1].position = sf::Vector2f(x2,y2);

    mWindow.draw(line);
}
