#include "SpriteBody.h"
#include "Globals.h"
SpriteBody::SpriteBody()
{
    //ctor
}

SpriteBody::SpriteBody(sf::Sprite sprite)
{
    m_sprite = sprite;
    //Seta origin no meio da imagem, somente para imagens unicas
    m_sprite.setOrigin(m_sprite.getTexture()->getSize().x/2.f, m_sprite.getTexture()->getSize().y/2.f );
}

SpriteBody::~SpriteBody()
{
    //dtor
}
void SpriteBody::update(float dt)
{
    m_sprite.setRotation( 180.f*m_body->GetAngle()/(M_PI) );
    m_sprite.setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
}

void SpriteBody::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void SpriteBody::setTexture(sf::Texture& texture)
{
    m_sprite.setTexture(texture);
}

sf::Sprite* SpriteBody::getSprite()
{
    return &m_sprite;
}
