#include "GameState.h"
#include "Globals.h"
#include "TextureManager.h"
#include "Engine.h"
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

void GameState::load(int stack)
{
    m_debug_render = new DebugRender(&window);
    m_debug_render->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    TextureManager::TextureControl.load("catapult", "data/img/catapult-fix.png");
    TextureManager::TextureControl.load("boulder", "data/img/wood-block-lowres-16.png");

    b2Vec2 gravity(0.0f, 10.0f);

    world = new b2World(gravity);
    world->SetAllowSleeping(true);
    world->SetDebugDraw(m_debug_render);

    // Chão
    b2BodyDef ground_def;
    ground_def.position.Set(0.0f, 600.0/pixelsPerMeter);

    b2Body* m_ground = world->CreateBody(&ground_def);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.f, 50.f/pixelsPerMeter);
    m_ground->CreateFixture(&groundBox, 0.0f);

//Dinamico

/*
    sp_body.setTexture();
    sp_body.getSprite()->setOrigin(8,8);
    //clone
    *sp_body.getBodyDef() = body->m_bodyDef;
    sp_body.getBodyDef()->position.Set(250.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    sp_body.getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
    *sp_body.getBodyFixture() = body->m_bodyFix;
    sp_body.getBodyFixture()->shape = sp_body.getBodyShape();

    sp_body.setWorld(*world);

    sp_body.getBody()->SetAngularVelocity(-2);
    */
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
/*
    b2Vec2 position = body->getBody()->GetPosition();
    float32 angle = body->getBody()->GetAngle();
    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
*/
    for(int i = 0; i < (int) bodylist.size(); i++)
    {
        bodylist[i]->update(dt);
    }


    return GST_NONE;
}

void GameState::events(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Space){
            SpriteBody* sp_body = new SpriteBody();

            sp_body->setTexture(TextureManager::TextureControl.get("boulder"));
            sp_body->getSprite()->setOrigin(8,8);
            sp_body->getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
            sp_body->getBodyDef()->position.Set((0)/pixelsPerMeter, (530)/pixelsPerMeter);
            sp_body->getBodyDef()->type = b2_dynamicBody;

            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float velX = mouse.x - sp_body->getBodyDef()->position.x;
            float velY = mouse.y - sp_body->getBodyDef()->position.y*pixelsPerMeter;
            cout << velY << endl;

            sp_body->getBodyDef()->linearVelocity.Set(velX/pixelsPerMeter, velY/pixelsPerMeter);
            sp_body->getBodyFixture()->friction = 0.5f;
            sp_body->getBodyDef()->angularVelocity = 2.f;

            sp_body->setWorld(*world);

            bodylist.push_back(sp_body);
        }
    }
    else if(event.type == sf::Event::MouseButtonPressed)
    {
        sf::Vector2i mouse = sf::Mouse::getPosition(window);
        float mouseX = floor(mouse.x/16.f)*16;
        float mouseY = floor(mouse.y/16.f)*16;
        SpriteBody* sp_body = new SpriteBody();

        sp_body->setTexture(TextureManager::TextureControl.get("boulder"));
        sp_body->getSprite()->setOrigin(8,8);
        sp_body->getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
        sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
        sp_body->getBodyDef()->type = b2_dynamicBody;

        sp_body->setWorld(*world);

        bodylist.push_back(sp_body);
    }
}

void GameState::render()
{
    for(int i = 0; i < (int) bodylist.size(); i++)
    {
        bodylist[i]->render(window);
    }

    //Grid
    for(unsigned short int x = 0; x < WINDOW_WIDTH; x+= 16)
        Engine::EngineControl.drawLine(x,0, x, WINDOW_HEIGHT, sf::Color(0,0,0, 20));
    for(unsigned short int y = 0; y < WINDOW_HEIGHT; y+= 16)
        Engine::EngineControl.drawLine(0,y, WINDOW_WIDTH, y, sf::Color(0,0,0, 50) );

    sf::Vector2i mouse = sf::Mouse::getPosition(window);
    Engine::EngineControl.drawRectVertex( floor(mouse.x/16.f)*16, floor(mouse.y/16.f)*16, 16, 16, sf::Color(100,50,100,50) );

    world->DrawDebugData();
}
