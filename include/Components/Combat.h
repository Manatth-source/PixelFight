#pragma once

#include <SFML/Graphics.hpp>
#include "Player/CharacterStats.h"
#include "Components/CombatTypes.h"


class Combat
{
public:
	explicit Combat(const CharacterStats& stats);

	// Attack and cooldown timer ticks
	void update(float deltaTime);

	// isDashing — a gate from Movement, passed by the caller (Character)
	void basicAttack(bool isDashing);

	// position/lookingRight — are taken from Movement by the caller and passed here
	sf::FloatRect getHitbox(sf::Vector2f position, bool lookingRight) const;

	float getDamage() const;
	AttackTypes getType() const;

	bool hasPerformedAttack() const;
	void markHit();

private:
	AttackTypes type_;
	bool isAttacking_;
	bool hasPerformedAttack_;


	struct AttackStats {
		float damage;
		float duration;
		float timerAttack;
		float cooldown;
		float cooldownTimer;
	};

	struct CombatStats {
		AttackStats basicAttack;
		AttackStats firstSkill;
		AttackStats secondSkill;
		AttackStats ultimate;
	};

	CombatStats stats_;
};