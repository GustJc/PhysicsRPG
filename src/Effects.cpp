#include "Effects.h"
#include "Engine.h"
#include "Globals.h"
SplashAnimation::SplashAnimation(sf::Texture &texture, sf::Vector2i clip, b2Vec2 pos, int frames, int msTime, sf::Vector2f scale, bool onlyOnce)
{
    this->setTexture(texture, clip.x, clip.y, frames, msTime);
    this->m_bodyDef.active = false;
    this->m_bodyDef.type = b2_dynamicBody;
    this->m_bodyShape.SetAsBox(0.8,0.8);
    this->m_bodyDef.position = pos;
    this->m_fixtureDef.filter.categoryBits = 2;
    this->m_fixtureDef.filter.maskBits = 2;
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
    if(m_animation.isReady()) {
        isDelete = true;
    }
    SpriteBody::update(dt);
}


SplashText::SplashText(string text, b2Vec2 pos, sf::Color color, int size, int msTime)
{
    mText.setFont(Engine::EngineControl.getFont());
    mText.setString(text);
    mText.setPosition(sf::Vector2f(pos.x, pos.y));
    mText.setCharacterSize(size);
    mText.setColor(color);
    mTimer = msTime;

    pos.x -= (mText.getGlobalBounds().width/2.f)/pixelsPerMeter;
    pos.y -= (mText.getGlobalBounds().height/2.f)/pixelsPerMeter;

    this->m_bodyDef.active = true;
    this->m_bodyDef.gravityScale = -0.5;
    this->m_bodyDef.type = b2_dynamicBody;
    this->m_bodyShape.SetAsBox(0.5,0.3);
    this->m_bodyDef.position = pos;

    this->m_fixtureDef.filter.categoryBits = 2;
    this->m_fixtureDef.filter.maskBits = 2;

    this->createBody(*Engine::world);
    this->m_animation.setFrames(0);

    Engine::effectslist.push_back(this);
    mClock.restart();
}

SplashText::~SplashText()
{

}

// SplashText
void SplashText::update(float dt)
{
    SpriteBody::update(dt);
    mText.setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
    if(mClock.getElapsedTime().asMilliseconds() > mTimer){
        isDelete = true;
    }
}
#include "Globals.h"
void SplashText::render(sf::RenderWindow &window)
{
    window.draw(mText);
}

bool SplashText::preSolve(Body *body, b2Contact *contact, const b2Manifold *manifold)
{
    return false;
}
