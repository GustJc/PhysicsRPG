#include <iostream>
#include "Flag.h"
#include <iostream>
using namespace std;

Flag::Flag()
{
    //ctor
    type = 1;
}

Flag::~Flag()
{
    //dtor
}

void Flag::startContact(Body *, b2Contact * )
{
    die();

    m_animation.getSprite().setColor(sf::Color(0,255, 0));
}

void Flag::endContact(Body * , b2Contact *)
{
    touching_objs--;
}
