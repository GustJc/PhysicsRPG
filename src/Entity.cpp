#include "Entity.h"
#include "Effects.h"
#include "Engine.h"
#include "Globals.h"

Entity::Entity()
{
    //ctor
    is_dead = false;
    this->HP = this->maxHP = 1;
}

Entity::~Entity()
{
    //dtor
}

int Entity::damage(int attack)
{
    int dano = attack;
    int random = rand() % int(def+1);

    dano -= random;

    if(dano > 0){
        hpTimer.restart();
        HP -= dano;
        if(HP <= 0){
            die();
            isDelete = true;
        }
        return dano;
    }

    return 0;

}

void Entity::render(sf::RenderWindow &window)
{
    SpriteBody::render(window);

    if(showHP && hpTimer.getElapsedTime().asSeconds() < hpDelay)
    {
        renderHP();
    }
}

void Entity::die()
{
    is_dead = true;
}

bool Entity::isDead()
{
    return is_dead;
}

void Entity::renderHP()
{

    int startX = m_animation.getSprite().getPosition().x - m_animation.getSprite().getTextureRect().width/2.f;
    int startY = m_animation.getSprite().getPosition().y - 10 - m_animation.getSprite().getTextureRect().height/2.f;
    int width  = m_animation.getSprite().getTextureRect().width;
    int height = 4;

    float percent = (float)this->HP / (float)this->maxHP;

    Engine::EngineControl.drawRectVertex(startX, startY,
                           width*percent, height, sf::Color(255,0,0,100) );

    Engine::EngineControl.drawLine(startX         , startY        , startX+width      , startY, sf::Color::Black);
    Engine::EngineControl.drawLine(startX+width   , startY+height , startX            , startY+height, sf::Color::Black);
    Engine::EngineControl.drawLine(startX+width   , startY+height , startX+width      , startY, sf::Color::Black);
    Engine::EngineControl.drawLine(startX         , startY+height , startX            , startY       , sf::Color::Black);
}
