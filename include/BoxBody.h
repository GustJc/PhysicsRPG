#ifndef BOXBODY_H
#define BOXBODY_H

#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>

class BoxBody
{
    public:
        BoxBody(b2World & world);
        BoxBody();
        virtual ~BoxBody();
        void setWorld(b2World & world);
        b2Body* getBody();
        sf::Shape& getShape();
        void update();
        void destroyBody(b2World & world);
    //protected:
        b2Body* m_body;
        b2BodyDef m_bodyDef;
        b2PolygonShape m_bodyShape;
        b2FixtureDef m_bodyFix;
        //SFML rect shape
        sf::RectangleShape m_shape;
};

#endif // BOXBODY_H
