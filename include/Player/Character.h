#pragma once

#include <SFML/Graphics.hpp>
#include <optional>

class Character
{
protected:
	std::optional<sf::Sprite> sprite_;
	sf::Vector2f position_;
	int health_;
	float speed_;
	float dashCooldown_;
	float dashCooldownTimer_;
	sf::RectangleShape dashIndicator_;

public:
	Character(const sf::Texture& texture);
	virtual ~Character();

	virtual void render(sf::RenderWindow& window);

	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);
	void dashLeft();
	void dashRight();
	void updateCooldowns(float deltaTime);
};