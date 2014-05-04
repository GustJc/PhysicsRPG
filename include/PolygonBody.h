#ifndef POLYGONBODY_H
#define POLYGONBODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
class PolygonBody
{
    public:
        PolygonBody(b2World & world);
        PolygonBody();
        void setWorld(b2World & world);
        sf::Shape& getShape();
        void update();

        virtual ~PolygonBody();
    protected:
        b2Body* m_body;
        b2BodyDef m_bodyDef;
        b2PolygonShape m_bodyShape;
        b2FixtureDef m_bodyFix;
        //SFML rect shape
        sf::RectangleShape m_shape;
    private:
};

#endif // POLYGONBODY_H
