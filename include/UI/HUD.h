#pragma once

#include <SFML/Graphics.hpp>
#include "UI/DashIndicator.h"
#include "Utils/ResourceManager.h"

class Character;


class HUD
{
private:
	DashIndicator dashIndicatorPlayer1_;
	DashIndicator dashIndicatorPlayer2_;


public:
	explicit HUD(const ResourceManager& resourceManager);

	void update(const Character& player1, const Character& player2);
	void render(sf::RenderWindow& window) const;
};