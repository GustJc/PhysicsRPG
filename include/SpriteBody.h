#ifndef SPRITEBODY_H
#define SPRITEBODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Body.h"
#include "Animation.h"

class SpriteBody : public Body
{
    public:
        SpriteBody();
        virtual ~SpriteBody();

        void update(float dt = 0);
        void render(sf::RenderWindow& window);

        void setTexture(sf::Texture& texture, int sizeW = -1, int sizeH = -1, int frames = 1, int msTime =0 );
        sf::Sprite* getSprite();
        void setDefaultRotation(float rotationgraus);


    protected:
        float default_rotation = 0.0f;
        sf::Sprite m_sprite;
        Animation m_animation;
    private:
};

#endif // SPRITEBODY_H
