#ifndef BODY_H
#define BODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>
using namespace std;
/////////////////////////////////////////////////////////////////
/// \brief Classe base para corpos fisicos normais
///
/////////////////////////////////////////////////////////////////
class Body
{
    public:
        Body();
        virtual ~Body();

        virtual void createBody(b2World & world, bool isCircle = false);

        virtual void update(float dt = 0) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        void destroyBody(b2World & world);

        b2Body* getBody();
        b2Fixture *getFixture();
        b2BodyDef* getBodyDef();
        b2Shape* getBodyShape();
        b2FixtureDef* getBodyFixture();

        virtual void startContact(Body * body);
        virtual void endContact(Body * body);
        b2PolygonShape m_bodyShape;
        b2CircleShape  m_bodyCircleShape;

        int type = 0;
    protected:
        b2Body* m_body;
        b2BodyDef m_bodyDef;
        b2FixtureDef m_fixtureDef;
};

#endif // BODY_H
