#include "TextureManager.h"
#include <stdexcept>
#include <cassert>
TextureManager::TextureManager()
{
    //ctor
}

TextureManager::~TextureManager()
{
    //dtor
}

TextureManager TextureManager::TextureControl;

void TextureManager::load(std::string id, const std::string& filename)
{
    std::unique_ptr<sf::Texture> texture(new sf::Texture());

    if(!texture->loadFromFile(filename)) {
        throw std::runtime_error("TextureManager::load - failed to load " + filename);
    }

    //auto inserted =
    mTextureMap.insert(std::make_pair(id, std::move(texture)));

    //assert(inserted.second);
}

sf::Texture& TextureManager::get(std::string id)
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
}


const sf::Texture& TextureManager::get(std::string id) const
{
    auto found = mTextureMap.find(id);
    assert(found != mTextureMap.end());

    return *found->second;
}


