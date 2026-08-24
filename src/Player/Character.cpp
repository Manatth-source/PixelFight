#include "Player/Character.h"
#include <iostream>
#include <algorithm>
#include "Utils/Logger.h"


//--------------------------------------------------------------------------

Character::Character(
	const sf::Texture& texture,
	const sf::Texture& dashReadyTexture,
	const sf::Texture& dashReloadTexture,
	const CharacterStats& stats
)
	: sprite_(texture)
	, dashReadyIndicator_(dashReadyTexture)
	, dashReloadIndicator_(dashReloadTexture)
	, animation_(*sprite_)
	, position_({ Constants::Player::PositionX, Constants::Player::PositionY })
	, health_(stats.startHealth)
	, isAlive_(true)
	, baseSpeed_(stats.speed)
	, speed_(stats.speed)
	, speedSit_(stats.speedSit)
	, dashToRight_(true)
	, dashTimer_(0.f)
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

	const sf::Vector2f indicatorSize(
		Constants::Dash::IndicatorSize,
		Constants::Dash::IndicatorSize
	);

	dashReadyIndicator_->setScale({
		indicatorSize.x / dashReadyTexture.getSize().x,
		indicatorSize.y / dashReadyTexture.getSize().y
	});

	dashReloadIndicator_->setScale({
		indicatorSize.x / dashReadyTexture.getSize().x,
		indicatorSize.y / dashReadyTexture.getSize().y
	});

	dashReadyIndicator_->setPosition({
		Constants::Dash::IndicatorXPlayer1,
		Constants::Dash::IndicatorY
	});

	dashReloadIndicator_->setPosition({
		Constants::Dash::IndicatorXPlayer1,
		Constants::Dash::IndicatorY
	});

	dashReloadIndicator_->setColor(sf::Color(255, 255, 255, 0));
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
	else if (dashPhase_ == DashPhase::Start || dashPhase_ == DashPhase::End) {
		animation_.play("Dash");
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
	//Dash
	if (dashCooldownTimer_ > 0.f) {
		dashCooldownTimer_ -= deltaTime;

		dashReadyIndicator_->setColor(sf::Color(255, 255, 255, 0));
		dashReloadIndicator_->setColor(sf::Color::White);
	}
	else {
		dashReadyIndicator_->setColor(sf::Color::White);
		dashReloadIndicator_->setColor(sf::Color(255, 255, 255, 0));
	}


	if (!(dashPhase_ == DashPhase::None)) dashTimer_ += deltaTime;


	if (dashPhase_ == DashPhase::Start && dashTimer_ >= Constants::Dash::DurationPhaseStartAndEnd) {
		dashTimer_ = 0.f;
		dashPhase_ = DashPhase::Move;
	}
	else if (dashPhase_ == DashPhase::Move) {
		performDash();
	}
	else if (dashPhase_ == DashPhase::End && dashTimer_ >= Constants::Dash::DurationPhaseStartAndEnd) {
		dashTimer_ = 0.f;
		dashPhase_ = DashPhase::None;
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
	window.draw(*dashReadyIndicator_);
	window.draw(*dashReloadIndicator_);
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

	if (dashPhase_ != DashPhase::None) {
		return;
	}

	position_.x = (position_.x - speed_ * deltaTime > 0 ? position_.x - speed_ * deltaTime : 0);
	setLookingRight(false);
	updateSpritePosition();
}


void Character::moveRight(float deltaTime) 
{

	if (dashPhase_ != DashPhase::None) {
		return;
	}

	position_.x = (position_.x + speed_ * deltaTime < Constants::Window::Width - Constants::Player::Size ? position_.x + speed_ * deltaTime : Constants::Window::Width - Constants::Player::Size);
	setLookingRight(true);
	updateSpritePosition();
}

//--------------------------------------------------------------------------
//--------------- Dash ---------------

void Character::dashLeft()
{
	if (dashCooldownTimer_ > 0.f || dashPhase_ != DashPhase::None) {
		return;
	}

	dashPhase_ = DashPhase::Start;
	dashTimer_ = 0.f;
	dashToRight_ = false;

	dashCooldownTimer_ = dashCooldown_;
}


void Character::dashRight()
{
	if (dashCooldownTimer_ > 0.f || dashPhase_ != DashPhase::None) {
		return;
	}

	dashPhase_ = DashPhase::Start;
	dashTimer_ = 0.f;
	dashToRight_ = true;

	dashCooldownTimer_ = dashCooldown_;
}


void Character::performDash()
{
	if (!dashToRight_) position_.x = std::max(position_.x - dashDistance_, 0.f);
	else position_.x = std::min(position_.x + dashDistance_, static_cast<float>(Constants::Window::Width - Constants::Player::Size));

	dashPhase_ = DashPhase::End;
	updateSpritePosition();
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
	if (dashPhase_ != DashPhase::None) {
		return;
	}

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
	if (dashPhase_ != DashPhase::None) {
		return;
	}

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
	if (dashPhase_ != DashPhase::None) {
		return;
	}

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
	dashReloadIndicator_->setPosition({ x, y });
	dashReadyIndicator_->setPosition({ x, y });
}

//--------------------------------------------------------------------------