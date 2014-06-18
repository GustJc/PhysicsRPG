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

    TextureManager::TextureControl.load("catapult", "data/img/catapult-fix.png");
    TextureManager::TextureControl.load("boulder", "data/img/wood-block-lowres-16.png");
    TextureManager::TextureControl.load("boulder_large", "data/img/wood-block-large.png");
    TextureManager::TextureControl.load("yellow", "data/img/wood-block-yellow.png");
    TextureManager::TextureControl.load("metal", "data/img/metal-block.png");

    TextureManager::TextureControl.load("boulder_8", "data/img/boulder-rad8.png");
    TextureManager::TextureControl.load("boulder_16", "data/img/boulder-rad16.png");
    TextureManager::TextureControl.load("boulder_32", "data/img/boulder-rad32.png");

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

    Flag * flag = new Flag();
    flag->setTexture(TextureManager::TextureControl.get("catapult"), 96, 96, 4, 200);
    flag->getSprite()->setOrigin(48,48);
    flag->getBodyDef()->position.Set(300.0f/pixelsPerMeter, 200.0f/pixelsPerMeter);
    ((b2PolygonShape*)flag->getBodyShape() )->SetAsBox(96.0f/pixelsPerMeter,48.0f/pixelsPerMeter);

    flag->setWorld(*world);

    flag->getBody()->SetUserData(flag);

    bodylist.push_back(flag);

    //in FooTest constructor
    world->SetContactListener(&listenner);


/**/
    Character* c = new Character();

    c->setTexture(TextureManager::TextureControl.get("yellow"));
    c->getSprite()->setOrigin(8,8);

    ((b2PolygonShape*)c->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);

    c->getBodyDef()->position.Set((500)/pixelsPerMeter, (560)/pixelsPerMeter);
    c->getBodyDef()->type = b2_dynamicBody;

    c->getBodyFixture()->density = 0.01f;

    c->setWorld(*world);
    c->getBody()->SetFixedRotation(true);
    c->getBody()->SetUserData(c);


    bodylist.push_back(c);


//Dinamico

/*
    sp_body.setTexture();
    sp_body.getSprite()->setOrigin(8,8);
    //clone
    *sp_body.getBodyDef() = body->m_bodyDef;
    sp_body.getBodyDef()->position.Set(250.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    sp_body.getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
    *sp_body.getBodyFixture() = body->m_bovoid startContact(Body * body);
        void endContact(Body * body);dyFix;
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
        if(event.key.code == sf::Keyboard::Q){
            isDebug = !isDebug;
        }
        else
        if(event.key.code == sf::Keyboard::Space){
            SpriteBody* sp_body = new SpriteBody();

            sp_body->setTexture(TextureManager::TextureControl.get("boulder"));
            sp_body->getSprite()->setOrigin(8,8);

            if(selectedId == 1){
                ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
            }else
            {

                delete sp_body->m_bodyShape;
                sp_body->m_bodyShape = new b2CircleShape();
                if(selectedId == 2){
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_8"));
                    sp_body->m_bodyShape->m_radius = 4/pixelsPerMeter;
                } else
                if(selectedId == 3) {
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_16"));
                    sp_body->m_bodyShape->m_radius = 8/pixelsPerMeter;
                } else
                if(selectedId == 4) {
                    sp_body->setTexture(TextureManager::TextureControl.get("boulder_32"));
                    sp_body->m_bodyShape->m_radius = 16/pixelsPerMeter;
                }
                ((b2CircleShape*)sp_body->m_bodyShape)->m_p.Set(0,0);
            }



            sp_body->getBodyDef()->position.Set((0)/pixelsPerMeter, (530)/pixelsPerMeter);
            sp_body->getBodyDef()->type = b2_dynamicBody;

            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float velX = mouse.x - sp_body->getBodyDef()->position.x;
            float velY = mouse.y - sp_body->getBodyDef()->position.y*pixelsPerMeter;

            sp_body->getBodyDef()->linearVelocity.Set(velX/pixelsPerMeter, velY/pixelsPerMeter);
            sp_body->getBodyFixture()->friction = 0.5f;
            sp_body->getBodyFixture()->density = 0.1f;

            sp_body->setWorld(*world);
            sp_body->getBody()->SetFixedRotation(false);
            if(selectedId == 1){
                sp_body->getBody()->ApplyAngularImpulse(0.01f, true);
            } else{
                sp_body->getBody()->ApplyAngularImpulse(0.001f, true);
            }


            bodylist.push_back(sp_body);
        }
        else if(event.key.code == sf::Keyboard::Num1){
            selectedId = 1;
        }
        else if(event.key.code == sf::Keyboard::Num2){
            selectedId = 2;
        }
        else if(event.key.code == sf::Keyboard::Num3){
            selectedId = 3;
        }
        else if(event.key.code == sf::Keyboard::Num4){
            selectedId = 4;
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
        if(selectedId == 1)
        {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float mouseX = floor(mouse.x/16.f)*16;
            float mouseY = floor(mouse.y/16.f)*16;
            SpriteBody* sp_body = new SpriteBody();

            sp_body->setTexture(TextureManager::TextureControl.get("boulder"));
            sp_body->getSprite()->setOrigin(8,8);
            ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
            sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
            sp_body->getBodyDef()->type = b2_dynamicBody;
            sp_body->getBodyFixture()->friction = 0.5f;
            sp_body->getBodyFixture()->density = 0.1f;

            sp_body->setWorld(*world);
            sp_body->getBody()->SetFixedRotation(false);

            bodylist.push_back(sp_body);
        } else
        if(selectedId >= 2 && selectedId <= 3)
        {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float mouseX = floor(mouse.x/16.f)*16;
            float mouseY = floor(mouse.y/16.f)*16;
            SpriteBody* sp_body = new SpriteBody();

            sp_body->setTexture(TextureManager::TextureControl.get("boulder_large"));

            if(selectedId == 2){
                sp_body->getSprite()->setOrigin( 16*4/2.f , 16/2.f);
                ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(16*2.f/pixelsPerMeter,8.0f/pixelsPerMeter);
                sp_body->getBodyDef()->position.Set((16*2+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
            } else
            {
                sp_body->getSprite()->setOrigin( 16/2.f, 16*4/2.f);
                ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,16*2.f/pixelsPerMeter);
                sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (16*2+mouseY)/pixelsPerMeter);
                sp_body->setDefaultRotation(90);
            }

            sp_body->getBodyDef()->type = b2_dynamicBody;
            sp_body->getBodyFixture()->friction = 0.5f;
            sp_body->getBodyFixture()->density = 0.1f;

            sp_body->setWorld(*world);
            sp_body->getBody()->SetFixedRotation(false);

            bodylist.push_back(sp_body);
        }
        if(selectedId >= 4 && selectedId <= 5)
        {
            sf::Vector2i mouse = sf::Mouse::getPosition(window);
            float mouseX = floor(mouse.x/16.f)*16;
            float mouseY = floor(mouse.y/16.f)*16;
            SpriteBody* sp_body = new SpriteBody();

            sp_body->getSprite()->setOrigin(8,8);
            ((b2PolygonShape*)sp_body->getBodyShape())->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
            sp_body->getBodyDef()->position.Set((8+mouseX)/pixelsPerMeter, (8+mouseY)/pixelsPerMeter);
            sp_body->getBodyDef()->type = b2_dynamicBody;

            if(selectedId == 4){
                sp_body->setTexture(TextureManager::TextureControl.get("yellow"));
                sp_body->getBodyFixture()->friction = 0.9f;
                sp_body->getBodyFixture()->density = 0.6f;
            }else if(selectedId == 5){
                sp_body->setTexture(TextureManager::TextureControl.get("metal"));
                sp_body->getBodyFixture()->friction = 1.0f;
                sp_body->getBodyFixture()->density = 2.0f;
            }

            sp_body->setWorld(*world);
            sp_body->getBody()->SetFixedRotation(false);

            bodylist.push_back(sp_body);
        }
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

    Engine::EngineControl.drawRectVertex(0,550,800,20);

    sf::Vector2i mouse = sf::Mouse::getPosition(window);

    int width = 16;
    int height = 16;
    if(selectedId == 2) width = 16 * 4;
    if(selectedId == 3) height = 16 * 4;
    Engine::EngineControl.drawRectVertex( floor(mouse.x/16.f)*16, floor(mouse.y/16.f)*16, width, height, sf::Color(100,50,100,50) );

    if(isDebug)
        world->DrawDebugData();
}
