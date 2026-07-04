#pragma once

#include "Utils/ResourceManager.h"
#include <SFML/Graphics.hpp>
#include <optional>
#include <iostream>

class Game 
{
private:
	sf::RenderWindow window_;
	ResourceManager resourceManager;
	std::optional<sf::Sprite> sprite_;
	sf::Clock clock_;

	bool reverseMode_ = false;
public:
	Game();

	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();
};