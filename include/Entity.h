#ifndef ENTITY_H
#define ENTITY_H

#include "SpriteBody.h"

class Entity : public SpriteBody
{
    public:
        Entity();
        virtual ~Entity();

        virtual int damage(int attack);

        void die();

        bool isDead();
    protected:
        bool is_dead;

        int HP = 1, maxHP = 1;
        int atk = 1, def = 0;
        float speed = 2;
    private:
};

#endif // ENTITY_H
