#include "Character.h"
#include "Engine.h"
#include "Globals.h"
#include "TextureManager.h"
#include "PlayerEntity.h"
#include "Effects.h"
#include "Shot.h"
#include <sstream>

Character::Character()
{
    //ctor
    name = "enemy";
    this->atk = 10;
    this->HP = this->maxHP = 20;

    this->getBodyFixture()->filter.maskBits = FilterShots | FilterWalls | FilterNormal | FilterEnemy | FilterPlayer;
    this->getBodyFixture()->filter.categoryBits= FilterEnemy;
}

Character::Character(b2World *world, float x, float y)
    : Character::Character()
{
    this->setTexture(TextureManager::TextureControl.get("weak_orc"), 64, 64, 7, 200);
    this->m_animation.setFrames(9, 9, 200);

    this->getSprite()->setOrigin(23,20);
    ((b2PolygonShape*)this->getBodyShape())->SetAsBox(12.0f/pixelsPerMeter,18.0f/pixelsPerMeter, b2Vec2(0, 9.0f/pixelsPerMeter), 0.0);
    this->getBodyDef()->position.Set(x, y);
    this->getBodyDef()->type = b2_dynamicBody;
    this->getBodyFixture()->density = 0.2f;
    this->createBody(*world);
    this->getBody()->SetFixedRotation(true);
    this->getBody()->SetUserData(this);

    this->atk = 10;
}

Character::~Character()
{
    //dtor
}

