#include "Utils/ResourceManager.h"


sf::Texture& ResourceManager::getTexture(const std::string& filepath) {
	auto it = textures_.find(filepath);
	if (it != textures_.end())
		return it->second;
	
	sf::Texture texture;
	texture.loadFromFile(filepath);

	textures_[filepath] = std::move(texture);
	return textures_[filepath];
}