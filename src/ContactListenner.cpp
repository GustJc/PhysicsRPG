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

void ContactListenner::PreSolve(b2Contact *contact, const b2Manifold *)
{
    void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData != nullptr)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
       // cout << static_cast<Body*>( bodyUserData )->name << endl;
        bool response = static_cast<Body*>( bodyUserData )->preSolve(contactedBody, contact);

        if(!response){
            contact->SetEnabled(false);
        }
    }
}

void ContactListenner::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
    void * bodyUserData = contact->GetFixtureA()->GetBody()->GetUserData();
    if (bodyUserData)
    {
        Body* contactedBody = (Body*)contact->GetFixtureB()->GetBody()->GetUserData();
        static_cast<Body*>( bodyUserData )->postSolve(contactedBody, impulse);
    }
}
