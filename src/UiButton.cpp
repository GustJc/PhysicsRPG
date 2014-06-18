#include "UiButton.h"

UiButton::UiButton()
{

}

UiButton::UiButton(sf::Vector2i size, sf::Texture &texture)
{
    setup(size, texture);
}

void UiButton::setup(sf::Vector2i size, sf::Texture &texture)
{
    width = size.x;
    height = size.y;
    state = 1;

    image.setTexture(texture);
    image.setTextureRect(sf::IntRect(width,0, width, height));
}

void UiButton::setPosition(float px, float py)
{
    image.setPosition(sf::Vector2f(px, py) );
}

void UiButton::render(sf::RenderWindow &window)
{
    window.draw(image);
}

bool UiButton::isOver(sf::Vector2i mouse)
{
    if(mouse.x < image.getPosition().x)
        return false;
    if(mouse.y > image.getPosition().y + image.getTextureRect().height)
        return false;
    if(mouse.x > image.getPosition().x + image.getTextureRect().width)
        return false;
    if(mouse.y < image.getPosition().y)
        return false;

    return true;
}

void UiButton::update(sf::Vector2i mouse)
{
    if(isOver(mouse) ) {
        if(state == 1)
        {
            image.setTextureRect( sf::IntRect(0, 0, width, height  ) );
            state = 2;
        }
    }
    else if(state == 2)
    {
        image.setTextureRect( sf::IntRect(width, 0, width, height  ) );
        state = 1;
    }
}
