#ifndef BODY_H
#define BODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
/////////////////////////////////////////////////////////////////
/// \brief Classe base para corpos fisicos normais
///
/////////////////////////////////////////////////////////////////
class Body
{
    public:
        Body();
        virtual ~Body();

        void setWorld(b2World & world);

        virtual void update(float dt = 0) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        void destroyBody(b2World & world);

        b2Body* getBody();
        b2BodyDef* getBodyDef();
        b2PolygonShape* getBodyShape();
        b2FixtureDef* getBodyFixture();

        virtual void startContact(Body * body);
        virtual void endContact(Body * body);
    protected:
        b2Body* m_body;
        b2BodyDef m_bodyDef;
        b2PolygonShape m_bodyShape;
        b2FixtureDef m_bodyFix;
};

#endif // BODY_H
