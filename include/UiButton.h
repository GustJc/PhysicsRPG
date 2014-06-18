#ifndef UIBUTTON_H
#define UIBUTTON_H

#include <SFML/Graphics.hpp>

class UiButton
{
public:
    UiButton();
    UiButton(sf::Vector2i size, sf::Texture& texture);

    void setup(sf::Vector2i size, sf::Texture& texture);

    void setPosition(float px, float py);
    void render(sf::RenderWindow& window);
    bool isOver(sf::Vector2i mouse);
    void update(sf::Vector2i mouse);

private:
    sf::Sprite image;
    int width;
    int height;
    int state = 1;
};

#endif // UIBUTTON_H
