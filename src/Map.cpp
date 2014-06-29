#include "Map.h"

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

        SpriteBody* sp_body = new SpriteBody(type);
        sp_body->createBody(*world);
        sp_body->getBody()->SetFixedRotation(false);
        sp_body->getBody()->SetTransform(b2Vec2(x,y), angle);

        Engine::bodylist.push_back(sp_body);

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
        Body* b = Engine::bodylist[i];
        if(b->type == 0) continue;
        file << b->getBody()->GetPosition().x << " " << b->getBody()->GetPosition().y << endl;
        //b2PolygonShape* poly = (b2PolygonShape*) b->getBody()->GetFixtureList()->GetShape();
        file << b->type << " " << b->getBody()->GetAngle() << endl;
//             << " " << poly->GetVertexCount() << endl;
//        for( int id = 0; id < poly->GetVertexCount(); id++)
//        {
//            file << poly->GetVertex(id).x << " " << poly->GetVertex(id).y << endl;
//        }
    }

    file.close();

    cout << "Mapa salvo: " << absFileName << endl;
}
