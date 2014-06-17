#include "Character.h"

#include "Globals.h"

Character::Character()
{
    //ctor
}

Character::~Character()
{
    //dtor
}

void Character::startContact(Body * )
{

    if(isDead() == false) {
        m_body->ApplyLinearImpulse( b2Vec2(0, -1/pixelsPerMeter), m_body->GetPosition(), true);
        die();
        cout << "morreu" << endl;
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
    if( m_timer_attack.getElapsedTime().asSeconds() > 15.f )
    {
        moveLeft();
    }
    else
    if( m_timer.getElapsedTime().asSeconds() > 2.f )
    {
        moveRight();
        if(m_timer.getElapsedTime().asSeconds() > 2.f*2)
            m_timer.restart();
    }else
    if( m_timer.getElapsedTime().asSeconds() < 2.f )
    {
        moveLeft();
    }
}

void Character::moveLeft()
{
    this->m_body->ApplyForceToCenter( b2Vec2(-0.3/pixelsPerMeter, 0 ), true );
    //this->m_body->ApplyLinearImpulse(b2Vec2(-2.5/pixelsPerMeter, 0 ), m_body->GetPosition(), true );
    //this->m_body->SetLinearVelocity( b2Vec2(-50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}

void Character::moveRight()
{
    //this->m_body->ApplyLinearImpulse(b2Vec2(+2.5/pixelsPerMeter, 0 ), m_body->GetPosition(), true );
    this->m_body->ApplyForceToCenter( b2Vec2(0.3/pixelsPerMeter, 0 ), true );
    //this->m_body->SetLinearVelocity( b2Vec2(50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}
