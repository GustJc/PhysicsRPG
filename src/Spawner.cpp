#include "Spawner.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Character.h"
#include "Engine.h"

Spawner::Spawner(b2World *world, float x, float y)
{
    this->name = "spawner";
    this->clock.restart();

    this->setTexture(TextureManager::TextureControl.get("spawn"));

    this->getSprite()->setScale(0.25, 0.25);
    this->getBodyDef()->position.Set(x, y);
    ((b2PolygonShape*)this->getBodyShape() )->SetAsBox(35.0f/pixelsPerMeter,35.0f/pixelsPerMeter);

    this->createBody(*world);
    this->getBody()->SetUserData(this);

}

void Spawner::update(float dt)
{
    Entity::update(dt);

    if(this->clock.getElapsedTime().asSeconds() > this->creationPeriod)
    {
        Engine::bodylist.push_back(createSoldier("Knight"));
        this->clock.restart();
    }
}

Character* Spawner::createSoldier(string type)
{
    if(type == "Knight")
    {
        return new Character(this->getBody()->GetWorld(), this->getBodyDef()->position.x - 35.0/pixelsPerMeter, this->getBodyDef()->position.y);
    }

    return nullptr;
}

