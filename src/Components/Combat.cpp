#include "Components/Combat.h"
#include "Core/Constants.h"
#include "Utils/Logger.h"


//--------------------------------------------------------------------------

Combat::Combat(const CharacterStats& stats)
	: type_(AttackTypes::basicAttack)
	, isAttacking_(false)
	, hasPerformedAttack_(false)
	, stats_{
		{ stats.attackDamage, stats.attackDuration, 0.f, stats.attackCooldown, 0.f }, // basicAttack
		{}, // firstSkill
		{}, // secondSkill
		{}  // ultimate
	}
{
}

//--------------------------------------------------------------------------

void Combat::update(float deltaTime)
{
	if (stats_.basicAttack.cooldownTimer > 0.f) {
		stats_.basicAttack.cooldownTimer -= deltaTime;
	}

	if (isAttacking_) {
		stats_.basicAttack.timerAttack -= deltaTime;
		if (stats_.basicAttack.timerAttack <= 0.f) {
			isAttacking_ = false;
		}
	}
}

//--------------------------------------------------------------------------

void Combat::basicAttack(bool isDashing)
{
	if (isDashing)
		return;

	if (stats_.basicAttack.cooldownTimer > 0.f)
		return;

	type_ = AttackTypes::basicAttack;
	isAttacking_ = true;
	stats_.basicAttack.timerAttack = stats_.basicAttack.duration;
	stats_.basicAttack.cooldownTimer = stats_.basicAttack.cooldown;
	hasPerformedAttack_ = false;

	Logger::log("Basic attack started");
}

//--------------------------------------------------------------------------

sf::FloatRect Combat::getHitbox(sf::Vector2f position, bool lookingRight) const
{
	if (!isAttacking_)
		return sf::FloatRect({ 0.f, 0.f }, { 0.f, 0.f });

	float halfSize = static_cast<float>(Constants::Player::Size) / 2.f;
	float newWidth = halfSize + Constants::Attack::HitboxWidth;

	float hitboxX;

	if (lookingRight)
		hitboxX = position.x + halfSize;
	else
		hitboxX = position.x - Constants::Attack::HitboxWidth;

	return sf::FloatRect({ hitboxX, position.y }, { newWidth, static_cast<float>(Constants::Player::Size) });
}

//--------------------------------------------------------------------------

float Combat::getDamage() const { return stats_.basicAttack.damage; }
AttackTypes Combat::getType() const { return type_; }
bool Combat::hasPerformedAttack() const { return hasPerformedAttack_; }

void Combat::markHit()
{
	hasPerformedAttack_ = true;
}

//--------------------------------------------------------------------------