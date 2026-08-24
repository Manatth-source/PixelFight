#include "Utils/ResourceManager.h"
#include "Utils/Logger.h"
#include <iostream>

sf::Texture& ResourceManager::getTexture(const std::string& filepath) const {
	auto it = textures_.find(filepath); //{ key; value } or .end()
	if (it != textures_.end())
		return it->second;
	
	sf::Texture texture;
	if(!texture.loadFromFile(filepath)) Logger::error("Couldn't load texture: " + filepath);
	textures_[filepath] = std::move(texture);

	return textures_[filepath];
}