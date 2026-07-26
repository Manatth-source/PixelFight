#include "Player/Character.h"
#include <iostream>

//--------------------------------------------------------------------------

Character::Character(const sf::Texture& texture)
	: sprite_(texture)
	, animation_(*sprite_)
	, position_({Constants::Player::PositionX, Constants::Player::PositionY})
	, health_(100)
	, speed_(Constants::Player::Speed)
	, dashCooldown_(Constants::Player::Dash_cooldown)
	, dashCooldownTimer_(0.0f)
	, verticalVelocity_(0.f)
	, isOnGround_(true)
	, groundY_(Constants::Player::PositionY)
	, gravity_(1500.f)
	, jumpStrength_(-600.f)
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
	if (isCrouching_) {
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


void Character::damage(int value) 
{
	this->health_ = std::max(health_ - value, 0);
}


//--------------------------------------------------------------------------

void Character::update(float deltaTime) {
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
	if (dashCooldownTimer_ > 0.f) {
		dashCooldownTimer_ -= deltaTime;

		dashIndicator_.setFillColor(sf::Color::Red);
	}
	else {
		dashIndicator_.setFillColor(sf::Color::Green);
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

//--------------------------------------------------------------------------

void Character::setMoving(bool moving)
{
	isMoving_ = moving;
}

//--------------------------------------------------------------------------