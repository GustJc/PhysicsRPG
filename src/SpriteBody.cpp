#include "SpriteBody.h"
#include "Globals.h"
#include "Engine.h"
#include "TextureManager.h"
SpriteBody::SpriteBody(int id, int px, int py)
{
    name = "sprite";
    type = id;

    if(id == 1)
    {
        setTexture(TextureManager::TextureControl.get("tileset"), 16,16);
        setFixedSpritePosition(16*7, 16);
        getSprite()->setOrigin(8,8);
        m_bodyShape.SetAsBox(7.8f/pixelsPerMeter,7.8f/pixelsPerMeter);
        m_bodyDef.position.Set(px, py);
        m_bodyDef.type = b2_dynamicBody;
        m_fixtureDef.friction = 0.5f;
        m_fixtureDef.density = 0.1f;
    }

}

SpriteBody::~SpriteBody()
{
    //dtor
}
void SpriteBody::update(float dt)
{
    if(isDelete){
        destroyBody(*Engine::world);
        removeFromList(Engine::bodylist);
        removeFromList(Engine::effectslist);

        return;
    }
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
    if(sizeW <= 0)
        sizeW = texture.getSize().x;
    if(sizeH <= 0)
        sizeH = texture.getSize().y;

    m_animation.setAnimation(texture, sizeW, sizeH, frames, msTime);
    m_animation.getSprite().setOrigin(sizeW/2, sizeH/2);
}

void SpriteBody::setFixedSpritePosition(int posX, int posY)
{
    m_animation.setFixed(posX, posY);
}

void SpriteBody::removeFromList(vector<Body *> &list)
{
    for(unsigned int i = 0; i < list.size(); i++){
        if(list[i] == this){
            delete list[i];
            list.erase(list.begin()+i);
        }
    }
}

sf::Sprite* SpriteBody::getSprite()
{
    return &m_animation.getSprite();
}

void SpriteBody::setDefaultRotation(float rotationgraus)
{
    default_rotation = rotationgraus;
}
