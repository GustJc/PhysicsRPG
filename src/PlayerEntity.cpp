#include "PlayerEntity.h"

#include "Globals.h"
#include "Engine.h"
#include "SpriteBody.h"
#include "TextureManager.h"

PlayerEntity::PlayerEntity(b2World *world)
{
    m_bodyCircleShape.m_radius = 4.f/pixelsPerMeter;

    //Full sprite is 23, 20
    m_bodyShape.SetAsBox(23.0f/pixelsPerMeter,16.0f/pixelsPerMeter, b2Vec2(0, double(-2)/pixelsPerMeter), 0);

    m_bodyDef.position.Set((100)/pixelsPerMeter, (500)/pixelsPerMeter);
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.fixedRotation = true;
    m_bodyDef.userData = this;

    m_body = world->CreateBody(&m_bodyDef);

    m_fixtureDef.filter.groupIndex = -1;
    m_fixtureDef.shape = &m_bodyShape;
    m_fixtureDef.density = 0.002;

    m_body->CreateFixture(&m_fixtureDef);

    m_fixtureDef.shape = &m_bodyCircleShape;
    m_fixtureDef.density = 0.001;
    m_fixtureDef.friction = 0;

    m_bodyCircleShape.m_p.Set( double(6-23)/pixelsPerMeter,double(20-4)/pixelsPerMeter);
    m_body->CreateFixture(&m_fixtureDef);

    m_bodyCircleShape.m_p.Set( double(23-10)/pixelsPerMeter,double(20-4)/pixelsPerMeter);
    m_body->CreateFixture(&m_fixtureDef);
}

void PlayerEntity::events(sf::Event &event){
    if(event.type == sf::Event::KeyPressed)
    {
        if(event.key.code == sf::Keyboard::Left)
            m_keyState |= KEY_LEFT;
        else
        if(event.key.code == sf::Keyboard::Right)
            m_keyState |= KEY_RIGHT;
        else
        if(event.key.code == sf::Keyboard::Up)
            m_keyState |= KEY_UP;
    }
    else
    if(event.type == sf::Event::KeyReleased)
    {
        if(event.key.code == sf::Keyboard::Left)
            m_keyState &= ~KEY_LEFT;
        else
        if(event.key.code == sf::Keyboard::Right)
            m_keyState &= ~KEY_RIGHT;
        else
        if(event.key.code == sf::Keyboard::Up)
            m_keyState &= ~KEY_UP;
    }

    if(event.type == sf::Event::MouseButtonPressed && shotTimer.getElapsedTime().asSeconds() > shot_cooldown)
    {
        shotTimer.restart();
        sf::Vector2i mouseTemp = sf::Mouse::getPosition(Engine::EngineControl.getWindowReference());
        sf::Vector2f mouse = Engine::EngineControl.getWindowReference().mapPixelToCoords(mouseTemp);

        sf::Vector2f diff = mouse - this->m_animation.getSprite().getPosition();

        cout << diff.x << " | " << diff.y << endl;
        //Arrow
        SpriteBody* shot = new SpriteBody();

        shot->setTexture(TextureManager::TextureControl.get("boulder_8"));
        shot->getSprite()->setOrigin(4,4);
        shot->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;

        shot->getBodyDef()->position.Set(
                    (this->m_animation.getSprite().getPosition().x)/pixelsPerMeter,
                    (this->m_animation.getSprite().getPosition().y)/pixelsPerMeter
                    );
        shot->getBodyDef()->type = b2_dynamicBody;
        shot->getBodyFixture()->friction = 0.5f;
        shot->getBodyFixture()->restitution = 0.2f;
        shot->getBodyFixture()->density = 2.f;
        shot->getBodyFixture()->filter.groupIndex = -1;

        shot->createBody(*Engine::world, true);

        shot->getBody()->SetFixedRotation(false);
        shot->getBody()->SetAngularDamping(0.8f);
        shot->getBody()->ApplyLinearImpulse(b2Vec2( shot->getBody()->GetMass()*diff.x/pixelsPerMeter,
                                                    shot->getBody()->GetMass()*diff.y/pixelsPerMeter  ),shot->getBody()->GetWorldCenter(),true);

        Engine::bodylist.push_back(shot);
        //End arrow

    }
}

void PlayerEntity::render(sf::RenderWindow &window)
{
    Entity::render(window);

    if(shotTimer.getElapsedTime().asSeconds() < shot_cooldown) {
        int startX = m_animation.getSprite().getPosition().x - m_animation.getSprite().getTextureRect().width/2.f;
        int startY = m_animation.getSprite().getPosition().y - 10 - m_animation.getSprite().getTextureRect().height/2.f;
        int width  = m_animation.getSprite().getTextureRect().width;
        int height = 4;

        float percent = shotTimer.getElapsedTime().asSeconds()/shot_cooldown;

        Engine::EngineControl.drawRectVertex(startX, startY,
                               width*percent, height, sf::Color(0,0,0,100) );

        Engine::EngineControl.drawLine(startX         , startY        , startX+width      , startY, sf::Color::Black);
        Engine::EngineControl.drawLine(startX+width   , startY+height , startX            , startY+height, sf::Color::Black);
        Engine::EngineControl.drawLine(startX+width   , startY+height , startX+width      , startY, sf::Color::Black);
        Engine::EngineControl.drawLine(startX         , startY+height , startX            , startY       , sf::Color::Black);
    }
}

void PlayerEntity::update(float dt)
{
    Entity::update(dt);

    int move = m_keyState & (KEY_LEFT|KEY_RIGHT);
    float desiredVel = 0;
    b2Vec2 vel = m_body->GetLinearVelocity();
    bool isStop = false;
    switch ( move )
    {
    case KEY_LEFT:
        if(vel.x > 0) isStop = true;
        desiredVel = b2Max( vel.x - 0.1f, -2.0f ); break;//desiredVel = -5; break;
    case KEY_RIGHT:
        if(vel.x < 0) isStop = true;
        desiredVel = b2Min( vel.x + 0.1f,  2.0f ); break;//desiredVel =  5; break;
    default:
        isStop = true;
    }

    if(isStop){
        if(vel.x > 0)
            desiredVel = b2Max( vel.x - 0.2f, 0.0f );
        else if(vel.x < 0)
            desiredVel = b2Min( vel.x + 0.2f,  0.0f );
    }

    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;

    m_body->ApplyLinearImpulse( b2Vec2(impulse,0), m_body->GetWorldCenter(), true );

    if(m_keyState & (KEY_UP))
    {
        m_body->ApplyLinearImpulse(b2Vec2(0,-0.001f), m_body->GetWorldCenter(), true);
    }

}
