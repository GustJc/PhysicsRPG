#include "Shot.h"

#include "TextureManager.h"
#include "Globals.h"
#include "Engine.h"
#include "Spawner.h"
#include "Effects.h"
#include "Entity.h"
#include <sstream>

Shot::Shot(int id, float px, float py, b2Vec2 force, int limit)
{
    name = "shot";
    type = id;

    this->getBodyFixture()->filter.maskBits = FilterShots | FilterWalls | FilterNormal | FilterEnemy | FilterObjects;
    this->getBodyFixture()->filter.categoryBits= FilterShots;

    if(id == 1)
    {
        this->setTexture(TextureManager::TextureControl.get("boulder_8"));
        this->getSprite()->setOrigin(4,4);
        this->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;

        this->getBodyDef()->position.Set(
                    px,
                    py
                    );
        this->getBodyDef()->type = b2_dynamicBody;
        this->getBodyFixture()->friction = 0.5f;
        this->getBodyFixture()->restitution = 0.4f;
        this->getBodyFixture()->density = 2.f;

        this->m_bodyDef.fixedRotation = false;
        this->m_bodyDef.angularDamping = 2.5f;

        Engine::bodylist.push_back(this);
    }
    else if(id == 2)
    {
        this->setTexture(TextureManager::TextureControl.get("boulder_8"));
        this->getSprite()->setOrigin(4,4);
        this->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;

        this->getBodyDef()->position.Set(
                    px-2,
                    0
                    );
        this->getBodyDef()->type = b2_dynamicBody;
        this->getBodyFixture()->friction = 0.5f;
        this->getBodyFixture()->restitution = 0.4f;
        this->getBodyFixture()->density = 2.f;
        this->m_bodyDef.fixedRotation = false;
        this->m_bodyDef.angularDamping = 2.5f;

        if(limit < 8){
            Shot* shot = new Shot(2, px, py, force, limit+1);
            shot->getBodyFixture()->filter.groupIndex = 1;
            shot->createBody(*Engine::world, true);

            force.x *= shot->getBody()->GetMass();
            force.y *= shot->getBody()->GetMass();
            shot->getBody()->ApplyLinearImpulse(force ,shot->getBody()->GetWorldCenter(),true);
        }

        Engine::bodylist.push_back(this);
    }
}

void Shot::update(float dt)
{
    if(m_body->IsAwake() == false){
        isDelete = true;
    }

    SpriteBody::update(dt);
}

void Shot::startContact(Body *body, b2Contact *)
{
    if(!isActive)
        return;

    if(body->name == "spawner")
    {
        Entity* ent = (Entity*) body;
        proccessHitDamage(ent);
        Engine::EngineControl.playSfx("data/music/sfx/explosion.wav");
    }
    else
    if(body->name == "wall")
    {
        Entity* ent = (Entity*) body;
        proccessHitDamage(ent);
        Engine::EngineControl.playSfx("data/music/sfx/explosion.wav");
    }
}

void Shot::proccessHitDamage(Entity *entity)
{
    if(!isActive)
        return;

    int dano = atk;
    entity->damage(dano);
    stringstream ss; ss << "-" << dano;

    SplashText* text = new SplashText(ss.str(), entity->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 25, 1000);
    text->inicialImpulse = b2Vec2(1,1);

    SplashAnimation* sa = new SplashAnimation(TextureManager::TextureControl.get("explosion"), sf::Vector2i(16,16),
                              this->getBody()->GetPosition(), 5, 100, sf::Vector2f(2.0, 2.0));
    sa->inicialImpulse = b2Vec2(0, 0); // To remove waning unused
}

int Shot::getAtk()
{
    return this->atk;
}
