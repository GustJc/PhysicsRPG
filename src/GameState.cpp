#include "GameState.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Engine.h"
#include "Flag.h"
#include "Character.h"
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

    TextureManager::TextureControl.load("player", "data/player.png");
    TextureManager::TextureControl.load("flag", "data/flag.png");

    TextureManager::TextureControl.load("wood", "data/img/wood-block-lowres-16.png");
    TextureManager::TextureControl.load("wood_large", "data/img/wood-block-large.png");
    TextureManager::TextureControl.load("boulder_8", "data/img/boulder-rad8.png");
    TextureManager::TextureControl.load("boulder_16", "data/img/boulder-rad16.png");

    b2Vec2 gravity(0.0f, 10.0f);

    //Prepara mundo
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

    Flag * flag = new Flag();
    flag->setTexture(TextureManager::TextureControl.get("flag"), 29, 46, 2, 400);
    flag->getSprite()->setOrigin(15,23);
    flag->getBodyDef()->position.Set(700.0f/pixelsPerMeter, (520.f-23.f)/pixelsPerMeter);
    ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(14.0f/pixelsPerMeter,23.0f/pixelsPerMeter);
    flag->createBody(*world);
    flag->getBody()->SetUserData(flag);
    bodylist.push_back(flag);

//    flag = new Flag();
//        flag->setTexture(TextureManager::TextureControl.get("player"), 47, 40);
//        flag->getSprite()->setOrigin(23,20);
//        flag->getBodyDef()->position.Set(300.0f/pixelsPerMeter, (520.f-20.f)/pixelsPerMeter);
//        ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(23.0f/pixelsPerMeter,20.0f/pixelsPerMeter);
//        flag->createBody(*world);
//        flag->getBody()->SetUserData(flag);
//        bodylist.push_back(flag);

        Character* c = new Character();
        c->setTexture(TextureManager::TextureControl.get("player"), 47, 40);
        c->getSprite()->setOrigin(23,20);
        ((b2PolygonShape*)c->getBodyShape())->SetAsBox(23.0f/pixelsPerMeter,20.0f/pixelsPerMeter);
        c->getBodyDef()->position.Set((300)/pixelsPerMeter, (500)/pixelsPerMeter);
        c->getBodyDef()->type = b2_dynamicBody;
        c->getBodyFixture()->density = 0.002f;
        c->createBody(*world);
        c->getBody()->SetFixedRotation(true);
        c->getBody()->SetUserData(c);
        bodylist.push_back(c);

    //in FooTest constructor
    world->SetContactListener(&listenner);
}

int GameState::unload()
{
    if(m_debug_render != nullptr)
        delete m_debug_render;
    if(world != nullptr)
        delete world;

    if(bodylist.empty() == false)
    {
        for(int i = 0; i < (int) bodylist.size(); i++)
            delete bodylist[i];

        bodylist.clear();
    }

    return mStack;
}

eStateType GameState::update(float dt)
{
    world->Step(dt, 8, 4);

    for(int i = 0; i < (int) bodylist.size(); i++)
    {
        bodylist[i]->update(dt);
    }


    return mStado;
}

void GameState::events(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Escape)
        {
            mStado = GST_MENU;
        }
        else if(event.key.code == sf::Keyboard::Q){
            isDebug = !isDebug;
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

    }
}

void GameState::render()
{
    for(int i = 0; i < (int) bodylist.size(); i++)
    {
        bodylist[i]->render(window);
    }

    sf::Vector2f offset = window.getView().getCenter();
    sf::Vector2f start(offset.x - WINDOW_WIDTH/2.f, offset.y - WINDOW_HEIGHT/2.f);

    //Draw grid
    for(int x = start.x; x < start.x+WINDOW_WIDTH; x+= 16)
        Engine::EngineControl.drawLine(x, start.y, x, start.y+WINDOW_HEIGHT, sf::Color(0,0,0, 20));
    for(int y = start.y; y < start.y+WINDOW_HEIGHT; y+= 16)
        Engine::EngineControl.drawLine(start.x, y, start.x+WINDOW_WIDTH, y, sf::Color(0,0,0, 50) );

    //Draw floor
    Engine::EngineControl.drawRectVertex(-400,520,1600,160);
    for(int x = -300; x < 1600; x+= 100)
        Engine::EngineControl.drawRectVertex(x,520,2,160,sf::Color(0,100,0));

    //Draw selection area
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(window);
    sf::Vector2f mouse = window.mapPixelToCoords(mouseTemp);

    int width = 16;
    int height = 16;
    if(selectedId == 2) width = 16 * 4;
    if(selectedId == 3) height = 16 * 4;
    Engine::EngineControl.drawRectVertex( floor(mouse.x/16.f)*16, floor(mouse.y/16.f)*16, width, height, sf::Color(100,50,100,50) );

    //Draw debug data
    if(isDebug)
        world->DrawDebugData();
}
