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
    Body* bodyUserData = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();

    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        bodyUserData->startContact(contactedBody, contact);
        contactedBody->startContact(bodyUserData, contact);
    }
}

void ContactListenner::EndContact(b2Contact* contact)
{
    Body* bodyUserData = (Body*)contact->GetFixtureA()->GetBody()->GetUserData();

    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        bodyUserData->endContact(contactedBody, contact);
        contactedBody->endContact(bodyUserData, contact);
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
