#include "Body.h"

Body::Body()
{
    //ctor
    m_bodyShape = new b2PolygonShape();
}

Body::~Body()
{
    //dtor
    if(m_bodyShape != nullptr)
        delete m_bodyShape;
}

void Body::createBody(b2World & world)
{
    m_body = world.CreateBody(&m_bodyDef);
    m_bodyFix.shape = m_bodyShape;
    b2Fixture* fix = m_body->CreateFixture(&m_bodyFix);
    m_fixture.push_back(fix);
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

b2Fixture *Body::getFixture(int id)
{
    return m_fixture[id];
}
b2BodyDef* Body::getBodyDef()
{
    return &m_bodyDef;
}
b2Shape* Body::getBodyShape()
{
    return m_bodyShape;
}
b2FixtureDef* Body::getBodyFixture()
{
    return &m_bodyFix;
}

void Body::startContact(Body * body)
{
}

void Body::endContact(Body * body)
{
}
