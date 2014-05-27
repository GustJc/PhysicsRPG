#ifndef FLAG_H
#define FLAG_H

#include "SpriteBody.h"

class Flag : public SpriteBody
{
    public:
        Flag();
        virtual ~Flag();
        void startContact(Body * body);
        void endContact(Body * body);
    protected:
        int HP = 10;
        int touching_objs=0;
    private:
};

#endif // FLAG_H
