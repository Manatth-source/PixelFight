#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Core/Constants.h"
#include "Graphics/Animation.h"


class Character
{
private:
	void updateAnimationState();

	void takeDamage(int value);

protected:
	std::optional<sf::Sprite> sprite_;

	Animation animation_;

	sf::Vector2f position_;

	int health_;
	bool isAlive_;

	float speed_;

	float dashCooldown_;
	float dashCooldownTimer_;

	sf::RectangleShape dashIndicator_;

	// Jump
	float verticalVelocity_;	// vertical speed of character at the moment
	bool isOnGround_;
	float groundY_;
	float gravity_;				// gravity force, pixels per second
	float jumpStrength_;		// initial vertical velocity during repulsion

	//Sit
	bool isCrouching_;

	//Move
	bool isMoving_;


public:
	Character(const sf::Texture& texture);
	virtual ~Character();

	void update(float deltaTime);

	virtual void render(sf::RenderWindow& window);

	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	void dashLeft();
	void dashRight();
	void updateCooldowns(float deltaTime);

	void jump();
	void updatePhysics(float deltaTime);

	void setCrouching(bool crouching);

	virtual void passive_skill();
	virtual void first_skill();
	virtual void second_skill();
	virtual void ultimate();

	void setMoving(bool moving);
};