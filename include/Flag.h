#ifndef FLAG_H
#define FLAG_H

#include "Entity.h"

class Flag : public Entity
{
    public:
        Flag();
        virtual ~Flag();
        void startContact(Body * body, b2Contact *contact);
        void endContact(Body * body, b2Contact *contact);
    protected:
        int HP = 10;
        int touching_objs=0;
    private:
};

#endif // FLAG_H
