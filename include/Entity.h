#ifndef ENTITY_H
#define ENTITY_H

#include "SpriteBody.h"

class Entity : public SpriteBody
{
    public:
        Entity();
        virtual ~Entity();

        virtual int damage(int attack);

        virtual void render(sf::RenderWindow &window);

        void die();

        bool isDead();
    protected:
        void renderHP();

    protected:
        bool is_dead;

        int HP = 1, maxHP = 1;
        int atk = 1, def = 0;
        float speed = 2;

        bool showHP = true;
        float hpDelay = 3;
        sf::Clock hpTimer;

    private:
};

#endif // ENTITY_H
