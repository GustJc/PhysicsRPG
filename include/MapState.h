#ifndef MAPSTATE_H
#define MAPSTATE_H

#include "State.h"
#include <SFML/Graphics.hpp>
#include <vector>
#include <map>
#include <string>
using namespace std;
class NodeData;
class MapState : public State
{
    public:
        MapState(sf::RenderWindow& wnd);
        virtual ~MapState();

        void load(int stack = 0);
        int unload();
        eStateType update(float dt);
        void events(sf::Event& event);
        void render();
        void renderNode(NodeData *root);
        void openNode(NodeData *node);
protected:
        sf::Sprite sp_map;
        sf::Sprite sp_dot;
    private:
        map<int, string> fases;
};

#endif // MAPSTATE_H
