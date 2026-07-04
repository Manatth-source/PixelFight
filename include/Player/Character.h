#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Character
{
protected:
	std::optional<sf::Sprite> sprite_;
	sf::Vector2f position_;
	int health_;

public:
	Character(const sf::Texture& texture);
	virtual ~Character();

	virtual void render(sf::RenderWindow& window);
};