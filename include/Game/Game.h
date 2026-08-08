#pragma once

#include <SFML/Graphics.hpp>
#include "Utils/ResourceManager.h"
#include "Input/KeyboardInputSource.h"
#include "Player/Samurai.h"
#include "Player/Goblin.h"
#include "Player/Wizard.h"
#include "Core/Constants.h"
#include <memory>


class Game
{
private:
	sf::RenderWindow window_;
	sf::RectangleShape ground_;
	sf::Clock clock_;
	ResourceManager resourceManager_;

	KeyboardInputSource inputSource_;

	std::unique_ptr<Character> player1_;
	std::unique_ptr<Character> player2_;

	sf::RectangleShape victory_plaque_;

public:
	Game();

	void run();

private:
	void processEvents();
	void update(float deltaTime);
	void render();
};