#ifndef BODY_H
#define BODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <vector>

typedef enum eFilterCategory {
    FilterNormal    = 0x00000001,
    FilterObjects   = 0x00000002,
    FilterEffects   = 0x00000004,
    FilterWalls     = 0x00000008,
    FilterPlayer    = 0x00000010,
    FilterShots     = 0x000000020,
    FilterEnemy     = 0x000000040,
    FilterFlag     = 0x000000080
} FilterCategory;

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
        b2PolygonShape *getBodyShape();
        b2FixtureDef* getBodyFixture();

        virtual void startContact(Body * body, b2Contact *contact);
        virtual void endContact(Body * body, b2Contact *contact);
        virtual void preSolve(Body * body, b2Contact *contact, const b2Manifold *manifold);
        virtual void postSolve(Body * body, b2Contact* contact, const b2ContactImpulse* impulse);
        b2PolygonShape m_bodyShape;
        b2CircleShape  m_bodyCircleShape;

        int type = 0;
        string name = "";

        bool isDelete = false;
    protected:
        b2Body* m_body;
        b2BodyDef m_bodyDef;
        b2FixtureDef m_fixtureDef;
};

#endif // BODY_H
