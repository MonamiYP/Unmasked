#include "AssetManager.hpp"

AssetManager::AssetManager(Manager* m_manager) 
: manager(m_manager) {}
AssetManager::~AssetManager() {}

void AssetManager::addTexture(std::string id, const char* path) {
    textures.emplace(id, TextureManager::loadTexture(path));
}

SDL_Texture* AssetManager::getTexture(std::string id) {
    return textures[id];
}