#include "Shot.h"

#include "TextureManager.h"
#include "Globals.h"
#include "Engine.h"

Shot::Shot(int id, float px, float py, b2Vec2 force, int limit)
{
    name = "shot";
    type = id;

    if(id == 1)
    {
        this->setTexture(TextureManager::TextureControl.get("boulder_8"));
        this->getSprite()->setOrigin(4,4);
        this->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;

        this->getBodyDef()->position.Set(
                    px,
                    py
                    );
        this->getBodyDef()->type = b2_dynamicBody;
        this->getBodyFixture()->friction = 0.5f;
        this->getBodyFixture()->restitution = 0.4f;
        this->getBodyFixture()->density = 2.f;
        this->getBodyFixture()->filter.groupIndex = -1;
        this->m_bodyDef.fixedRotation = false;
        this->m_bodyDef.angularDamping = 2.5f;

        Engine::bodylist.push_back(this);
    }
    else if(id == 2)
    {
        this->setTexture(TextureManager::TextureControl.get("boulder_8"));
        this->getSprite()->setOrigin(4,4);
        this->m_bodyCircleShape.m_radius = 4/pixelsPerMeter;

        this->getBodyDef()->position.Set(
                    px-2,
                    0
                    );
        this->getBodyDef()->type = b2_dynamicBody;
        this->getBodyFixture()->friction = 0.5f;
        this->getBodyFixture()->restitution = 0.4f;
        this->getBodyFixture()->density = 2.f;
        this->getBodyFixture()->filter.groupIndex = -1;
        this->m_bodyDef.fixedRotation = false;
        this->m_bodyDef.angularDamping = 2.5f;

        if(limit < 8){
            Shot* shot = new Shot(2, px+0.1f, py, force, limit+1);
            shot->getBodyFixture()->filter.groupIndex = 1;
            shot->createBody(*Engine::world, true);

            shot->getBody()->ApplyLinearImpulse(force ,shot->getBody()->GetWorldCenter(),true);
        }

        Engine::bodylist.push_back(this);
    }
}

void Shot::update(float dt)
{
    if(m_body->IsAwake() == false){
        isDelete = true;
    }

    SpriteBody::update(dt);
}
