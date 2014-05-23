#include <iostream>
#include "Flag.h"

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
    cout << "I'm dead!!!" << endl;
}

void Flag::endContact(Body * body)
{

}
