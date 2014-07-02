#ifndef PLAYERENTITY_H
#define PLAYERENTITY_H

#include "Entity.h"

class b2World;

#define KEY_LEFT 1
#define KEY_RIGHT 2
#define KEY_UP 4

class PlayerEntity : public Entity
{
public:
    PlayerEntity(b2World* world, float px=100, float py=500);

    void events(sf::Event& event);

    void render(sf::RenderWindow& window);

    void update(float dt = 0);

private:
    int m_keyState = 0;

    sf::Clock shotTimer;
    float shot_cooldown = 1.f;
    float shot_max_power = 300.f;
    float angle = 45;
    float shot_power = 50.f;

    b2Vec2 power;
    sf::Sprite arrow;
    sf::Sprite arrow_full;
    int selectedShot = 1;
};

#endif // PLAYERENTITY_H
