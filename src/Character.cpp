#include "Character.h"
#include "Engine.h"
#include "Globals.h"
#include "TextureManager.h"

Character::Character()
{
    //ctor
}

Character::Character(b2World *world, float x, float y)
{
    this->setTexture(TextureManager::TextureControl.get("slime"), 46, 27,3,200);

    this->getSprite()->setOrigin(23,20);
    ((b2PolygonShape*)this->getBodyShape())->SetAsBox(23.0f/pixelsPerMeter,13.0f/pixelsPerMeter);
    this->getBodyDef()->position.Set(x, y);
    this->getBodyDef()->type = b2_dynamicBody;
    this->getBodyFixture()->density = 0.2f;
    this->createBody(*world);
    this->getBody()->SetFixedRotation(true);
    this->getBody()->SetUserData(this);

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

void Character::postSolve(Body * body, b2Contact* contact, const b2ContactImpulse* impulse)
{
    if(body == nullptr) return;

    if(name == "shot")
    {
        cout << "IMP"<<endl;
    }
    else if(body && body->name == "shot")
    {
        float vy = -0.8*body->getBody()->GetMass()*body->getBody()->GetLinearVelocity().Length();
        body->getBody()->ApplyLinearImpulse(b2Vec2(0, vy),body->getBody()->GetWorldCenter(),  true);

        float attack = 10*impulse->normalImpulses[0];
        cout << "Normal: " << attack << endl;
    }
}

bool Character::preSolve(Body * body, b2Contact *contact, const b2Manifold *manifold)
{
    return true;
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
