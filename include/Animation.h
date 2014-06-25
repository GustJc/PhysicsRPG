#ifndef ANIMATION_H
#define ANIMATION_H

#include <SFML/Graphics.hpp>

class Animation
{
    public:
        Animation();
        virtual ~Animation();

        void setAnimation(sf::Texture& tex, int frameSizeX, int frameSizeY, int nFrames = 1, int msTime = 0);
        void setFrames(unsigned int clipY, unsigned int n_frame=1, unsigned int uDelay = 0, bool onlyOnce = false);

        void update(float dt);
        void render(sf::RenderWindow& window);

        void forceFrame(int frame_id);

        bool isReady();
        void pauseAnimation(int frame_id = -1);

        void setFixed(int x, int y);

        sf::Sprite& getSprite() { return m_sprite;}
    protected:
        sf::Sprite m_sprite;
        float current_time;
        float change_time;
        int current_frame;
        int current_indice;
        int max_frames;
        bool stop_last;
        bool is_ready;
        bool is_pause;
        int frame_sizeX;
        int frame_sizeY;

    private:
};

#endif // ANIMATION_H
