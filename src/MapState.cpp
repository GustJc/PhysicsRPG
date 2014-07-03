#include "MapState.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Map.h"

ostream& operator << (ostream& os, const sf::Vector2i& s)
{
    return os << "Vector2i[ x: " << s.x << " y: " << s.y << " ]" << endl;
}
ostream& operator << (ostream& os, const sf::Vector2f& s)
{
    return os << "Vector2f[ x: " << s.x << " y: " << s.y << " ]" << endl;
}

class NodeData
{
public:
    NodeData(float x, float y, NodeData* parent = nullptr);

    sf::Vector2f pos;

    bool complete = false;
    bool over = false;
    bool selected = false;
    bool visible = false;

    vector<NodeData*> adjacent;

    void updateSelection(sf::Vector2i mousePos);
};

vector<NodeData*> nodes;


MapState::MapState(sf::RenderWindow& wnd)
: State(wnd)
{
    //ctor
}

MapState::~MapState()
{
    for(auto item : nodes) {
        delete item;
    }
}

void MapState::load(int stack )
{
    cout << "[Estado] Carregando estado MapState. " << endl;
    TextureManager::TextureControl.load("map", "data/map.png");
    TextureManager::TextureControl.load("dot", "data/dot.png");

    sp_map.setTexture(TextureManager::TextureControl.get("map") );
    sp_dot.setTexture(TextureManager::TextureControl.get("dot") );
    sp_dot.setOrigin(10,9);

    auto node = new NodeData(180, 514);
    auto node2 = new NodeData(255,400, node);
        auto node3 = new NodeData(380,340, node2);
        auto node4 = new NodeData(565,384, node3);
    auto node5 = new NodeData(145,310, node2);
    auto node6 = new NodeData(190,90, node5);
    auto node7 = new NodeData(410,70, node6);
        auto node8 = new NodeData(520,50, node7);
    auto node9 = new NodeData(370,210, node7);

    auto node10 = new NodeData(505,140, node9);
    auto node11 = new NodeData(540,170, node10);
    auto node12 = new NodeData(565,210, node11);
    auto node13 = new NodeData(680,365, node12);

    nodes.push_back( node );
    nodes.push_back( node2 );
    nodes.push_back( node3 );
    nodes.push_back( node4 );
    nodes.push_back( node5 );
    nodes.push_back( node6 );
    nodes.push_back( node7 );
    nodes.push_back( node8 );
    nodes.push_back( node9 );
    nodes.push_back( node10 );
    nodes.push_back( node11 );
    nodes.push_back( node12 );
    nodes.push_back( node13 );

    //Fases
    fases[0] = "output.map";
    fases[1] = "map3.map";
    fases[2] = "map4.map";

    fases[3] = "output.map";
    fases[4] = "map3.map";
    fases[5] = "map4.map";
    fases[6] = "output.map";
    fases[7] = "map3.map";
    fases[8] = "map4.map";
    fases[9] = "output.map";
    fases[10] = "map3.map";
    fases[11] = "map4.map";

    Map::MapControl.map_name = fases[0];

    //Completou ultimo mapa
    if(stack == 1)
    {
        for( map<int, string>::iterator it = fases.begin();
             it != fases.end(); it++)
        {
            if(it->second == Map::MapControl.map_name)
            { //Mesmo nome, então chave
                Map::MapControl.fases.push_back(it->first);
                cout << "Novo completo " << it->first << endl;
                break;
            }
        }

    }

    for(int i = 0; i < (int)Map::MapControl.fases.size(); i++)
    {
        int index = Map::MapControl.fases[i];
        nodes[index]->complete = true;
        nodes[index]->visible = true;
    }

}
int MapState::unload()
{
    for( auto item : nodes)
        delete item;

    nodes.clear();

    return mStack;
}

eStateType MapState::update(float )
{
    for(int i = 0; i < (int)nodes.size(); i++)
    {
        nodes[i]->updateSelection(sf::Mouse::getPosition(window) );
        if(nodes[i]->selected)
        {
            mStado = GST_GAME;
            Map::MapControl.map_name = fases[i];
        }
    }

    return mStado;
}
void MapState::events(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Q){

            auto node = nodes[0];

            openNode(node);
         }

        if(event.key.code == sf::Keyboard::Escape) {
            mStado = GST_MENU;
        }
    }
    else
    if(event.type == sf::Event::MouseButtonPressed)
    {
        if(event.mouseButton.button == sf::Mouse::Left)
        {
            bool found = false;
            for(NodeData* item : nodes) {
                if( item->over )
                {
                    item->selected = true;
                    found = true;
                    break;
                }
            }
            if(found)
                for(NodeData* item : nodes)
                    if(! item->over)
                        item->selected = false;

        }
    }

}

void MapState::renderNode(NodeData* node)
{
    while(node != nullptr) {
        if(node->complete)
            sp_dot.setScale(2.0, 2.0);
        else
            sp_dot.setScale(1.0, 1.0);

        if(node->selected)
            sp_dot.setColor(sf::Color(255,0,0) );
        else
            sp_dot.setColor(sf::Color(255,255,255) );

        sp_dot.setPosition(node->pos);
        window.draw(sp_dot);
        node->visible = true;

        if( node->complete ){
            for(auto item : node->adjacent) {
                //cout << "Render: " << node->pos.x << " " << node->adjacent.size() << endl;
                renderNode(item);
            }
        }

        node = nullptr;
    }
}

void MapState::openNode(NodeData* node)
{
    if(!node->complete){
        node->complete = true;
        return;
    }


    for(auto item : node->adjacent) {
        openNode(item);
    }

}


void MapState::render()
{
    window.draw(sp_map);

    auto startNode = nodes[0];
    renderNode(startNode);
}


NodeData::NodeData(float x, float y, NodeData *parent)
{
    pos.x = x;
    pos.y =y;
    if(parent != nullptr){
        parent->adjacent.push_back(this);
        //cout << this->pos.x << endl;
    }
}

void NodeData::updateSelection(sf::Vector2i mousePos)
{
    this->over = false;

    if(mousePos.x < pos.x - 10)
        return;
    if(mousePos.y > pos.y + 10)
        return;
    if(mousePos.x > pos.x + 10)
        return;
    if(mousePos.y < pos.y - 10)
        return;

    this->over = true;
}
