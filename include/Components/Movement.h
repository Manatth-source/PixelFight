#pragma once

#include <SFML/Graphics.hpp>
#include "Player/CharacterStats.h"

// Movement owns everything related to character movement: position, speed (walking/crouching), look direction, dash, and jump.
class Movement
{
public:
	enum class DashPhase
	{
		None,
		Start,
		Move,
		End
	};

	enum class JumpPhase
	{
		None,
		Start,
		Loop,
		Land
	};

private:
	void updateDash(float deltaTime);
	void updateJumpPhysics(float deltaTime);
	void performDash();

	sf::Vector2f position_;
	float groundY_;

	float baseSpeed_;
	float speedSit_;
	float speed_;

	bool isLookingRight_;
	bool isMoving_;
	bool isCrouching_;

	// Dash
	DashPhase dashPhase_;
	bool dashToRight_;
	float dashTimer_;
	float dashDistance_;
	float dashCooldown_;
	float dashCooldownTimer_;

	// Jump
	JumpPhase jumpPhase_;
	float verticalVelocity_;
	bool isOnGround_;
	float gravity_;
	float jumpStrength_;
	float jumpStartTimer_;
	float jumpStartDuration_;
	float jumpLandTimer_;
	float jumpLandDuration_;

public:
	explicit Movement(sf::Vector2f startPosition, float groundY, const CharacterStats& stats);

	// Update: runs the dash, jump physics, dash cooldown timer, and recalculates speed_
	void update(float deltaTime);

	// Move
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	// Dash
	void dashLeft();
	void dashRight();
	bool isDashReady() const;

	// Jump
	void jump();

	// Crouch / Moving flags (controlled externally, Character forwards them here)
	void setCrouching(bool crouching);

	void setPosition(sf::Vector2f position);


	sf::Vector2f getPosition() const;
	bool isLookingRight() const;
	bool isMoving() const;
	bool isCrouching() const;
	bool isDashing() const;

	DashPhase getDashPhase() const;
	JumpPhase getJumpPhase() const;
};