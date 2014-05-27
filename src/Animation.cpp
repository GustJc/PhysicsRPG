#include "Animation.h"
#include <iostream>
using namespace std;
Animation::Animation()
{
    //ctor
    current_time = 0;
    is_pause = false;
    is_ready = false;
    current_frame = 0;
}

Animation::~Animation()
{
    //dtor
}

void Animation::setAnimation(sf::Texture& tex, int frameSizeX, int frameSizeY, int nFrames, int msTime)
{
    m_sprite.setTexture(tex);
    this->frame_sizeX = frameSizeX;
    this->frame_sizeY = frameSizeY;
    this->max_frames = nFrames;
    this->change_time = msTime*0.001f;
    forceFrame(0);
}

void Animation::update(float dt)
{
    if(is_pause)
        return;

    is_ready = false;
    current_time += dt;
    // Se passou o tempo, atualiza frame
    if(current_time >= change_time)
    {
        current_time -= change_time;
        current_frame += 1;
        if(current_frame >= max_frames)
        {
            is_ready = true;
            current_frame -= max_frames;
        }
        m_sprite.setTextureRect(sf::IntRect(current_frame*frame_sizeX, 0, frame_sizeX, frame_sizeY));
        m_sprite.setOrigin(frame_sizeX/2, frame_sizeY/2);
    }
}
void Animation::render(sf::RenderWindow& window)
{
    window.draw(m_sprite);
}

void Animation::forceFrame(int frame_id)
{
    if(frame_id == -1){
        current_frame = max_frames-1;
    } else {
        current_frame = frame_id;
    }

    m_sprite.setTextureRect(sf::IntRect(current_frame*frame_sizeX, 0, frame_sizeX, frame_sizeY));
    m_sprite.setOrigin(frame_sizeX/2, frame_sizeY/2);
    current_time = 0;
}
bool Animation::isReady()
{
    return is_ready;
}

