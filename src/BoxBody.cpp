#include "BoxBody.h"
#include "Globals.h"
#include <math.h>
BoxBody::BoxBody(b2World & world)
{
    m_shape = sf::RectangleShape(sf::Vector2f(20,20));
	m_shape.setOrigin(10,10);
	m_shape.setFillColor(sf::Color(255, 0, 255, 255));
    m_bodyDef.position.Set(300.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    m_bodyDef.type = b2_dynamicBody;
    //Box eh metade, entao 20x20
    m_bodyShape.SetAsBox(10.0f/pixelsPerMeter,10.0f/pixelsPerMeter);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.3f;
    m_bodyFix.friction = 0.5f;
    m_bodyFix.restitution = 0.1f;
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

//Cria um corpo sem coloca-lo no mundo, fixture nao ligada
BoxBody::BoxBody()
{
    m_shape = sf::RectangleShape(sf::Vector2f(10.f,10.f));
    m_shape.setOrigin(5,5);
	m_shape.setFillColor( sf::Color(120, 59, 25) );
    m_bodyDef.position.Set(300.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    m_bodyDef.type = b2_dynamicBody;
    m_bodyShape.SetAsBox(5.0f/pixelsPerMeter,5.0f/pixelsPerMeter);
    m_bodyFix.shape = &m_bodyShape;
    m_bodyFix.density = 0.1f;
    m_bodyFix.friction = 0.1f;
}

void BoxBody::setWorld(b2World & world) {
    m_body = world.CreateBody(&m_bodyDef);
    m_body->CreateFixture(&m_bodyFix);
}

b2Body* BoxBody::getBody() {
    return m_body;
}

sf::Shape & BoxBody::getShape() {
    return m_shape;
}

void BoxBody::update() {
    m_shape.setRotation( 180.f*m_body->GetAngle()/(M_PI) );
    m_shape.setPosition( m_body->GetPosition().x*pixelsPerMeter, m_body->GetPosition().y*pixelsPerMeter);
}

void BoxBody::destroyBody(b2World & world)
{
    m_body->DestroyFixture(m_body->GetFixtureList());
	world.DestroyBody(m_body);
}


BoxBody::~BoxBody()
{
    //dtor
}

