#include "GameState.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Flag.h"
#include "Character.h"
#include "PlayerEntity.h"
#include "Effects.h"
#include "Spawner.h"
#include <cmath>

#include <iostream>
using namespace std;
GameState::GameState(sf::RenderWindow& wnd) :
State(wnd)
{
    //ctor
}
GameState::~GameState()
{
    //dtor

}

void GameState::load(int )
{
    cout << "[Estado] Carregando estado GameState. " << endl;

    m_debug_render = new DebugRender(&window);
    m_debug_render->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    TextureManager::TextureControl.load("menu_superior", "data/menu_su.png");
    TextureManager::TextureControl.load("tileset", "data/tileset.png");

    TextureManager::TextureControl.load("player", "data/player.png");
    TextureManager::TextureControl.load("flag", "data/flag.png");
    TextureManager::TextureControl.load("slime", "data/slime.png");
    TextureManager::TextureControl.load("weak_orc", "data/weak_orc.png");
    TextureManager::TextureControl.load("spawn", "data/spawn.png");

    TextureManager::TextureControl.load("wood", "data/img/wood-block-lowres-16.png");
    TextureManager::TextureControl.load("wood_large", "data/img/wood-block-large.png");
    TextureManager::TextureControl.load("boulder_8", "data/img/boulder-rad8.png");
    TextureManager::TextureControl.load("boulder_16", "data/img/boulder-rad16.png");

    TextureManager::TextureControl.load("explosion", "data/explosion.png");

    b2Vec2 gravity(0.0f, 10.0f);

    //Prepara mundo
    Engine::world = new b2World(gravity);
    world =  Engine::world;

    world->SetAllowSleeping(true);
    world->SetDebugDraw(m_debug_render);

    // Cria Chão
    b2BodyDef ground_def;
    ground_def.position.Set(400.0f/pixelsPerMeter, 600.0/pixelsPerMeter);

    b2Body* m_ground = world->CreateBody(&ground_def);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(800.f/pixelsPerMeter, 80.f/pixelsPerMeter);
    m_ground->CreateFixture(&groundBox, 0.0f);

    Flag * flag = new Flag();
    flag->setTexture(TextureManager::TextureControl.get("flag"), 29, 46, 2, 400);
    flag->getSprite()->setOrigin(15,23);
    flag->getBodyDef()->position.Set(700.0f/pixelsPerMeter, (520.f-23.f)/pixelsPerMeter);
    ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(14.0f/pixelsPerMeter,23.0f/pixelsPerMeter);
    flag->createBody(*world);
    flag->getBody()->SetUserData(flag);
    Engine::bodylist.push_back(flag);

    //Spawner * spawner = new Spawner(world, 600.0f/pixelsPerMeter, (520.f-35.f)/pixelsPerMeter);
    //Engine::bodylist.push_back(spawner);
    Character* c = new Character(world, (300)/pixelsPerMeter, (500)/pixelsPerMeter);
    Engine::bodylist.push_back(c);

    player = new PlayerEntity(world);
    player->setTexture(TextureManager::TextureControl.get("player"), 47, 40);
    player->getSprite()->setOrigin(23,20);
    Engine::bodylist.push_back(player);

    //in FooTest constructor
    world->SetContactListener(&listenner);


    loadMap("output.map");
}

int GameState::unload()
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

    if(Engine::effectslist.empty() == false)
    {
        for(int i = 0; i < (int) Engine::effectslist.size(); i++)
            delete Engine::effectslist[i];

        Engine::effectslist.clear();
    }

    return mStack;
}

eStateType GameState::update(float dt)
{
    world->Step(dt, 8, 4);

    for(int i = 0; i < (int) Engine::bodylist.size(); i++)
    {
        Engine::bodylist[i]->update(dt);
    }

    for(int i = 0; i < (int) Engine::effectslist.size(); i++)
    {
        Engine::effectslist[i]->update(dt);
    }

    return mStado;
}

void GameState::events(sf::Event& event)
{
    player->events(event);
    if(event.type == sf::Event::KeyPressed)
    {
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
//Debug Controls

        if(event.key.code == sf::Keyboard::X)
        {
            SplashAnimation* sa = new SplashAnimation(TextureManager::TextureControl.get("explosion"), sf::Vector2i(16,16),
                                      b2Vec2(300/pixelsPerMeter, (500)/pixelsPerMeter), 5, 100, sf::Vector2f(5.0, 5.0) );
            sa->inicialImpulse = b2Vec2(1, 1);
        }
        if(event.key.code == sf::Keyboard::Z)
        {
            SplashText* sa = new SplashText("Teste",
                                                 b2Vec2((100)/pixelsPerMeter, (500)/pixelsPerMeter)
                                                 ,sf::Color::Blue, 30, 1000);
            sa->inicialImpulse = b2Vec2(1, 1);
        }

//Move camera
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
//Zoom
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

    }
}

void GameState::render()
{

    //Draw floor
    Engine::EngineControl.drawRectVertex(-400,520,1600,160);
    for(int x = -300; x < 1600; x+= 100)
        Engine::EngineControl.drawRectVertex(x,520,2,160,sf::Color(0,100,0));

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

    //Effects layer
    for(int i = 0; i < (int) Engine::effectslist.size(); i++)
    {
        Engine::effectslist[i]->render(window);
    }

    //Draw selection area
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(mouseTemp);

    int width = 16;
    int height = 16;
    if(selectedId == 2) width = 16 * 4;
    if(selectedId == 3) height = 16 * 4;
    Engine::EngineControl.drawRectVertex( floor(mouse.x/16.f)*16, floor(mouse.y/16.f)*16, width, height, sf::Color(100,50,100,50) );


    sf::Sprite menu;
    menu.setTexture(TextureManager::TextureControl.get("menu_superior"));
    menu.setPosition( window.mapPixelToCoords(sf::Vector2i(0,0) ) );
    window.draw(menu);


    //Draw debug data
    if(isDebug)
        world->DrawDebugData();
}

#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
void GameState::loadMap(string filename)
{
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
        cout << "x: " << x << endl;
        cout << "type: " << type << endl;
        SpriteBody* sp_body = new SpriteBody(type);
        sp_body->createBody(*world);
        sp_body->getBody()->SetFixedRotation(false);
        sp_body->getBody()->SetTransform(b2Vec2(x,y), angle);

        Engine::bodylist.push_back(sp_body);

    }

    file.close();

    cout << "Map loaded: " << absFileName << endl;

}

