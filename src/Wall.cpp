#include "Wall.h"

#include "Engine.h"
#include "TextureManager.h"
#include "Globals.h"
#include "Effects.h"

#include <sstream>

Wall::Wall(int id, float px, float py)
{
    name = "wall";
    type = id;
    if(id == 1)
    {
        setTexture(TextureManager::TextureControl.get("tileset"), 16,16);
        setFixedSpritePosition(16*7, 16);
        getSprite()->setOrigin(8,8);
        m_bodyShape.SetAsBox(7.8f/pixelsPerMeter,7.8f/pixelsPerMeter);
        m_bodyDef.position.Set(px, py);
        m_bodyDef.type = b2_dynamicBody;
        m_fixtureDef.friction = 0.5f;
        m_fixtureDef.density = 0.5f;
        this->HP = 10;
    }

    Engine::bodylist.push_back(this);
}

void Wall::startContact(Body *body, b2Contact *)
{
    if(body->name == "shot")
    {
        int dano = 1;
        stringstream ss; ss << "-" << dano;

        this->damage(dano);

        SplashText* text = new SplashText(ss.str(), this->getBody()->GetPosition()+b2Vec2(0, -1), sf::Color::Red, 15, 1000);
        text->inicialImpulse = b2Vec2(1,1);

        SplashAnimation* sa = new SplashAnimation(TextureManager::TextureControl.get("explosion"), sf::Vector2i(16,16),
                                  this->getBody()->GetPosition(), 5, 100, sf::Vector2f(2.0, 2.0));
        sa->inicialImpulse = b2Vec2(0, 0); // To remove waning unused
    }
}
