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

void ContactListenner::PreSolve(b2Contact *contact, const b2Manifold *manifold)
{
    Body * bodyUserData = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData != nullptr)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        bodyUserData->preSolve(contactedBody, contact, manifold);
        contactedBody->preSolve(bodyUserData, contact, manifold);
    }
}

void ContactListenner::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    Body * bodyUserData = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        bodyUserData->postSolve(contactedBody, contact, impulse);
        contactedBody->postSolve(bodyUserData, contact, impulse);
    }
}
