#include "Map.h"
#include "Wall.h"
#include "Spawner.h"
#include "Character.h"
#include <SpriteBody.h>
#include <Engine.h>
#include <fstream>
#include <iostream>
#include <sstream>

enum
{
    OBJ_WALL=1,
    OBJ_SPAWN,
    OBJ_FLAG,
    OBJ_ENEMY
};

enum
{
    WALL_BLOCK=1,
    WALL_LONG_VERTICAL,
    WALL_LONG_HORIZONTAL
};

Map Map::MapControl;

Map::Map()
{
}

void Map::loadMap(string filename)
{
    b2World* world = Engine::world;
    ifstream file;
    string absFileName("./data/map/"+filename);
    file.open( absFileName.c_str());

    if(file.is_open() == false){
        printf("Nao foi possivel abrir o arquivo: %s.\n", absFileName.c_str());
        return;
    }


    float x, y, angle;
    int objtype, type;
    while(file >> objtype >> x >> y >> type >> angle)
    {
        if(objtype == OBJ_WALL){
            Wall* w = new Wall(type, x, y);
            w->createBody(*world);
        }else if(objtype == OBJ_SPAWN){
            Spawner* s = new Spawner(Engine::world,x,y);
            Engine::bodylist.push_back(s);
        }else if(objtype == OBJ_FLAG){


        }else if(objtype == OBJ_ENEMY){


        }


    }

    file.close();

    cout << "Map loaded: " << absFileName << endl;

}

void Map::saveMap(string filename)
{
    ofstream file;
    string absFileName("./data/map/"+filename);
    file.open( absFileName.c_str(),ios::out | ios::binary);

    //Box2D objects
    for(unsigned int i = 0; i < Engine::bodylist.size(); i++)
    {
        cout << "Body" << endl;
        Body* b = Engine::bodylist[i];
        if(b->type == 0) continue; //ignore flag

        if(b->name == "wall")
            file << OBJ_WALL << " ";
        else if(b->name == "spawner")
            file << OBJ_SPAWN << " ";
        else if(b->name == "enemy")
            file << OBJ_ENEMY << " ";
        else if(b->name == "flag")
            file << OBJ_FLAG << " ";

        file << b->getBody()->GetPosition().x << " " << b->getBody()->GetPosition().y << endl;
        file << b->type << " " << b->getBody()->GetAngle() << endl;

    }

    file.close();

    cout << "Mapa salvo: " << absFileName << endl;
}
