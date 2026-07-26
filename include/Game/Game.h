#pragma once

#include <SFML/Graphics.hpp>
#include <memory>
#include "Utils/ResourceManager.h"
#include "Player/Samurai.h"
#include "Player/Goblin.h"
#include "Core/Constants.h"


class Game
{
private:
	sf::RenderWindow window_;
	sf::RectangleShape ground_;
	sf::Clock clock_;
	ResourceManager resourceManager_;
	std::unique_ptr<Character> player_;

public:
	Game();

	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();
};