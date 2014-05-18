#include "TestState.h"
#include "Globals.h"
#include "TextureManager.h"
TestState::TestState(sf::RenderWindow& wnd) :
State(wnd)
{
    //ctor
}
TestState::~TestState()
{
    //dtor
}

void TestState::load(int stack)
{
    m_debug_render = new DebugRender(&window);
    m_debug_render->SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

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
    body = new BoxBody(*world);
    body->getBody()->SetAngularVelocity(100.f);

    TextureManager::TextureControl.load("catapult", "data/img/catapult-fix.png");
    sp = new sf::Sprite(TextureManager::TextureControl.get("catapult") );
    sp->setPosition(sf::Vector2f(300,100));
    sp->setTextureRect(sf::IntRect(0,0,96,96));
    sp->setOrigin(sf::Vector2f(43,43));

    an_sp.setAnimation(TextureManager::TextureControl.get("catapult"), 96, 96, 5, 100);

    TextureManager::TextureControl.load("boulder", "data/img/wood-block-lowres-16.png");
    sp_body.setTexture(TextureManager::TextureControl.get("boulder"));
    sp_body.getSprite()->setOrigin(8,8);
    //clone
    *sp_body.getBodyDef() = body->m_bodyDef;
    sp_body.getBodyDef()->position.Set(250.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    sp_body.getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
    *sp_body.getBodyFixture() = body->m_bodyFix;
    sp_body.getBodyFixture()->shape = sp_body.getBodyShape();

    sp_body.setWorld(*world);

    sp_body.getBody()->SetAngularVelocity(-2);
}

int TestState::unload()
{
    if(m_debug_render != nullptr)
        delete m_debug_render;
    if(world != nullptr)
        delete world;
    if(sp != nullptr)
        delete sp;

    return mStack;
}

eStateType TestState::update(float dt)
{
    world->Step(dt, 6, 2);

    b2Vec2 position = body->getBody()->GetPosition();

    float32 angle = body->getBody()->GetAngle();

    printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
    an_sp.update(dt);
    body->update();
    sp_body.update();
    window.draw(body->getShape() );
    sp_body.render(window);
    an_sp.render(window);
    world->DrawDebugData();


    return GST_NONE;
}

void TestState::events(sf::Event& event)
{
    if(event.type == sf::Event::KeyPressed){
        if(event.key.code == sf::Keyboard::D)
            rotation += 15;
        else if(event.key.code == sf::Keyboard::A)
            rotation -= 15;
        else if(event.key.code == sf::Keyboard::W)
            TextureManager::TextureControl.get("catapult").setSmooth(true);
        cout << rotation << endl;
        sp->setRotation(rotation);
    }
}

void TestState::render()
{

}
