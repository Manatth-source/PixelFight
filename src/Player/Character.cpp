#include "Player/Character.h"
#include <iostream>

//--------------------------------------------------------------------------

Character::Character(const sf::Texture& texture)
	: sprite_(texture)
	, animation_(*sprite_)
	, position_({ Constants::Player::PositionX, Constants::Player::PositionY })
	, health_(100)
	, isAlive_(true)
	, speed_(Constants::Player::Speed)
	, dashCooldown_(Constants::Player::Dash_cooldown)
	, dashCooldownTimer_(0.0f)
	, verticalVelocity_(0.f)
	, isOnGround_(true)
	, groundY_(Constants::Player::PositionY)
	, gravity_(1500.f)
	, jumpStrength_(-600.f)
	, isAttacking_(false)
	, attackTimer_(0.f)
	, attackDuration_(0.2f)
	, attackCooldown_(1.0f)
	, attackCooldownTimer_(0.f)
	, attackDamage_(10)
{

	sprite_->setScale({ 1.1f, 1.1f });
	sprite_->setPosition(position_);
#if 0
	//Idle
	animation_.addFrame(sf::IntRect(
		{ 0, 0 },
		{ 128, 128 }
	));

	animation_.addFrame(sf::IntRect(
		{ 128, 0 },
		{ 128, 128 }
	));

	animation_.addFrame(sf::IntRect(
		{ 256, 0 },
		{ 128, 128 }
	));
//#endif
	//Walk
	animation_.addFrame(sf::IntRect(
		{ 386, 0 },
		{ 128, 128 }
	));

	animation_.addFrame(sf::IntRect(
		{ 514, 0 },
		{ 128, 128 }
	));

	animation_.addFrame(sf::IntRect(
		{ 642, 0 },
		{ 128, 128 }
	));

	animation_.addFrame(sf::IntRect(
		{ 770, 0 },
		{ 128, 128 }
	));
#endif

	// Dash Indicator
	dashIndicator_.setSize({ 50.f, 50.f });
	dashIndicator_.setFillColor(sf::Color::Green);
	dashIndicator_.setPosition({ 50.f, 500.f });


}

//--------------------------------------------------------------------------

Character::~Character() 
{
}

//--------------------------------------------------------------------------
// private

void Character::updateAnimationState() 
{
	if (!isAlive_) {
		speed_ = 0;
		animation_.play("Dead");
	}
	else if (isCrouching_) {
		speed_ = Constants::Player::SpeedSit;
		animation_.play("Sit");
	}
	else if (!isOnGround_) {
		animation_.play("Jump_Loop");
	}
	else if (isMoving_) {
		animation_.play("Walk");
	}
	else {
		animation_.play("Idle");
	}
}


//--------------------------------------------------------------------------

void Character::update(float deltaTime) 
{
	speed_ = Constants::Player::Speed;
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
	sprite_->setPosition(position_);
}

//--------------------------------------------------------------------------
//--------------- Move ---------------
void Character::moveLeft(float deltaTime) 
{
	position_.x = (position_.x - speed_ * deltaTime > 0 ? position_.x - speed_ * deltaTime : 0);
	sprite_->setPosition(position_);
}


void Character::moveRight(float deltaTime) 
{
	position_.x = (position_.x + speed_ * deltaTime < Constants::Window::Width - Constants::Player::Size ? position_.x + speed_ * deltaTime : Constants::Window::Width - Constants::Player::Size);
	sprite_->setPosition(position_);
}

//--------------------------------------------------------------------------
//--------------- Dash ---------------
void Character::dashLeft()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x = std::max(
		position_.x - Constants::Player::Dash_distance,
		0.f
	);

	sprite_->setPosition(position_);
	dashCooldownTimer_ = dashCooldown_;

}


void Character::dashRight()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x = std::min(
		position_.x + Constants::Player::Dash_distance,
		static_cast<float>(Constants::Window::Width - Constants::Player::Size)
	);

	sprite_->setPosition(position_);
	dashCooldownTimer_ = dashCooldown_;

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
		}

		sprite_->setPosition(position_);
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

//Attack

void Character::attack() 
{
	if (attackCooldownTimer_ > 0.f) {
		return;
	}

	isAttacking_ = true;
	attackTimer_ = attackDuration_;
	attackCooldownTimer_ = attackCooldown_;
	hasHitThisAttack_ = false;
}


sf::FloatRect Character::getAttackHitbox() const
{
	if (!isAttacking_) {
		return sf::FloatRect({ 0.f, 0.f }, { 0.f, 0.f });
	}

	float hitboxWidth = 60.f;
	float hitboxX = position_.x + Constants::Player::Size; // We only hit to the right !!! It needs to be finalized !!!

	return sf::FloatRect({ hitboxX, position_.y }, { hitboxWidth, static_cast<float>(Constants::Player::Size) });
}


sf::FloatRect Character::getBodyBounds() const
{
	return sf::FloatRect(position_, { static_cast<float>(Constants::Player::Size), static_cast<float>(Constants::Player::Size) });
}


bool Character::hasHitThisAttack() const
{
	return hasHitThisAttack_;
}


void Character::markHit()
{
	hasHitThisAttack_ = true;
}


void Character::takeDamage(int value)
{
	this->health_ = std::max(health_ - value, 0);
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