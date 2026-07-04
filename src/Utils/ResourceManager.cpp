#include "Utils/ResourceManager.h"


sf::Texture& ResourceManager::getTexture(const std::string& filepath) {
	return textures_[filepath];
}