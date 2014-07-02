#include "Spawner.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Character.h"
#include "Engine.h"

Spawner::Spawner(b2World *world, float x, float y, bool spawning)
{
    this->type = 1;
    this->name = "spawner";
    this->clock.restart();

    this->setTexture(TextureManager::TextureControl.get("spawn"), 32, 32, 1, 200);

    this->getSprite()->setScale(4, 4);
    this->getBodyDef()->position.Set(x, y);
    ((b2PolygonShape*)this->getBodyShape() )->SetAsBox(35.0f/pixelsPerMeter,32.0f/pixelsPerMeter);

    this->createBody(*world);
    this->getBody()->SetUserData(this);

    this->is_spawning = spawning;

}

void Spawner::update(float dt)
{
    Entity::update(dt);

    if(is_spawning == false) return;

    if(this->clock.getElapsedTime().asSeconds() > this->creationPeriod)
    {
        this->m_animation.setFrames(0, 2, 400);
        Engine::bodylist.push_back(createSoldier("weak_orc"));
        this->clock.restart();
    }
    if(m_animation.isReady())
    {
        this->m_animation.setFrames(0, 1, 200);
    }

}

void Spawner::setSpawning(bool spawning)
{
    is_spawning = spawning;
}

bool Spawner::isSpawning()
{
    return is_spawning;
}

Character* Spawner::createSoldier(string type)
{
    if(type == "weak_orc")
    {
        return new Character(this->getBody()->GetWorld(), this->getBodyDef()->position.x - 35.0/pixelsPerMeter, this->getBodyDef()->position.y);
    }

    return nullptr;
}

