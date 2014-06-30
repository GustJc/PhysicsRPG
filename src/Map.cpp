#include "Map.h"
#include "Wall.h"
#include <SpriteBody.h>
#include <Engine.h>
#include <fstream>
#include <iostream>
#include <sstream>

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
    int type;
    while(file >> x >> y >> type >> angle)
    {

        Wall* w = new Wall(type, x, y);
        w->createBody(*world);

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

        file << b->getBody()->GetPosition().x << " " << b->getBody()->GetPosition().y << endl;
        file << b->type << " " << b->getBody()->GetAngle() << endl;

    }

    file.close();

    cout << "Mapa salvo: " << absFileName << endl;
}
