#include <iostream>
#include "Flag.h"
#include <iostream>
using namespace std;

Flag::Flag()
{
    //ctor
}

Flag::~Flag()
{
    //dtor
}

void Flag::startContact(Body * body)
{
    touching_objs++;
    if(touching_objs >= HP)
        cout << "I'm dead!!!" << endl;

    cout << touching_objs << endl;
    int green = touching_objs * 25;
    if(green > 255 ) green = 255;

    m_animation.getSprite().setColor(sf::Color(0,green, 0));
}

void Flag::endContact(Body * body)
{
    touching_objs--;
}
