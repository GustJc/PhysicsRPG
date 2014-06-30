#ifndef EFFECTS_H
#define EFFECTS_H

#include "SpriteBody.h"
#include "Box2D/Box2D.h"
class SplashAnimation : public SpriteBody
{
public:
    SplashAnimation(sf::Texture& texture, sf::Vector2i clip, b2Vec2 pos, int frames=1, int msTime=0, sf::Vector2f scale = sf::Vector2f(1.0, 1.0), bool onlyOnce = true, bool active = false);
    virtual ~SplashAnimation();

    virtual void update(float dt = 0);
    b2Vec2 inicialImpulse = b2Vec2(0,0);

private:
    bool isCreated = false;
};

class SplashText : public SpriteBody
{
public:
    SplashText(string text, b2Vec2 pos, sf::Color color, int size, int msTime);
    virtual ~SplashText();

    virtual void update(float dt = 0);
    virtual void render(sf::RenderWindow &window);
    void preSolve(Body *body, b2Contact *contact, const b2Manifold *manifold);
    b2Vec2 inicialImpulse = b2Vec2(0,0);
private:
    bool isCreated = false;
    sf::Text mText;
    sf::Clock mClock;
    int mTimer = 0;
};

#endif // EFFECTS_H
