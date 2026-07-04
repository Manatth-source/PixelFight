#include "Utils/ResourceManager.h"
#include <iostream>

sf::Texture& ResourceManager::getTexture(const std::string& filepath) {
	auto it = textures_.find(filepath); //{ key; value } or .end()
	if (it != textures_.end())
		return it->second;
	
	sf::Texture texture;
	if(!texture.loadFromFile(filepath)) std::cout << "Couldn't load texture: " << filepath << std::endl;;
	textures_[filepath] = std::move(texture);

	return textures_[filepath];
}