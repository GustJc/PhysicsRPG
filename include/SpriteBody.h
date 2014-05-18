#ifndef SPRITEBODY_H
#define SPRITEBODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Body.h"

class SpriteBody : public Body
{
    public:
        SpriteBody();
        SpriteBody(sf::Sprite sprite);
        virtual ~SpriteBody();

        void update(float dt = 0);
        void render(sf::RenderWindow& window);

        void setTexture(sf::Texture& texture);
        sf::Sprite* getSprite();

    protected:
        sf::Sprite m_sprite;
    private:
};

#endif // SPRITEBODY_H
