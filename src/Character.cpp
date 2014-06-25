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
        m_animation.setFrames(0, 3, 200);
        moveLeft();
    }
    else
    if( m_timer.getElapsedTime().asSeconds() > 2.f )
    {
        m_animation.setFrames(1, 3, 200);
        moveRight();
        if(m_timer.getElapsedTime().asSeconds() > 2.f*2){
            m_animation.setFrames(0, 3, 200);
            m_timer.restart();
        }
    }else
    if( m_timer.getElapsedTime().asSeconds() < 2.f )
    {
        moveLeft();
    }
}

void Character::moveLeft()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Min( vel.x - 0.1f, -2.0f );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;

    //this->m_body->ApplyForceToCenter( b2Vec2(-0.3/pixelsPerMeter, 0 ), true );
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
    //this->m_body->SetLinearVelocity( b2Vec2(-50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}

void Character::moveRight()
{
    b2Vec2 vel = m_body->GetLinearVelocity();
    float desiredVel = b2Max( vel.x + 0.1f,  2.0f );
    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;
    this->m_body->ApplyLinearImpulse(b2Vec2(impulse/pixelsPerMeter, 0 ), m_body->GetWorldCenter(), true );
    //this->m_body->ApplyForceToCenter( b2Vec2(0.3/pixelsPerMeter, 0 ), true );
    //this->m_body->SetLinearVelocity( b2Vec2(50/pixelsPerMeter, this->m_body->GetLinearVelocity().y ) );
}
