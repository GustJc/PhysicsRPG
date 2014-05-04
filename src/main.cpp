#include <Box2D/Box2D.h>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <stdio.h>

#include "BoxBody.h"
#include "Globals.h"
#include "DebugRender.h"
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
        }


        float dt = tempoDecorrido.getElapsedTime().asSeconds();
        world.Step(dt, 6, 2);

        b2Vec2 position = body.getBody()->GetPosition();

        float32 angle = body.getBody()->GetAngle();

        //printf("%4.2f %4.2f %4.2f\n", position.x, position.y, angle);
        body.update();
        window.draw(body.getShape() );
        world.DrawDebugData();
        tempoDecorrido.restart();
        //world.Step(dt, 6, 2);

        window.display();

    }

    return 0;
}

