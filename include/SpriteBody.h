#ifndef SPRITEBODY_H
#define SPRITEBODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

#include "Body.h"
#include "Animation.h"

class SpriteBody : public Body
{
    public:
        SpriteBody(int id = 0, int px = 0, int py = 0);
        virtual ~SpriteBody();

        virtual void update(float dt = 0);
        virtual void render(sf::RenderWindow& window);

        void setTexture(sf::Texture& texture, int sizeW = -1, int sizeH = -1, int frames = 1, int msTime =0 );
        sf::Sprite* getSprite();
        void setDefaultRotation(float rotationgraus);
        void setFixedSpritePosition(int posX, int posY);

        void removeFromList(vector<Body*>& list);

        Animation m_animation;
protected:
        float default_rotation = 0.0f;
    private:
};

#endif // SPRITEBODY_H
