#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        void setAnimation(sf::Texture& tex, int frameSizeX, int frameSizeY, int nFrames = 1, int msTime = 0);

        void update(float dt);
        void render(sf::RenderWindow& window);

        void forceFrame(int frame_id);

        bool isReady();

        sf::Sprite& getSprite() { return m_sprite;}
    protected:
        sf::Sprite m_sprite;
        float current_time;
        float change_time;
        int current_frame;
        int max_frames;
        bool is_ready;
        bool is_pause;
        int frame_sizeX;
        int frame_sizeY;

    private:
};

#endif // ANIMATION_H
