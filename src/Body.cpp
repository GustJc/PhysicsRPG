#include "Body.h"

Body::Body()
{
    //ctor
}

Body::~Body()
{
    //dtor
}

void Body::setWorld(b2World & world)
{
    m_body = world.CreateBody(&m_bodyDef);
    m_bodyFix.shape = &m_bodyShape;
    m_body->CreateFixture(&m_bodyFix);
}

void Body::destroyBody(b2World & world)
{
    m_body->DestroyFixture(m_body->GetFixtureList());
	world.DestroyBody(m_body);
}

b2Body* Body::getBody()
{
    return m_body;
}
b2BodyDef* Body::getBodyDef()
{
    return &m_bodyDef;
}
b2PolygonShape* Body::getBodyShape()
{
    return &m_bodyShape;
}
b2FixtureDef* Body::getBodyFixture()
{
    return &m_bodyFix;
}
