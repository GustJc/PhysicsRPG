#include "PlayerEntity.h"

#include "Globals.h"
#include "Engine.h"
#include "SpriteBody.h"
#include "TextureManager.h"
#include "Shot.h"
#include <math.h>

PlayerEntity* PlayerEntity::PlayerControl = nullptr;

PlayerEntity::PlayerEntity(b2World *world, float px, float py)
{
    PlayerControl = this;
    name = "player";
    this->HP = this->maxHP = 30;
    this->def = 5;
    this->atk = 5;

    this->getBodyFixture()->filter.maskBits = FilterWalls | FilterWalls | FilterNormal | FilterEnemy | FilterObjects;
    this->getBodyFixture()->filter.categoryBits= FilterPlayer;

    this->setTexture(TextureManager::TextureControl.get("player_char"), 64, 64, 1, 1);
    this->getSprite()->setScale(0.9, 0.9);
    this->m_animation.setFrames(11, 1, 200);

    this->getSprite()->setOrigin(23,20);

    arrow.setTexture(TextureManager::TextureControl.get("arrow"));
    arrow.setOrigin(0, arrow.getTextureRect().height/2.f);
    arrow_full.setTexture(TextureManager::TextureControl.get("arrow2"));
    arrow_full.setOrigin(0, arrow_full.getTextureRect().height/2.f);

    //Full sprite is 23, 20
    m_bodyShape.SetAsBox(20.0f/pixelsPerMeter,18.0f/pixelsPerMeter, b2Vec2(0, double(-2)/pixelsPerMeter), 0);

    m_bodyDef.position.Set((px)/pixelsPerMeter, (py)/pixelsPerMeter);
    m_bodyDef.type = b2_dynamicBody;
    m_bodyDef.fixedRotation = true;
    m_bodyDef.userData = this;

    m_body = world->CreateBody(&m_bodyDef);

    m_fixtureDef.shape = &m_bodyShape;
    m_fixtureDef.density = 0.002;

    m_body->CreateFixture(&m_fixtureDef);

    m_fixtureDef.shape = &m_bodyCircleShape;
    m_fixtureDef.density = 0.001;
    m_fixtureDef.friction = 0.1;

    m_bodyCircleShape.m_radius = 8.f/pixelsPerMeter;
    m_bodyCircleShape.m_p.Set( double(0)/pixelsPerMeter,double(20-4)/pixelsPerMeter);

    m_body->CreateFixture(&m_fixtureDef);

//    m_bodyCircleShape.m_p.Set( double(23-10)/pixelsPerMeter,double(20-4)/pixelsPerMeter);
//    m_body->CreateFixture(&m_fixtureDef);
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
        this->m_animation.setFrames(19, 10, 70, true);

        shotTimer.restart();
        m_state = 1;
    }
}

void PlayerEntity::render(sf::RenderWindow &window)
{
    Entity::render(window);

    int startX = m_animation.getSprite().getPosition().x - m_animation.getSprite().getTextureRect().width/2.f;
    int startY = m_animation.getSprite().getPosition().y - 10 - m_animation.getSprite().getTextureRect().height/2.f;
    int width  = m_animation.getSprite().getTextureRect().width;
    int height = 4;

    if(shotTimer.getElapsedTime().asSeconds() < shot_cooldown) {

        float percent = shotTimer.getElapsedTime().asSeconds()/shot_cooldown;

        Engine::EngineControl.drawRectVertex(startX, startY,
                               width*percent, height, sf::Color(0,0,0,100) );

        Engine::EngineControl.drawLine(startX         , startY        , startX+width      , startY, sf::Color::Black);
        Engine::EngineControl.drawLine(startX+width   , startY+height , startX            , startY+height, sf::Color::Black);
        Engine::EngineControl.drawLine(startX+width   , startY+height , startX+width      , startY, sf::Color::Black);
        Engine::EngineControl.drawLine(startX         , startY+height , startX            , startY       , sf::Color::Black);
    }

    //arrow

    int posX = startX+width;
    int posY = startY + m_animation.getSprite().getTextureRect().height/2.f;

    sf::IntRect rect = arrow_full.getTextureRect();
    rect.width = arrow.getTextureRect().width*shot_power/shot_max_power;
    arrow_full.setTextureRect(rect);
    arrow.setColor(sf::Color(255, 255, 255, 150));
    arrow_full.setColor(sf::Color(255, 255, 255, 150));

    arrow_full.setPosition(posX, posY);
    arrow.setPosition(posX, posY);
    arrow.setRotation(angle);
    arrow_full.setRotation(angle);

    window.draw(arrow);
    window.draw(arrow_full);
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
        desiredVel = b2Max( vel.x - 0.1f, -2.0f );
        if(this->isNotFalling())
            this->m_animation.setFrames(9, 6, 70);
        break;//desiredVel = -5; break;
    case KEY_RIGHT:
        if(vel.x < 0) isStop = true;
        desiredVel = b2Min( vel.x + 0.1f,  2.0f );
        if(this->isNotFalling())
            this->m_animation.setFrames(11, 6, 70);
        break;//desiredVel =  5; break;
    default:
        isStop = true;
    }

    if(isStop)
    {
        if(vel.x > 0)
            desiredVel = b2Max( vel.x - 0.2f, 0.0f );
        else if(vel.x < 0)
            desiredVel = b2Min( vel.x + 0.2f,  0.0f );
    }

    if(this->m_animation.isReady())
    {
        //Atacando
        if(this->m_state == 1)
        {
            this->atira();
            m_state = 0;
        }
        this->m_animation.setFrames(11, 1);
    }

    float velChange = desiredVel - vel.x;
    float impulse = m_body->GetMass() * velChange;

    m_body->ApplyLinearImpulse( b2Vec2(impulse,0), m_body->GetWorldCenter(), true );

    if(m_keyState & (KEY_UP))
    {
        if(this->isNotFalling())
        {
            this->m_animation.setFrames(3, 7, 100, true);
            m_body->ApplyForce( b2Vec2(0,-300*m_body->GetMass() ), m_body->GetWorldCenter(), true );
        }
    }

    //Update throw force
    sf::Vector2i mouseTemp = sf::Mouse::getPosition(Engine::EngineControl.getWindowReference());
    sf::Vector2f mouse = Engine::EngineControl.getWindowReference().mapPixelToCoords(mouseTemp);

    sf::Vector2f diff = mouse - this->m_animation.getSprite().getPosition();


    power = b2Vec2(diff.x, diff.y);

    shot_power = power.Length();
    if(shot_power > shot_max_power) shot_power = shot_max_power;

    angle = atan( diff.y/diff.x ) * 180.f/M_PI;
    if(diff.x < 0) angle = -angle;

    //Update camera
    sf::View& view = Engine::EngineControl.getViewGame();
    view.setCenter(sf::Vector2f(m_animation.getSprite().getPosition().x + WINDOW_WIDTH/4.f,
                                m_animation.getSprite().getPosition().y - WINDOW_HEIGHT/4.f  ) );
    Engine::EngineControl.getWindowReference().setView(view);

}

void PlayerEntity::atira()
{
    //Arrow
    float powerX = shot_power*cos(angle*M_PI/180.f);
    float powerY = shot_power*sin(angle*M_PI/180.f);


    Shot* shot = new Shot(selectedShot,
                          (this->m_animation.getSprite().getPosition().x)/pixelsPerMeter,
                          (this->m_animation.getSprite().getPosition().y)/pixelsPerMeter,
                          b2Vec2( powerX/pixelsPerMeter,
                                  powerY/pixelsPerMeter) );
    shot->createBody(*Engine::world, true);

    shot->getBody()->ApplyLinearImpulse(b2Vec2( shot->getBody()->GetMass()*powerX/pixelsPerMeter,
                                                shot->getBody()->GetMass()*powerY/pixelsPerMeter  ),shot->getBody()->GetWorldCenter(),true);
    //End arrow
}

bool PlayerEntity::isNotFalling()
{
    return this->m_body->GetLinearVelocity().y <= 0.00001 && this->m_body->GetLinearVelocity().y >= -0.00001;
}
