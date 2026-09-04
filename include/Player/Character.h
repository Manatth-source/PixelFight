#pragma once

#include <SFML/Graphics.hpp>
#include <optional>
#include "Player/CharacterStats.h"
#include "Components/Movement.h"
#include "Core/Constants.h"
#include "Graphics/Animation.h"
#include "Utils/ResourceManager.h"


class Character
{
private:
	// Update
	void updateAnimationState();

	void updateSpritePosition();

	//Shild
	void breakShield();

protected:
	const ResourceManager& resourceManager_;

	std::optional<sf::Sprite> sprite_;
	void initializeSprite();

	Animation animation_;
	Movement movement_;

	float health_;
	bool isAlive_;

	//Attack
	enum class AttackTypes {
		basicAttack,
		firstSkill,
		secondSkill,
		ultimate
	};

	AttackTypes attackTypes_;
	sf::RectangleShape attackHitbox_;
	bool isAttacking_;
	bool hasPerformedAttack_;
	float attackTimer_;
	float attackDuration_;
	float attackCooldown_;
	float attackCooldownTimer_;
	float attackDamage_;

	//Shild
	enum class ShildPhase {
		None,
		Active
	};

	ShildPhase shildPhase_;
	float shildCooldown_;
	float shildCooldownTimer_;

public:

	Character(const ResourceManager& resourceManager, const CharacterStats& stats);
	virtual ~Character() = default;

	void update(float deltaTime);

	virtual void render(sf::RenderWindow& window);

	void setPosition(float x, float y);

	// Move
	void moveLeft(float deltaTime);
	void moveRight(float deltaTime);

	// Dash
	virtual void dashLeft();
	virtual void dashRight();
	bool isDashReady() const;

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
	AttackTypes getAttackTypes() const;

	void basicAttack();
#if 0
	virtual void passive_skill() = 0;
	virtual void first_skill() = 0;
	virtual void second_skill() = 0;
	virtual void ultimate() = 0;
#endif

	sf::FloatRect getAttackHitbox() const;
	sf::FloatRect getBodyBounds() const;

	bool hasPerformedAttack() const;
	void markHit();

	void takeDamage(float value, AttackTypes attackerType);
	//---
	bool isAlive() const;
	//---

};