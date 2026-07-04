#pragma once 

#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>


class ResourceManager
{
private:
	std::unordered_map<std::string, sf::Texture> textures_;

public:
	sf::Texture& getTexture(const std::string& filepath);
};