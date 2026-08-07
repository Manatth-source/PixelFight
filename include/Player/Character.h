#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Player/CharacterStats.h"
#include "Core/Constants.h"
#include "Graphics/Animation.h"


class Character
{
private:
	// Update
	void updateAnimationState();

protected:
	std::optional<sf::Sprite> sprite_;

	Animation animation_;

	sf::Vector2f position_;

	float health_;
	bool isAlive_;

	bool isLookingRight_;

	float baseSpeed_;
	float speed_;

	//Dach
	float dashDistance_;
	float dashCooldown_;
	float dashCooldownTimer_;
	sf::RectangleShape dashIndicator_;

	// Jump
	enum class JumpPhase {
		None,
		Start,
		Loop,
		Land
	};

	JumpPhase jumpPhase_;

	float jumpStartTimer_;
	float jumpStartDuration_;

	float jumpLandTimer_;
	float jumpLandDuration_;

	float verticalVelocity_;	// vertical speed of character at the moment
	bool isOnGround_;
	float groundY_;
	float gravity_;				// gravity force, pixels per second
	float jumpStrength_;		// initial vertical velocity during repulsion

	//Sit
	bool isCrouching_;
	float speedSit_;

	//Move
	bool isMoving_;

	//Attack
	sf::RectangleShape attackHitbox_;
	bool isAttacking_;
	bool hasHitThisAttack_;
	float attackTimer_;
	float attackDuration_;
	float attackCooldown_;
	float attackCooldownTimer_;
	float attackDamage_;

public:

	Character(const sf::Texture& texture, const CharacterStats& stats);
	~Character();

	void update(float deltaTime);

	virtual void render(sf::RenderWindow& window);

	void setPosition(float x, float y);
	void updateSpritePosition();

	void setLookingRight(bool lookingRight);

	// Move
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	// Dash
	void dashLeft();
	void dashRight();

	// Udate
	void updateCooldowns(float deltaTime);

	// Jump
	void jump();
	void updatePhysics(float deltaTime);

	// Sit
	void setCrouching(bool crouching);

	// Attack
	//---
	float getAttackDamage() const;

	virtual void passive_skill();
	virtual void first_skill();
	virtual void second_skill();
	virtual void ultimate();

	void attack();
	sf::FloatRect getAttackHitbox() const;
	sf::FloatRect getBodyBounds() const;

	bool hasHitThisAttack() const;
	void markHit();

	void takeDamage(float value);
	bool isAlive() const;
	//---

	void setMoving(bool moving);
};