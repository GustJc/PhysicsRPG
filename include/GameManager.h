#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "State.h"
#include <SFML/Graphics.hpp>

class GameManager
{
    private:
        State* mEstadoAtual;
        int stack;
    public:
        GameManager();
        virtual ~GameManager();

        int run(int argc, char* args[]);

        void loadMainTextures();

        void executeTests();
};

#endif // GAMEMANAGER_H
