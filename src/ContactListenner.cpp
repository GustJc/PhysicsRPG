#include "ContactListenner.h"
#include "Body.h"

ContactListenner::ContactListenner()
{

}

ContactListenner::~ContactListenner()
{
    //dtor
}
#include <iostream>
using namespace std;
void ContactListenner::BeginContact(b2Contact* contact)
{
    void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();


    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        static_cast<Body*>( bodyUserData )->startContact(contactedBody);
    }
}

void ContactListenner::EndContact(b2Contact* contact)
{
    void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();

    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        static_cast<Body*>( bodyUserData )->endContact(contactedBody);
    }
}
