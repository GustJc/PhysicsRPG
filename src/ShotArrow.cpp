#include "ShotArrow.h"

#include "TextureManager.h"
#include "Engine.h"
#include "Globals.h"
#include "math.h"
ShotArrow::ShotArrow(int id, float px, float py, b2Vec2 force)
{
    name = "shot";
    type = id;

    this->getBodyFixture()->filter.maskBits = FilterShots | FilterWalls | FilterNormal | FilterEnemy | FilterObjects;
    this->getBodyFixture()->filter.categoryBits= FilterShots;

    this->setTexture(TextureManager::TextureControl.get("arrow_shot"));
    this->getSprite()->setOrigin(16,16);
    this->m_bodyShape.SetAsBox(0.4f, 0.1f);

    this->getBodyDef()->position.Set(
                px,
                py
                );
    this->getBodyDef()->type = b2_dynamicBody;
    this->getBodyDef()->angle = atan2(force.y, force.x);

    this->getBodyFixture()->friction = 0.5f;
    this->getBodyFixture()->restitution = 0.4f;
    this->getBodyFixture()->density = 2.f;

    this->m_bodyDef.fixedRotation = false;
    this->m_bodyDef.angularDamping = 2.5f;

    Engine::bodylist.push_back(this);
}

void ShotArrow::update(float dt)
{
    if(m_body->IsAwake() == false){
        isDelete = true;
    }


    b2Vec2 flightDirection = m_body->GetLinearVelocity();

    if(hasCollided == false )
    {
        m_body->SetTransform(m_body->GetPosition(), atan2(flightDirection.y, flightDirection.x) );
    }
    else
    {
        float flightSpeed = flightDirection.Normalize();
        b2Vec2 pointingDirection = m_body->GetWorldVector( b2Vec2( -1, 0 ) );
        float dot = b2Dot( flightDirection, pointingDirection );

        float dragConstant = 0.5f;
        float dragForceMag = (1 - fabs(dot) ) * flightSpeed * flightSpeed * dragConstant * m_body->GetMass();

        b2Vec2 arrowTailPosition = m_body->GetWorldPoint( b2Vec2( -0.4f, 0 ) );
        m_body->ApplyForce( dragForceMag * -flightDirection, arrowTailPosition, true );
     }

    SpriteBody::update(dt);
}

void ShotArrow::startContact(Body *, b2Contact *)
{
    hasCollided = true;
}
