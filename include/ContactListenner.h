#ifndef CONTACTLISTENNER_H
#define CONTACTLISTENNER_H

#include <Box2D/Box2D.h>

class ContactListenner : public b2ContactListener
{
    public:
        ContactListenner();
        virtual ~ContactListenner();
        void BeginContact(b2Contact* contact);
        void EndContact(b2Contact* contact);
        void PreSolve(b2Contact* contact, const b2Manifold* oldManifold);
        void PostSolve(b2Contact* contact, const b2ContactImpulse* impulse);
    protected:
    private:
};

#endif // CONTACTLISTENNER_H
