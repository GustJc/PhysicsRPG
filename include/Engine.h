#pragma once

#include <SFML/Graphics.hpp>

class Engine
{
    public:
        Engine();
        virtual ~Engine();

        static Engine EngineControl;

        sf::RenderWindow& getWindowReference();
        sf::Font& getFont();
        sf::View& getViewGame();

        bool isEventsPaused();
        void setEventsPaused(bool pause = true);

        void drawRectVertex(int x, int y, int w, int h, sf::Color color = sf::Color::Black);
        void drawLine(int x, int y, int x2, int y2, sf::Color color = sf::Color::Black);

    protected:
        bool mEventsPaused;
    private:
        sf::RenderWindow mWindow;
        sf::Font mFont;
        sf::View mViewGame;
};

