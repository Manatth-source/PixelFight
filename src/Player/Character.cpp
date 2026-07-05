#include "Player/Character.h"
#include <iostream>

Character::Character(const sf::Texture& texture)
	: sprite_(texture)
	, position_(0.f, 180.f)
	, health_(100)
	, speed_(200.f)
	, dashCooldown_(2.0f)
	, dashCooldownTimer_(0.0f)
{
	sprite_->setScale({ 0.3f, 0.3f });
	sprite_->setPosition(position_);

	dashIndicator_.setSize({ 70.f, 70.f });
	dashIndicator_.setFillColor(sf::Color::Green);
	dashIndicator_.setPosition({ 50.f, 600.f });
}

Character::~Character() 
{
}

void Character::render(sf::RenderWindow& window) 
{
	window.draw(*sprite_);
	window.draw(dashIndicator_);
}

void Character::moveLeft(float deltaTime) 
{
	position_.x = (position_.x - speed_ * deltaTime > 0 ? position_.x - speed_ * deltaTime : 0);
	sprite_->setPosition(position_);
}

void Character::moveRight(float deltaTime) 
{
	position_.x = (position_.x + speed_ * deltaTime < 1200 ? position_.x + speed_ * deltaTime : 1200);
	sprite_->setPosition(position_);
}

void Character::dashLeft()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x -= 100.f;

	if (position_.x < 0.f)
		position_.x = 0.f;

	sprite_->setPosition(position_);
	dashCooldownTimer_ = dashCooldown_;

	std::cout << "Left_Dash - position: " << position_.x << std::endl;
}

void Character::dashRight()
{
	if (dashCooldownTimer_ > 0.f) {
		return;
	}

	position_.x += 100.f;

	if (position_.x > 1220.f)
		position_.x = 1220.f;

	sprite_->setPosition(position_);
	dashCooldownTimer_ = dashCooldown_;

	std::cout << "Right_Dash - position: " << position_.x << std::endl;

}

void Character::updateCooldowns(float deltaTime) {
	if (dashCooldownTimer_ > 0.f) {
		dashCooldownTimer_ -= deltaTime;
		dashIndicator_.setFillColor(sf::Color::Red);
	}
	else {
		dashIndicator_.setFillColor(sf::Color::Green);
	}
}