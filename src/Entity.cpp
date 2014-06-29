#include "Entity.h"
#include "Effects.h"
#include "Globals.h"
Entity::Entity()
{
    //ctor
    is_dead = false;
}

Entity::~Entity()
{
    //dtor
}

int Entity::damage(int attack)
{
    int dano = attack;
    int random = rand() % int(def+1);

    dano -= random;

    cout << "Dano: " << dano << endl;

    if(dano > 0){
        HP -= dano;
        if(HP <= 0){
            die();
            isDelete = true;
        }
        return dano;
    }

    return 0;

}

void Entity::die()
{
    is_dead = true;
}

bool Entity::isDead()
{
    return is_dead;
}
