#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
typedef enum eStateType {
    GST_NONE,
    GST_GAME,
    GST_MENU,
    GST_TESTE,
    GST_MAP,
    GST_EXIT
} StateType;

class State
{
    public:
        virtual void load(int stack = 0) = 0;
        virtual int unload() = 0;
        virtual eStateType update(float dt) = 0;
        virtual void render() = 0;
        virtual void events(sf::Event& event) = 0;
        virtual ~State(){};
        State(sf::RenderWindow& wnd) : window(wnd){mStack = 0;mStado = GST_NONE;};

    protected:
        sf::RenderWindow& window;
        int mStack;
        eStateType mStado;
};



#endif // STATE_H
