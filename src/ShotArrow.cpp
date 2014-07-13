#include "ShotArrow.h"

#include "TextureManager.h"
#include "Engine.h"
#include "Globals.h"
#include "math.h"
#include "Spawner.h"
#include "Effects.h"
#include <sstream>
ShotArrow::ShotArrow(int id, float px, float py, b2Vec2 force)
{
    name = "shot";
    type = id;

    this->getBodyFixture()->filter.maskBits = FilterShots | FilterWalls | FilterNormal | FilterEnemy | FilterObjects;
    this->getBodyFixture()->filter.categoryBits= FilterShots;

    this->setTexture(TextureManager::TextureControl.get("arrow_shot"), 32, 16);
    this->getSprite()->setOrigin(16,8);
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
        Body* b = (Body*)m_collisionToMakeSticky.targetBody->GetUserData();
        if(b->name == "sprite" || m_body->GetJointList() == nullptr){
            if(isDelete == false){
                isDelete = true;
                m_animation.setFrames(1, 4, 70, true);
                m_animation.forceFrame(0);
                isActive = glued = false;
            }
        }
    }

    if(glued){
        Body* b = (Body*)m_collisionToMakeSticky.targetBody->GetUserData();
        if(m_body->GetJointList() == nullptr || b->isDelete) {
            if(isActive)
            {
                b2Filter filter;
                filter.maskBits = FilterWalls | FilterNormal | FilterObjects;
                filter.categoryBits= FilterShots;
                m_body->GetFixtureList()->SetFilterData(filter);
                m_body->GetFixtureList()->SetDensity(0.5);
                m_body->ResetMassData();
                isActive = false;
            }
        }
        SpriteBody::update(dt);
        return;
    }

    //Animação de morte
    if(isDelete)
    {
        m_animation.getSprite().setRotation( default_rotation + 180.f*m_body->GetAngle()/(M_PI) );
        m_animation.getSprite().setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
        m_animation.update(dt);
        if(m_animation.isReady()){
            SpriteBody::update(dt);
        }
        return;
    }

    //Junta corpos
    if(m_collisionToMakeSticky.active)
    {
        glued = true;
        Body* b = (Body*) m_collisionToMakeSticky.targetBody->GetUserData();
        if(b->isDelete){ // Evita criar juntas em corpos destroidos
//            isDelete = true;
//            m_animation.setFrames(1, 4, 70, true);
//            m_animation.forceFrame(0);
            isActive = false;
//            glued = false;
            return;
        }
        b2Vec2 worldCoordsAnchorPoint = m_collisionToMakeSticky.arrowBody->GetWorldPoint( b2Vec2(0.6f, 0) );

        b2WeldJointDef weldJointDef;
        weldJointDef.bodyA = m_collisionToMakeSticky.targetBody;
        weldJointDef.bodyB = m_collisionToMakeSticky.arrowBody;
        weldJointDef.localAnchorA = weldJointDef.bodyA->GetLocalPoint( worldCoordsAnchorPoint );
        weldJointDef.localAnchorB = weldJointDef.bodyB->GetLocalPoint( worldCoordsAnchorPoint );
        weldJointDef.referenceAngle = weldJointDef.bodyB->GetAngle() - weldJointDef.bodyA->GetAngle();
        m_collisionToMakeSticky.joint = m_body->GetWorld()->CreateJoint( &weldJointDef );

        m_body->GetFixtureList()->SetDensity(0.001);
        m_body->ResetMassData();

        b2Filter noCol; noCol.categoryBits = 0; noCol.maskBits = 0;
        this->m_body->GetFixtureList()->SetFilterData(noCol);
        return;
    }


    b2Vec2 flightDirection = m_body->GetLinearVelocity();

    if(hasCollided == false )
    {
        m_body->SetTransform(m_body->GetPosition(), atan2(flightDirection.y, flightDirection.x) );
    }
//    else
//    {
//        float flightSpeed = flightDirection.Normalize();
//        b2Vec2 pointingDirection = m_body->GetWorldVector( b2Vec2( -1, 0 ) );
//        float dot = b2Dot( flightDirection, pointingDirection );

//        float dragConstant = 0.5f;
//        float dragForceMag = (1 - fabs(dot) ) * flightSpeed * flightSpeed * dragConstant * m_body->GetMass();

//        b2Vec2 arrowTailPosition = m_body->GetWorldPoint( b2Vec2( -0.4f, 0 ) );
//        m_body->ApplyForce( dragForceMag * -flightDirection, arrowTailPosition, true );
//     }

    SpriteBody::update(dt);
}

void ShotArrow::startContact(Body *body, b2Contact *contact)
{
    Shot::startContact(body, contact);
    hasCollided = true;
}

void ShotArrow::postSolve(Body *body, b2Contact *, const b2ContactImpulse *)
{
    if(glued || !isActive) return;

    m_collisionToMakeSticky.arrowBody = this->m_body;
    m_collisionToMakeSticky.targetBody = body->getBody();
    m_collisionToMakeSticky.active = true;
}
