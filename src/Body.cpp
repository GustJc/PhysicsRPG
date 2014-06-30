#include "Body.h"
#include "Globals.h"
Body::Body()
{
    m_bodyDef.userData = this;
}

Body::~Body()
{
}

void Body::createBody(b2World & world, bool isCircle)
{
    cout << "Create" << endl;
    m_body = world.CreateBody(&m_bodyDef);
    if(isCircle)
        m_fixtureDef.shape = &m_bodyCircleShape;
   else
        m_fixtureDef.shape = &m_bodyShape;

    m_body->CreateFixture(&m_fixtureDef);
}

void Body::destroyBody(b2World & world)
{
    cout << "Body Destroyed" << endl;
    m_body->DestroyFixture(m_body->GetFixtureList());
    world.DestroyBody(m_body);
}

b2Body* Body::getBody()
{
    return m_body;
}

b2Fixture *Body::getFixture()
{
    return m_body->GetFixtureList();
}
b2BodyDef* Body::getBodyDef()
{
    return &m_bodyDef;
}
b2Shape* Body::getBodyShape()
{
    return &m_bodyShape;
}
b2FixtureDef* Body::getBodyFixture()
{
    return &m_fixtureDef;
}

void Body::startContact(Body * , b2Contact *)
{
}

void Body::endContact(Body * , b2Contact *)
{
}

void Body::preSolve(Body *, b2Contact* , const b2Manifold *)
{

}

void Body::postSolve(Body *, b2Contact *, const b2ContactImpulse *)
{

}
