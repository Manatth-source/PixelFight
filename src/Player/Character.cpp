#include "Player/Character.h"
#include <iostream>
#include <algorithm>
#include "Utils/Logger.h"


//--------------------------------------------------------------------------

Character::Character(
	const ResourceManager& resourceManager,
	const CharacterStats& stats
)
	: resourceManager_(resourceManager)
	, movement_({ Constants::Player::PositionX, Constants::Player::PositionY }, Constants::Player::PositionY, stats)
	, health_(stats.startHealth)
	, isAlive_(true)
	, isAttacking_(false)
	, attackTimer_(0.f)
	, attackDuration_(stats.attackDuration)
	, attackCooldown_(stats.attackCooldown)
	, attackCooldownTimer_(0.f)
	, attackDamage_(stats.attackDamage)
	, hasPerformedAttack_(false)
	, shildPhase_(ShildPhase::None)
	, shildCooldown_(Constants::Shild::Cooldown)
	, shildCooldownTimer_(0.f)
{
}

//--------------------------------------------------------------------------

void Character::initializeSprite()
{
	animation_.setSprite(*sprite_);
	sprite_->setOrigin({ static_cast<float>(Constants::Player::Size) / 2.f, static_cast<float>(Constants::Player::Size) / 2.f });
	sprite_->setScale({ Constants::Player::SpriteScale, Constants::Player::SpriteScale });
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Update ---------------

void Character::updateAnimationState()
{
	if (!isAlive_) {
		animation_.play("Dead");
		return;
	}
	else if (movement_.getDashPhase() == Movement::DashPhase::Start || movement_.getDashPhase() == Movement::DashPhase::End) {
		animation_.play("Dash");
		return;
	}
	else if (movement_.isCrouching() && movement_.getJumpPhase() == Movement::JumpPhase::None) {
		animation_.play("Sit");
		return;
	}

	if (movement_.getJumpPhase() == Movement::JumpPhase::Start) {
		animation_.play("Jump_Start");
	}
	else if (movement_.getJumpPhase() == Movement::JumpPhase::Loop) {
		animation_.play("Jump_Loop");
	}
	else if (movement_.getJumpPhase() == Movement::JumpPhase::Land) {
		animation_.play("Jump_Land");
	}
	else if (movement_.isMoving()) {
		animation_.play("Walk");
	}
	else if (shildPhase_ == ShildPhase::Active) {
		animation_.play("Shild");
	}
	else {
		animation_.play("Idle");
	}
}


void Character::updateCooldowns(float deltaTime)
{

	//Attack
	if (attackCooldownTimer_ > 0.f) {
		attackCooldownTimer_ -= deltaTime;
	}

	if (isAttacking_) {
		attackTimer_ -= deltaTime;
		if (attackTimer_ <= 0.f) {
			isAttacking_ = false;
		}
	}

	//Shild
	if (shildCooldownTimer_ > 0.f) {
		shildCooldownTimer_ -= deltaTime;
	}

	if (shildPhase_ == ShildPhase::Active) {
		shildPhase_ = ShildPhase::None;
	}
}


void Character::updateSpritePosition() {
	sf::Vector2f position = movement_.getPosition();
	sf::Vector2f center = position + sf::Vector2f(Constants::Player::Size / 2.f, Constants::Player::Size / 2.f);
	sprite_->setPosition(center);

	float scaleX = movement_.isLookingRight() ? Constants::Player::SpriteScale : -Constants::Player::SpriteScale;
	sprite_->setScale({ scaleX, Constants::Player::SpriteScale });
}

//--------------------------------------------------------------------------

void Character::update(float deltaTime)
{
	updateAnimationState();
	animation_.update(deltaTime);
}

//--------------------------------------------------------------------------

void Character::render(sf::RenderWindow& window)
{
	window.draw(*sprite_);
}

//--------------------------------------------------------------------------

void Character::setPosition(float x, float y)
{
	movement_.setPosition({ x, y });
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Move ---------------

void Character::moveLeft(float deltaTime)
{
	if (!isAlive_)
		return;

	movement_.moveLeft(deltaTime);
	updateSpritePosition();
}


void Character::moveRight(float deltaTime)
{
	if (!isAlive_)
		return;

	movement_.moveRight(deltaTime);
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Dash ---------------

void Character::dashLeft()
{
	movement_.dashLeft();
}


void Character::dashRight()
{
	movement_.dashRight();
}


bool Character::isDashReady() const
{
	return movement_.isDashReady();
}

//--------------------------------------------------------------------------
// --------------- Shild ---------------

void Character::shild()
{
	if (movement_.isDashing() || movement_.getJumpPhase() != Movement::JumpPhase::None)
		return;


	if (movement_.isMoving() || movement_.isCrouching())
		return;


	if (shildCooldownTimer_ > 0.f)
		return;


	shildPhase_ = ShildPhase::Active;
}

void Character::breakShield()
{
	shildPhase_ = ShildPhase::None;
	shildCooldownTimer_ = shildCooldown_;
}

//--------------------------------------------------------------------------
// --------------- Jump ---------------

void Character::jump()
{
	movement_.jump();
}


void Character::updatePhysics(float deltaTime)
{
	movement_.update(deltaTime);
	updateSpritePosition();
}

//--------------------------------------------------------------------------

void Character::setCrouching(bool crouching)
{
	movement_.setCrouching(crouching);
}

//--------------------------------------------------------------------------

// --------------- Attack ---------------

float Character::getAttackDamage() const
{
	return attackDamage_;
}


void Character::basicAttack()
{
	if (movement_.isDashing())
		return;

	if (attackCooldownTimer_ > 0.f)
		return;

	attackTypes_ = AttackTypes::basicAttack;
	isAttacking_ = true;
	attackTimer_ = attackDuration_;
	attackCooldownTimer_ = attackCooldown_;
	hasPerformedAttack_ = false;

	Logger::log("Basic attack started");
}


sf::FloatRect Character::getAttackHitbox() const
{
	if (!isAttacking_)
		return sf::FloatRect({ 0.f, 0.f }, { 0.f, 0.f });

	float halfSize = static_cast<float>(Constants::Player::Size) / 2.f;
	float newWidth = halfSize + Constants::Attack::HitboxWidth;

	sf::Vector2f position = movement_.getPosition();
	float hitboxX;


	if (movement_.isLookingRight())
		hitboxX = position.x + halfSize;
	else
		hitboxX = position.x - Constants::Attack::HitboxWidth;


	return sf::FloatRect({ hitboxX, position.y }, { newWidth, static_cast<float>(Constants::Player::Size) });
}


sf::FloatRect Character::getBodyBounds() const
{
	return sf::FloatRect(movement_.getPosition(), { static_cast<float>(Constants::Player::Size), static_cast<float>(Constants::Player::Size) });
}


bool Character::hasPerformedAttack() const
{
	return hasPerformedAttack_;
}


void Character::markHit()
{
	hasPerformedAttack_ = true;
}


void Character::takeDamage(float value, AttackTypes attackerType)
{
	if (shildPhase_ == ShildPhase::Active && attackerType != AttackTypes::basicAttack)
		return; // skill is blocked by a shield

	if (shildPhase_ == ShildPhase::Active && attackerType == AttackTypes::basicAttack)
		breakShield(); // basic attack pierces the shield


	health_ = std::max(health_ - value, 0.f);
	if (health_ == 0) isAlive_ = false;
}

Character::AttackTypes Character::getAttackTypes() const
{
	return attackTypes_;
}

//--------------------------------------------------------------------------

bool Character::isAlive() const
{
	return isAlive_;
}

//--------------------------------------------------------------------------