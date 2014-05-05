#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "BoxBody.h"
#include "Globals.h"
#include "DebugRender.h"

#include "SpriteBody.h"

#include "TextureManager.h"
#include "Animation.h"
using namespace std;

int main() {

    sf::RenderWindow window(sf::VideoMode(800,600,32),"Game-Box");

    DebugRender m_debug_render(&window);
    m_debug_render.SetFlags( b2Draw::e_shapeBit | b2Draw::e_jointBit | b2Draw::e_aabbBit | b2Draw::e_pairBit | b2Draw::e_centerOfMassBit);

    b2Vec2 gravity(0.0f, 10.0f);
    bool doSleep = true;
    b2World world(gravity);
    world.SetAllowSleeping(doSleep);

    world.SetDebugDraw(&m_debug_render);

    // Chao
    b2BodyDef ground_def;
    ground_def.position.Set(0.0f, 600.0f/pixelsPerMeter);

    b2Body* m_ground = world.CreateBody(&ground_def);
    b2PolygonShape groundBox;
    groundBox.SetAsBox(50.f, 50.f/pixelsPerMeter);
    m_ground->CreateFixture(&groundBox, 0.0f);

    //Dinamico
    BoxBody body(world);
    body.getBody()->SetAngularVelocity(100.f);
/*
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position.Set(0.0f, 4.0f);
    b2Body* bbody = world.CreateBody(&bodyDef);
    b2PolygonShape dynamicBox;
    dynamicBox.SetAsBox(1.0f, 1.0f);

    b2FixtureDef fixtureDef;

    fixtureDef.shape = &dynamicBox;
    fixtureDef.density = 1.0f;
    fixtureDef.friction = 0.3f;
    bbody->CreateFixture(&fixtureDef);
*/

//TESTES
    TextureManager::TextureControl.load("catapult", "data/img/catapult-fix.png");
    sf::Sprite sp(TextureManager::TextureControl.get("catapult") );
    sp.setPosition(sf::Vector2f(300,100));
    sp.setTextureRect(sf::IntRect(0,0,96,96));
    sp.setOrigin(sf::Vector2f(43,43));

    Animation an_sp;
    an_sp.setAnimation(TextureManager::TextureControl.get("catapult"), 96, 96, 5, 100);
    int rotation = 0;

    TextureManager::TextureControl.load("boulder", "data/img/wood-block-lowres-16.png");
    SpriteBody sp_body;
    sp_body.setTexture(TextureManager::TextureControl.get("boulder"));
    sp_body.getSprite()->setOrigin(8,8);
    //clone
    *sp_body.getBodyDef() = body.m_bodyDef;
    sp_body.getBodyDef()->position.Set(250.0f/pixelsPerMeter, 0.0f/pixelsPerMeter);
    sp_body.getBodyShape()->SetAsBox(8.0f/pixelsPerMeter,8.0f/pixelsPerMeter);
    *sp_body.getBodyFixture() = body.m_bodyFix;
    sp_body.getBodyFixture()->shape = sp_body.getBodyShape();

    sp_body.setWorld(world);

    sp_body.getBody()->SetAngularVelocity(-2);

//TESTES
    window.setFramerateLimit(60);
    sf::Clock tempoDecorrido;
    while(window.isOpen())
    {
        window.clear(sf::Color(255,255,255));
        sf::Event event;
        while(window.pollEvent(event)){
            if(event.type == sf::Event::Closed){
                window.close();
            }
            if(event.type == sf::Event::KeyPressed){
                if(event.key.code == sf::Keyboard::D)
                    rotation += 15;
                else if(event.key.code == sf::Keyboard::A)
                    rotation -= 15;
                else if(event.key.code == sf::Keyboard::W)
                    TextureManager::TextureControl.get("catapult").setSmooth(true);
                cout << rotation << endl;
                sp.setRotation(rotation);
            }
        }


        float dt = tempoDecorrido.getElapsedTime().asSeconds();
        world.Step(dt, 6, 2);

        b2Vec2 position = body.getBody()->GetPosition();

        float32 angle = body.getBody()->GetAngle();

        //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        an_sp.update(dt);
        body.update();
        sp_body.update();
        window.draw(body.getShape() );
        tempoDecorrido.restart();
        window.draw(sp);
        sp_body.render(window);
        an_sp.render(window);
        world.DrawDebugData();

        window.display();

    }

    return 0;
}

