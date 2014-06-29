#include "Character.h"
#include "Engine.h"
#include "Globals.h"
#include "TextureManager.h"
#include "PlayerEntity.h"
#include "Effects.h"
#include <sstream>

Character::Character()
{
    //ctor
    name = "enemy";
    this->atk = 10;
}

Character::Character(b2World *world, float x, float y)
{
    name = "enemy";
    this->setTexture(TextureManager::TextureControl.get("slime"), 46, 27,3,200);

    this->getSprite()->setOrigin(23,20);
    ((b2PolygonShape*)this->getBodyShape())->SetAsBox(23.0f/pixelsPerMeter,13.0f/pixelsPerMeter);
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

void Character::postSolve(Body * body, b2Contact* , const b2ContactImpulse* impulse)
{
    if(body == nullptr) return;

    if(name == "shot")
    {
        cout << "IMP"<<endl;
    }
    else if(body->name == "shot")
    {
        float vy = -0.8*body->getBody()->GetMass()*body->getBody()->GetLinearVelocity().Length();
        body->getBody()->ApplyLinearImpulse(b2Vec2(0, vy),body->getBody()->GetWorldCenter(),  true);

        float attack = 10*impulse->normalImpulses[0];
        cout << "Normal: " << attack << endl;

        int dano = 2;
        this->damage(2);
        stringstream ss; ss << "-" << dano;
        SplashText* text = new SplashText(ss.str(), this->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 25, 1000);
        text->inicialImpulse = b2Vec2(1,1);
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
            m_animation.setFrames(0, 3, 200, true);
            m_animation.forceFrame(0);
        }

        if(m_animation.isReady()) {
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

            player->getBody()->ApplyLinearImpulse(b2Vec2(-backForce*player->getBody()->GetMass(), 0),
                                                  player->getBody()->GetWorldCenter(), true );

            stringstream ss; ss << "-" << dano;

            SplashText* text = new SplashText(ss.str(), player->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 25, 1000);
            text->inicialImpulse = b2Vec2(1,1);
        }

    }
}

void Character::update(float dt)
{
    Entity::update(dt);

    if(isDead() == false)
        onAI();
}

void Character::onAI()
{
    moveLeft();
//    if( m_timer_attack.getElapsedTime().asSeconds() > 5.f )
//    {
//        m_animation.setFrames(0, 3, 200);
//        moveLeft();
//    }
//    else
//    if( m_timer.getElapsedTime().asSeconds() > 2.f )
//    {
//        m_animation.setFrames(1, 3, 200);
//        moveRight();
//        if(m_timer.getElapsedTime().asSeconds() > 2.f*2){
//            m_animation.setFrames(0, 3, 200);
//            m_timer.restart();
//        }
//    }else
//    if( m_timer.getElapsedTime().asSeconds() < 2.f )
//    {
//        moveLeft();
//    }
}

void Character::moveLeft()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Min( vel.x - float(speed*0.5f), -float(speed) );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;

    //this->m_body->ApplyForceToCenter( b2Vec2(-0.3/pixelsPerMeter, 0 ), true );
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
    //this->m_body->SetLinearVelocity( b2Vec2(-50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}

void Character::moveRight()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Max( vel.x + float(speed*0.5f),  float(speed) );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
    //this->m_body->ApplyForceToCenter( b2Vec2(0.3/pixelsPerMeter, 0 ), true );
    //this->m_body->SetLinearVelocity( b2Vec2(50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}
