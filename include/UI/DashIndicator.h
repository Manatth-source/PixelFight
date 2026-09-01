#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Utils/ResourceManager.h"


class DashIndicator
{
private:
	std::optional<sf::Sprite> readySprite_;
	std::optional<sf::Sprite> reloadSprite_;

public:
	DashIndicator(const ResourceManager& resourceManager, float x, float y);

	void setPosition(float x, float y);

	// isReady == true  -> showing ready
	// isReady == false -> showing reload
	void update(bool isReady);

	void render(sf::RenderWindow& window) const;
};