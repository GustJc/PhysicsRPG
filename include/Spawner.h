#ifndef SPAWNER_H
#define SPAWNER_H

#include "Entity.h"
#include "Character.h"

class Spawner : public Entity
{
    public:
        Spawner(b2World *world, float x, float y, bool spawning = true);
        Character* createSoldier(string type);

        void update(float dt = 0);

        void setSpawning(bool spawning);
        bool isSpawning();

    protected:
        sf::Clock clock;
        float creationPeriod = 10.0;
        int HP = 10, maxHP = 10;
        int atk = 0, def = 1;
        int touching_objs=0;
        bool is_spawning = true;
};

#endif // SPAWNER_H
