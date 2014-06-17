#ifndef ENTITY_H
#define ENTITY_H

#include "SpriteBody.h"

class Entity : public SpriteBody
{
    public:
        Entity();
        virtual ~Entity();

        virtual void startContact(Body * ) {};
        virtual void endContact(Body * ) {};

        void die();

        bool isDead();
    protected:
        bool is_dead;
    private:
};

#endif // ENTITY_H
