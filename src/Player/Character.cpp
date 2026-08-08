#include "Player/Character.h"
#include <iostream>
#include <algorithm>
#include "Utils/Logger.h"


//--------------------------------------------------------------------------

Character::Character(const sf::Texture& texture, const CharacterStats& stats)
	: sprite_(texture)
	, animation_(*sprite_)
	, position_({ Constants::Player::PositionX, Constants::Player::PositionY })
	, health_(stats.startHealth)
	, isAlive_(true)
	, baseSpeed_(stats.speed)
	, speed_(stats.speed)
	, speedSit_(stats.speedSit)
	, dashDistance_(stats.dashDistance)
	, dashCooldown_(stats.dashCooldown)
	, dashCooldownTimer_(0.0f)
	, verticalVelocity_(0.f)
	, isOnGround_(true)
	, groundY_(Constants::Player::PositionY)
	, gravity_(stats.gravity)
	, jumpStrength_(stats.jumpStrength)
	, isAttacking_(false)
	, attackTimer_(0.f)
	, attackDuration_(stats.attackDuration)
	, attackCooldown_(stats.attackCooldown)
	, attackCooldownTimer_(0.f)
	, attackDamage_(stats.attackDamage)
	, hasPerformedAttack_(false)
	, isCrouching_(false)
	, isMoving_(false)
	, jumpPhase_(JumpPhase::None)
	, jumpStartTimer_(0.f)
	, jumpStartDuration_(stats.jumpStartDuration)
	, jumpLandTimer_(0.f)
	, jumpLandDuration_(stats.jumpLandDuration)
	, isLookingRight_(true)
{
	sprite_->setOrigin({ static_cast<float>(Constants::Player::Size) / 2.f, static_cast<float>(Constants::Player::Size) / 2.f });
	sprite_->setScale({ Constants::Player::SpriteScale, Constants::Player::SpriteScale });
	updateSpritePosition();

	dashIndicator_.setSize({ Constants::Dash::IndicatorSize, Constants::Dash::IndicatorSize });
	dashIndicator_.setFillColor(sf::Color::Green);
	dashIndicator_.setPosition({ Constants::Dash::IndicatorXPlayer1, Constants::Dash::IndicatorY });
}

//--------------------------------------------------------------------------

Character::~Character() 
{
}

//--------------------------------------------------------------------------
//--------------- Update ---------------

// private
void Character::updateAnimationState()
{
	if (!isAlive_) {
		speed_ = 0;
		animation_.play("Dead");
		return;
	}
	else if (isCrouching_ && jumpPhase_ == JumpPhase::None) {
		speed_ = speedSit_;
		animation_.play("Sit");
		return;
	}

	speed_ = baseSpeed_;

	if (jumpPhase_ == JumpPhase::Start) {
		animation_.play("Jump_Start");
	}
	else if (jumpPhase_ == JumpPhase::Loop) {
		animation_.play("Jump_Loop");
	}
	else if (jumpPhase_ == JumpPhase::Land) {
		animation_.play("Jump_Land");
	}
	else if (isMoving_) {
		animation_.play("Walk");
	}
	else {
		animation_.play("Idle");
	}
}


void Character::updateCooldowns(float deltaTime)
{
	//Dach
	if (dashCooldownTimer_ > 0.f) {
		dashCooldownTimer_ -= deltaTime;

		dashIndicator_.setFillColor(sf::Color::Red);
	}
	else {
		dashIndicator_.setFillColor(sf::Color::Green);
	}

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

	//Jump
	if (jumpPhase_ == JumpPhase::Start) {
		jumpStartTimer_ -= deltaTime;
		if (jumpStartTimer_ <= 0.f) {
			jumpPhase_ = JumpPhase::Loop;
		}
	}


	if (jumpPhase_ == JumpPhase::Land) {
		jumpLandTimer_ -= deltaTime;
		if (jumpLandTimer_ <= 0.f) {
			jumpPhase_ = JumpPhase::None;
		}
	}
}


void Character::updateSpritePosition() {
	sf::Vector2f center = position_ + sf::Vector2(Constants::Player::Size / 2.f, Constants::Player::Size / 2.f);
	sprite_->setPosition(center);
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
	window.draw(dashIndicator_);
}

//--------------------------------------------------------------------------

void Character::setPosition(float x, float y)
{
	position_ = { x, y };
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Move ---------------

void Character::moveLeft(float deltaTime) 
{
	position_.x = (position_.x - speed_ * deltaTime > 0 ? position_.x - speed_ * deltaTime : 0);
	setLookingRight(false);
	updateSpritePosition();
}


void Character::moveRight(float deltaTime) 
{
	position_.x = (position_.x + speed_ * deltaTime < Constants::Window::Width - Constants::Player::Size ? position_.x + speed_ * deltaTime : Constants::Window::Width - Constants::Player::Size);
	setLookingRight(true);
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Dash ---------------

void Character::dashLeft()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x = std::max(position_.x - dashDistance_, 0.f);
	updateSpritePosition();
	dashCooldownTimer_ = dashCooldown_;
}


void Character::dashRight()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x = std::min(position_.x + dashDistance_, static_cast<float>(Constants::Window::Width - Constants::Player::Size));
	updateSpritePosition();
	dashCooldownTimer_ = dashCooldown_;
}

//--------------------------------------------------------------------------
// --------------- Shild ---------------

void Character::shild()
{

}

//--------------------------------------------------------------------------
// --------------- Jump ---------------

void Character::jump()
{
	if (!isOnGround_) {
		return;
	}

	verticalVelocity_ = jumpStrength_;
	isOnGround_ = false;

	jumpPhase_ = JumpPhase::Start;
	jumpStartTimer_ = jumpStartDuration_;
}


void Character::updatePhysics(float deltaTime) 
{
	if (!isOnGround_) {
		verticalVelocity_ += gravity_ * deltaTime;
		position_.y += verticalVelocity_ * deltaTime;


		if (position_.y >= groundY_) {
			position_.y = groundY_;
			verticalVelocity_ = 0.f;
			isOnGround_ = true;
			jumpPhase_ = JumpPhase::Land;
			jumpLandTimer_ = jumpLandDuration_;
		}

		updateSpritePosition();
	}
}

//--------------------------------------------------------------------------

void Character::setCrouching(bool crouching)
{
	isCrouching_ = crouching;
}

//--------------------------------------------------------------------------
// Skills

void Character::passive_skill() 
{
}

void Character::first_skill()
{
}

void Character::second_skill()
{
}

void Character::ultimate()
{
}

// --------------- Attack ---------------

float Character::getAttackDamage() const
{
	return attackDamage_;
}


void Character::attack() 
{
	if (attackCooldownTimer_ > 0.f) {
		return;
	}

	isAttacking_ = true;
	attackTimer_ = attackDuration_;
	attackCooldownTimer_ = attackCooldown_;
	hasPerformedAttack_ = false;

	Logger::log("Attack started");
}


sf::FloatRect Character::getAttackHitbox() const
{
	if (!isAttacking_) {
		return sf::FloatRect({ 0.f, 0.f }, { 0.f, 0.f });
	}

	float hitboxX;

	if (isLookingRight_) {
		hitboxX = position_.x + Constants::Player::Size;
	}
	else {
		hitboxX = position_.x - Constants::Attack::HitboxWidth;
	}

	return sf::FloatRect({ hitboxX, position_.y }, { Constants::Attack::HitboxWidth, static_cast<float>(Constants::Player::Size) });
}


sf::FloatRect Character::getBodyBounds() const
{
	return sf::FloatRect(position_, { static_cast<float>(Constants::Player::Size), static_cast<float>(Constants::Player::Size) });
}


bool Character::hasPerformedAttack() const
{
	return hasPerformedAttack_;
}


void Character::markHit()
{
	hasPerformedAttack_ = true;
}


void Character::takeDamage(float value)
{
	this->health_ = std::max(health_ - value, 0.f);
	if (health_ == 0) isAlive_ = false;
}


bool Character::isAlive() const
{
	return isAlive_;
}

//--------------------------------------------------------------------------

void Character::setMoving(bool moving)
{
	isMoving_ = moving;
}

//--------------------------------------------------------------------------

void Character::setLookingRight(bool lookingRight)
{
	if (isLookingRight_ == lookingRight) 
		return;

	isLookingRight_ = lookingRight;

	float scaleX = isLookingRight_ ? Constants::Player::SpriteScale : -Constants::Player::SpriteScale;
	sprite_->setScale({ scaleX, Constants::Player::SpriteScale });
}

//--------------------------------------------------------------------------

void Character::setDashIndicatorPosition(float x, float y)
{
	dashIndicator_.setPosition({ x, y });
}

//--------------------------------------------------------------------------