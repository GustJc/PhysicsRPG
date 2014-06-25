#include "Animation.h"
#include <iostream>
using namespace std;
Animation::Animation()
{
    //ctor
    current_time = 0;
    is_pause = false;
    is_ready = false;
    stop_last = false;
    current_frame = 0;
    current_indice = 0;
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

void Animation::setFrames(unsigned int clipY, unsigned int n_frame, unsigned int uDelay, bool onlyOnce)
{
    current_indice = clipY;
    m_sprite.setTextureRect(sf::IntRect(current_frame*frame_sizeX, current_indice*frame_sizeY, frame_sizeX, frame_sizeY));
    if(uDelay != 0) //If zero, stays the same
        this->change_time = uDelay*0.001f;
    max_frames = n_frame;
    stop_last = onlyOnce;
    is_ready = false;
}

void Animation::update(float dt)
{
    m_sprite.setOrigin(frame_sizeX/2, frame_sizeY/2);
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
        m_sprite.setTextureRect(sf::IntRect(current_frame*frame_sizeX, current_indice*frame_sizeY, frame_sizeX, frame_sizeY));
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
    m_sprite.setTextureRect(sf::IntRect(current_frame*frame_sizeX, current_indice*frame_sizeY, frame_sizeX, frame_sizeY));
    m_sprite.setOrigin(frame_sizeX/2, frame_sizeY/2);
    current_time = 0;
}
bool Animation::isReady()
{
    return is_ready;
}

void Animation::pauseAnimation(int frame_id)
{
    is_pause = true;
    if(frame_id != -1)
        current_frame = frame_id;
}

void Animation::setFixed(int x, int y)
{
    m_sprite.setTextureRect(sf::IntRect(x,y,frame_sizeX, frame_sizeY) );
    is_pause = true;
}

