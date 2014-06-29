#ifndef EFFECTS_H
#define EFFECTS_H

#include "SpriteBody.h"

class SplashAnimation : SpriteBody
{
public:
    SplashAnimation(sf::Texture& texture, sf::Vector2i clip, b2Vec2 pos, int frames=1, int msTime=0, sf::Vector2f scale = sf::Vector2f(1.0, 1.0), bool onlyOnce = true);
    virtual ~SplashAnimation();

    virtual void update(float dt = 0);
};

#endif // EFFECTS_H
