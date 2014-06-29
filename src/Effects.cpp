#include "Effects.h"
#include "Engine.h"
SplashAnimation::SplashAnimation(sf::Texture &texture, sf::Vector2i clip, b2Vec2 pos, int frames, int msTime, sf::Vector2f scale, bool onlyOnce)
{
    this->setTexture(texture, clip.x, clip.y, frames, msTime);
    this->m_bodyDef.active = false;
    this->m_bodyDef.type = b2_dynamicBody;
    this->m_bodyShape.SetAsBox(0.8,0.8);
    this->m_bodyDef.position = pos;
    this->createBody(*Engine::world);
    this->m_animation.setFrames(0, frames, msTime, onlyOnce);

    m_animation.getSprite().setScale(scale );

    Engine::effectslist.push_back(this);
}

SplashAnimation::~SplashAnimation()
{

}

void SplashAnimation::update(float dt)
{
    SpriteBody::update(dt);

    if(m_animation.isReady()) {
        this->destroyBody(*Engine::world);
        removeFromList(Engine::effectslist);
    }
}
