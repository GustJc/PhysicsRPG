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

void Character::startContact(Body *body, b2Contact *)
{
    firstImpulse = true;
    if(body->name == "shot")
    {
        if(is_dead) return;

        float vy = -0.8*body->getBody()->GetMass()*body->getBody()->GetLinearVelocity().Length();
        body->getBody()->ApplyLinearImpulse(b2Vec2(0, vy),body->getBody()->GetWorldCenter(),  true);

        Shot* shot= (Shot*)body;
        float attack_multiplier = 0.5 + lastImpulse;
        //cout << "Atk multipler: " << attack_multiplier << endl;
        if(attack_multiplier < 0) attack_multiplier = 0;
        if(attack_multiplier > 2) attack_multiplier = 2;

        int dano = shot->getAtk() * (attack_multiplier);
        this->damage(dano);

        if(this->is_dead){
            //cout << "Dead" << endl;
            this->m_animation.setFrames(20, 5, 550, true);
            SplashText* text = new SplashText("Oh No! x.x", this->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 12, 1000);
            text->inicialImpulse = b2Vec2(-1,1.5);
        }

        stringstream ss; ss << "-" << dano;
        SplashText* text = new SplashText(ss.str(), this->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 20, 1000);
        text->inicialImpulse = b2Vec2(1,1);
    }
}

void Character::endContact(Body *body, b2Contact *)
{
    if(body->name == "player")
    {
        this->m_animation.setFrames(9, 3, 200);
        this->m_animation.forceFrame(0);
    }
}

void Character::postSolve(Body * , b2Contact* , const b2ContactImpulse* impulse)
{    
    if(firstImpulse) {
        lastImpulse = impulse->normalImpulses[0];
        firstImpulse = false;
    }
}

void Character::preSolve(Body *body , b2Contact *, const b2Manifold *)
{
    if(body->name == "player")
    {
        PlayerEntity* player = (PlayerEntity*)body;
        getBody()->SetLinearVelocity(b2Vec2(0,0));

        if(m_timer_attack.getElapsedTime().asSeconds() > m_attack_period)
        {
            m_timer_attack.restart();
            m_animation.setFrames(13, 6, 50, true);
            m_animation.forceFrame(0);
        }

        if(m_animation.isReady()) {
            this->m_animation.setFrames(9, 3, 200);
            this->m_animation.forceFrame(0);
            player->m_animation.setFrames(20, 6, 110, true);
            player->m_animation.forceFrame(0);

            int dano = player->damage(this->atk);
            b2Vec2 point = player->getBody()->GetWorldCenter();
            point.y -= 0.5;
            point.x += 0.5;

            float forceX = -player->getBody()->GetMass();
            float forceY = -player->getBody()->GetMass();

            player->getBody()->ApplyLinearImpulse(b2Vec2(forceX, forceY),
                                                  point, true );
            int backForce = dano;
            if(backForce > 15) backForce = 15;

            player->getBody()->ApplyLinearImpulse(b2Vec2(-backForce*player->getBody()->GetMass(), forceY),
                                                  player->getBody()->GetWorldCenter(), true);

            stringstream ss; ss << "-" << dano;

            SplashText* text = new SplashText(ss.str(), player->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 25, 1000);
            text->inicialImpulse = b2Vec2(1,1);
        }
    }
}

void Character::update(float dt)
{
    m_animation.getSprite().setRotation( default_rotation + 180.f*m_body->GetAngle()/(M_PI) );
    m_animation.getSprite().setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
    m_animation.update(dt);

    if(isDelete)
    {
        if(this->m_animation.isReady())
        {
            int gold = 1;
            PlayerEntity::PlayerControl->gold += gold;
            stringstream ss; ss << "+" << gold;
            SplashText* text = new SplashText(ss.str(), this->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Yellow, 22, 800);
            text->inicialImpulse = b2Vec2(-0.5, 1.5);

            destroyBody(*Engine::world);
            removeFromList(Engine::bodylist);
            removeFromList(Engine::effectslist);
        }
    }

    if(this->is_dead)
    {
        m_body->SetActive(false);
    }

    if(isDead() == false)
        onAI();
}

void Character::onAI()
{
    moveLeft();
}

void Character::moveLeft()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Min( vel.x - float(speed*0.5f), -float(speed) );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
}

void Character::moveRight()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Max( vel.x + float(speed*0.5f),  float(speed) );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
}
