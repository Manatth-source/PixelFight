#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Player/CharacterStats.h"
#include "Core/Constants.h"
#include "Graphics/Animation.h"
#include "Utils/ResourceManager.h"


class Character
{
private:
	// Update
	void updateAnimationState();

	//Dash
	virtual void performDash();

	//Move
	void setLookingRight(bool lookingRight);

protected:
	const ResourceManager& resourceManager_;

	std::optional<sf::Sprite> sprite_;
	void initializeSprite();

	Animation animation_;

	sf::Vector2f position_;

	float health_;
	bool isAlive_;

	bool isLookingRight_;

	float baseSpeed_;
	float speed_;

	//Dach
	enum class DashPhase
	{
		None,
		Start,
		Move,
		End
	};

	DashPhase dashPhase_;

	bool dashToRight_;
	float dashTimer_;
	float dashDistance_;
	float dashCooldown_;
	float dashCooldownTimer_;

	std::optional<sf::Sprite> dashReadyIndicator_;
	std::optional<sf::Sprite> dashReloadIndicator_;
	void initializeDashIndicators();

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
	bool hasPerformedAttack_;
	float attackTimer_;
	float attackDuration_;
	float attackCooldown_;
	float attackCooldownTimer_;
	float attackDamage_;

public:

	Character(const ResourceManager& resourceManager, const CharacterStats& stats);
	virtual ~Character() = default;

	void update(float deltaTime);

	virtual void render(sf::RenderWindow& window);

	void setPosition(float x, float y);
	void updateSpritePosition();

	// Move
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	// Dash
	virtual void dashLeft();
	virtual void dashRight();

	//Shild
	virtual void shild();

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

	bool hasPerformedAttack() const;
	void markHit();

	void takeDamage(float value);
	bool isAlive() const;
	//---

	void setMoving(bool moving);

	void setDashIndicatorPosition(float x, float y);
};