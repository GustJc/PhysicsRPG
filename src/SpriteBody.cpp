#include "SpriteBody.h"
#include "Globals.h"
SpriteBody::SpriteBody()
{
    //ctor
}

SpriteBody::~SpriteBody()
{
    //dtor
}
void SpriteBody::update(float dt)
{
    m_animation.getSprite().setRotation( default_rotation + 180.f*m_body->GetAngle()/(M_PI) );
    m_animation.getSprite().setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
    m_animation.update(dt);

    //m_sprite.setRotation( 180.f*m_body->GetAngle()/(M_PI) );
    //m_sprite.setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);


}

void SpriteBody::render(sf::RenderWindow& window)
{
    //window.draw(m_sprite);
    m_animation.render(window);
}

void SpriteBody::setTexture(sf::Texture& texture, int sizeW, int sizeH, int frames, int msTime )
{
    m_sprite.setTexture(texture);

    if(sizeW <= 0)
        sizeW = texture.getSize().x;
    if(sizeH <= 0)
        sizeH = texture.getSize().y;

    m_animation.setAnimation(texture, sizeW, sizeH, frames, msTime);
    m_animation.getSprite().setOrigin(sizeW/2, sizeH/2);
}

sf::Sprite* SpriteBody::getSprite()
{
    return &m_sprite;
}

void SpriteBody::setDefaultRotation(float rotationgraus)
{
    default_rotation = rotationgraus;
}
