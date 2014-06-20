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

        void createBody(b2World & world);

        virtual void update(float dt = 0) = 0;
        virtual void render(sf::RenderWindow& window) = 0;

        void destroyBody(b2World & world);

        b2Body* getBody();
        b2Fixture *getFixture(int id = 0);
        b2BodyDef* getBodyDef();
        b2Shape* getBodyShape();
        b2FixtureDef* getBodyFixture();

        virtual void startContact(Body * body);
        virtual void endContact(Body * body);
        b2Shape* m_bodyShape = nullptr;
    protected:
        b2Body* m_body;
        vector<b2Fixture*> m_fixture;
        b2BodyDef m_bodyDef;
        b2FixtureDef m_bodyFix;
};

#endif // BODY_H
