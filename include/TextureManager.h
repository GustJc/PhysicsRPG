#pragma once

#include <SFML/Graphics.hpp>
#include <map>
#include <string>
#include <memory>


class TextureManager
{
    public:
        TextureManager();
        virtual ~TextureManager();

        static TextureManager TextureControl;

        void load(std::string id, const std::string& filename);
        const sf::Texture& get(std::string id) const;
        sf::Texture& get(std::string id);
    protected:
    private:
        std::map<std::string, std::unique_ptr<sf::Texture>>
            mTextureMap;
};


