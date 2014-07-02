#include "EditorState.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Flag.h"
#include "Character.h"
#include "Map.h"
#include "Wall.h"
#include "Spawner.h"
#include <cmath>

#include <iostream>
using namespace std;
EditorState::EditorState(sf::RenderWindow& wnd) :
State(wnd)
{
    //ctor
}
EditorState::~EditorState()
{
    //dtor

}

void EditorState::load(int )
{
    cout << "[Estado] Carregando estado EditorState. " << endl;
    m_debug_render = new DebugRender(&window);
    m_debug_render->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    TextureManager::TextureControl.load("catapult", "data/img/catapult-fix.png");
    TextureManager::TextureControl.load("boulder", "data/img/wood-block-lowres-16.png");
    TextureManager::TextureControl.load("boulder_large", "data/img/wood-block-large.png");
    TextureManager::TextureControl.load("yellow", "data/img/wood-block-yellow.png");
    TextureManager::TextureControl.load("metal", "data/img/metal-block.png");

    TextureManager::TextureControl.load("player", "data/player.png");
    TextureManager::TextureControl.load("flag", "data/flag.png");

    TextureManager::TextureControl.load("tileset", "data/tileset.png");

    TextureManager::TextureControl.load("boulder_8", "data/img/boulder-rad8.png");
    TextureManager::TextureControl.load("boulder_16", "data/img/boulder-rad16.png");
    TextureManager::TextureControl.load("boulder_32", "data/img/boulder-rad32.png");

    TextureManager::TextureControl.load("spawn", "data/spawn.png");

    b2Vec2 gravity(0.0f, 10.0f);

    world = new b2World(gravity);
    world->SetAllowSleeping(true);
    world->SetDebugDraw(m_debug_render);

    // Cria Chão
    b2BodyDef ground_def;
    ground_def.position.Set(400.0f/pixelsPerMeter, 600.0/pixelsPerMeter);

    b2Body* m_ground = world->CreateBody(&ground_def);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(800.f/pixelsPerMeter, 80.f/pixelsPerMeter);
    m_ground->CreateFixture(&groundBox, 0.0f);

    //in FooTest constructor
    world->SetContactListener(&listenner);

    Flag * flag = new Flag();
    flag->type = 0;
    flag->setTexture(TextureManager::TextureControl.get("flag"), 29, 46, 2, 400);
    flag->getSprite()->setOrigin(15,23);
    flag->getBodyDef()->position.Set(1100.0f/pixelsPerMeter, (520.f-23.f)/pixelsPerMeter);
    ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(14.0f/pixelsPerMeter,23.0f/pixelsPerMeter);
    flag->createBody(*world);
    flag->getBody()->SetUserData(flag);
    Engine::bodylist.push_back(flag);


}

int EditorState::unload()
{
    if(m_debug_render != nullptr)
        delete m_debug_render;
    if(world != nullptr)
        delete world;

    if(Engine::bodylist.empty() == false)
    {
        for(int i = 0; i < (int) Engine::bodylist.size(); i++)
            delete Engine::bodylist[i];

        Engine::bodylist.clear();
    }

    return mStack;
}

eStateType EditorState::update(float dt)
{
    world->Step(dt, 8, 4);
/*
    b2Vec2 position = body->getBody()->GetPosition();
    float32 angle = body->getBody()->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
*/
    for(int i = 0; i < (int) Engine::bodylist.size(); i++)
    {
        Engine::bodylist[i]->update(dt);
    }

    return mStado;
}

void EditorState::events(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::P){
            Map::MapControl.saveMap("output.map");
        }
        if(event.key.code == sf::Keyboard::Escape)
        {
            mStado = GST_MENU;
        }
        else if(event.key.code == sf::Keyboard::Q){
            isDebug = !isDebug;
        }
        else if(event.key.code == sf::Keyboard::E){
            isGrid = !isGrid;
        }
        else if(event.key.code == sf::Keyboard::R){
            unload();
            load();
        }
        else if(event.key.code == sf::Keyboard::RControl ||
                event.key.code == sf::Keyboard::LControl ){
            isSnap = !isSnap;
        }
//Move Controls
        else if(event.key.code == sf::Keyboard::D)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(20,0));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::A)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(-20,0));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::W)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(0,-20));
            window.setView(view);
        }
        else if(event.key.code == sf::Keyboard::S)
        {
            sf::View& view = Engine::EngineControl.getViewGame();
            view.move(sf::Vector2f(0,20));
            window.setView(view);
        }
//Zoom controls
        if(event.key.control)
        {
            if(event.key.code == sf::Keyboard::Equal)
            {
                sf::View& view = Engine::EngineControl.getViewGame();
                view.zoom(0.8f);
                window.setView(view);
            }
            else
            if(event.key.code == sf::Keyboard::Dash)
            {
                sf::View& view = Engine::EngineControl.getViewGame();
                view.zoom(1.2f);
                window.setView(view);
            }
        }
//Editor controls
        else
        if(event.key.code == sf::Keyboard::Space){
            SpriteBody* sp_body = new SpriteBody();

            sp_body->setTexture(TextureManager::TextureControl.get("boulder"));
            sp_body->getSprite()->setOrigin(8,8);
            bool isCircle = false;

            if(selectedId == 1){
                sp_body->type = 1;
                ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
            }else
            {
                if(selectedId == 2){
                    sp_body->type = 2;
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_8"));
                    sp_body->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;
                } else
                if(selectedId == 3) {
                    sp_body->type = 3;
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_16"));
                    sp_body->m_bodyCircleShape.m_radius = 8/pixelsPerMeter;
                } else
                if(selectedId == 4) {
                    sp_body->type = 4;
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_32"));
                    sp_body->m_bodyCircleShape.m_radius = 16/pixelsPerMeter;
                }
                isCircle = true;
                sp_body->m_bodyCircleShape.m_p.Set(0,0);
            }

            sp_body->getBodyDef()->position.Set((0)/pixelsPerMeter, (530)/pixelsPerMeter);
            sp_body->getBodyDef()->type = b2_dynamicBody;

            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float velX = mouse.x - sp_body->getBodyDef()->position.x;
            float velY = mouse.y - sp_body->getBodyDef()->position.y*pixelsPerMeter;

            sp_body->getBodyDef()->linearVelocity.Set(velX/pixelsPerMeter, velY/pixelsPerMeter);
            sp_body->getBodyFixture()->friction = 0.5f;
            sp_body->getBodyFixture()->density = 0.1f;

            sp_body->createBody(*world, isCircle);
            sp_body->getBody()->SetFixedRotation(false);
            if(selectedId == 1){
                sp_body->getBody()->ApplyAngularImpulse(0.01f, true);
            } else{
                sp_body->getBody()->ApplyAngularImpulse(0.001f, true);
            }


            Engine::bodylist.push_back(sp_body);
        }
        else if(event.key.code == sf::Keyboard::Num1){
            selectedId = 1;
            b_width = 16; b_height = 16;
        }
        else if(event.key.code == sf::Keyboard::Num2){
            selectedId = 2;
            b_width = 16*5; b_height = 16;
        }
        else if(event.key.code == sf::Keyboard::Num3){
            selectedId = 3;
            b_width = 16; b_height = 16*5;
        }
        else if(event.key.code == sf::Keyboard::Num4){
            selectedId = 4;
            b_width = 16*5; b_height = 16*5;
        }
        else if(event.key.code == sf::Keyboard::Num5){
            selectedId = 5;
        }
        else if(event.key.code == sf::Keyboard::Num6){
            selectedId = 6;
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        createWallObject();

    }
}

void EditorState::render()
{
    for(int i = 0; i < (int) Engine::bodylist.size(); i++)
    {
        Engine::bodylist[i]->render(window);
    }

    sf::Vector2f offset = window.getView().getCenter();
    sf::Vector2f start(offset.x - WINDOW_WIDTH/2.f, offset.y - WINDOW_HEIGHT/2.f);

    //Draw grid
    if(isGrid)
    {
        for(int x = start.x; x < start.x+WINDOW_WIDTH; x+= 16)
            Engine::EngineControl.drawLine(x, start.y, x, start.y+WINDOW_HEIGHT, sf::Color(0,0,0, 20));
        for(int y = start.y; y < start.y+WINDOW_HEIGHT; y+= 16)
            Engine::EngineControl.drawLine(start.x, y, start.x+WINDOW_WIDTH, y, sf::Color(0,0,0, 50) );
    }
    //Draw floor
    Engine::EngineControl.drawRectVertex(-400,520,1600,160);
    for(int x = -300; x < 1600; x+= 100)
        Engine::EngineControl.drawRectVertex(x,520,2,160,sf::Color(0,100,0));

    //Draw selection area
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(mouseTemp);

    int mouseX = mouse.x - 8.f;
    int mouseY = mouse.y - 8.f;
    if(isSnap)
    {
        mouseX = floor(mouse.x/16.f)*16;
        mouseY = floor(mouse.y/16.f)*16;
    }

    Engine::EngineControl.drawRectVertex( mouseX, mouseY, b_width, b_height, sf::Color(100,50,100,50) );

    //Draw debug data
    if(isDebug)
        world->DrawDebugData();
}

#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
void EditorState::saveMap(string filename)
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

void EditorState::createWallObject()
{
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(mouseTemp);
    float mouseX = mouse.x - 8.f;
    float mouseY = mouse.y - 8.f;

    if(isSnap)
    {
        mouseX = floor(mouse.x/16.f)*16;
        mouseY = floor(mouse.y/16.f)*16;
    }
//Blocks
    //Normal block
    if(selectedId == 1)
    {
        Wall* w = new Wall(1, (float)(8.f+mouseX)/pixelsPerMeter, (float)(8.f+mouseY)/pixelsPerMeter);
        w->createBody(*world);
    }else
    if(selectedId == 2)
    {
        Wall* w = new Wall(2, (float)(16*2.5+mouseX)/pixelsPerMeter, (float)(8+mouseY)/pixelsPerMeter);
        w->createBody(*world);
    } else
    if(selectedId == 3)
    {
        Wall* w = new Wall(3, (float)(8+mouseX)/pixelsPerMeter, (float)(16*2.5+mouseY)/pixelsPerMeter);
        w->createBody(*world);
    }else
    if(selectedId == 4)
    {
        Spawner * spawner = new Spawner(world, (float)(16*2+mouseX)/pixelsPerMeter, (float)(16*2.5+mouseY-8)/pixelsPerMeter, false);
        Engine::bodylist.push_back(spawner);
    }
//    else
//    if(selectedId >= 2 && selectedId <= 3)
//    {

//        SpriteBody* sp_body = new SpriteBody();

//        //sp_body->setTexture(TextureManager::TextureControl.get("boulder_large"));
//        sp_body->setTexture(TextureManager::TextureControl.get("tileset"), 16*5,16);
//        sp_body->setFixedSpritePosition(0, 0);

//        if(selectedId == 2){
//            sp_body->type = 2;
//            sp_body->getSprite()->setOrigin( 16*4/2.f , 16/2.f);
//            ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox( (16*2.5f-0.2f)/pixelsPerMeter,7.8f/pixelsPerMeter);
//            sp_body->getBodyDef()->position.Set((16*2.5+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
//        } else
//        {
//            sp_body->type = 3;
//            sp_body->getSprite()->setOrigin( 16/2.f, 16*4/2.f);
//            ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(7.8f/pixelsPerMeter,(16*2.5f-0.2f)/pixelsPerMeter);
//            sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (16*2.5+mouseY)/pixelsPerMeter);
//            sp_body->setDefaultRotation(90);
//        }

//        sp_body->getBodyDef()->type = b2_dynamicBody;
//        sp_body->getBodyFixture()->friction = 0.5f;
//        sp_body->getBodyFixture()->density = 0.1f;

//        sp_body->createBody(*world);
//        sp_body->getBody()->SetFixedRotation(false);

//        Engine::bodylist.push_back(sp_body);
//    }else
//    if(selectedId >= 4 && selectedId <= 5)
//    {

//        SpriteBody* sp_body = new SpriteBody();

//        sp_body->getSprite()->setOrigin(8,8);
//        ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(7.8f/pixelsPerMeter,7.8f/pixelsPerMeter);
//        sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
//        sp_body->getBodyDef()->type = b2_dynamicBody;

//        if(selectedId == 4){
//            sp_body->type = 4;
//            sp_body->setTexture(TextureManager::TextureControl.get("yellow"));
//            sp_body->getBodyFixture()->friction = 0.9f;
//            sp_body->getBodyFixture()->density = 0.6f;
//        }else if(selectedId == 5){
//            sp_body->type = 5;
//            sp_body->setTexture(TextureManager::TextureControl.get("metal"));
//            sp_body->getBodyFixture()->friction = 1.0f;
//            sp_body->getBodyFixture()->density = 2.0f;
//        }

//        sp_body->createBody(*world);
//        sp_body->getBody()->SetFixedRotation(false);

//        Engine::bodylist.push_back(sp_body);
//    }
}
