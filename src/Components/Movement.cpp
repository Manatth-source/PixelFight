#include "Components/Movement.h"
#include "Core/Constants.h"
#include <algorithm>

//--------------------------------------------------------------------------

Movement::Movement(sf::Vector2f startPosition, float groundY, const CharacterStats& stats)
	: position_(startPosition)
	, groundY_(groundY)
	, baseSpeed_(stats.speed)
	, speedSit_(stats.speedSit)
	, speed_(stats.speed)
	, isLookingRight_(true)
	, isMoving_(false)
	, isCrouching_(false)
	, dashPhase_(DashPhase::None)
	, dashToRight_(true)
	, dashTimer_(0.f)
	, dashDistance_(stats.dashDistance)
	, dashCooldown_(stats.dashCooldown)
	, dashCooldownTimer_(0.f)
	, jumpPhase_(JumpPhase::None)
	, verticalVelocity_(0.f)
	, isOnGround_(true)
	, gravity_(stats.gravity)
	, jumpStrength_(stats.jumpStrength)
	, jumpStartTimer_(0.f)
	, jumpStartDuration_(stats.jumpStartDuration)
	, jumpLandTimer_(0.f)
	, jumpLandDuration_(stats.jumpLandDuration)
{
}

//--------------------------------------------------------------------------
// --------------- Update ---------------

void Movement::update(float deltaTime)
{
	isMoving_ = false;
	updateDash(deltaTime);
	updateJumpPhysics(deltaTime);

	if (dashCooldownTimer_ > 0.f)
		dashCooldownTimer_ -= deltaTime;

	speed_ = isCrouching_ ? speedSit_ : baseSpeed_;

	if (jumpPhase_ == JumpPhase::Start) {
		jumpStartTimer_ -= deltaTime;
		if (jumpStartTimer_ <= 0.f)
			jumpPhase_ = JumpPhase::Loop;
	}

	if (jumpPhase_ == JumpPhase::Land) {
		jumpLandTimer_ -= deltaTime;
		if (jumpLandTimer_ <= 0.f)
			jumpPhase_ = JumpPhase::None;
	}
}


void Movement::updateDash(float deltaTime)
{
	if (dashPhase_ == DashPhase::None)
		return;

	dashTimer_ += deltaTime;

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
}


void Movement::updateJumpPhysics(float deltaTime)
{
	// during a horizontal dash, vertical physics is not calculated
	if (dashPhase_ != DashPhase::None)
		return;

	if (isOnGround_)
		return;

	verticalVelocity_ += gravity_ * deltaTime;
	position_.y += verticalVelocity_ * deltaTime;

	if (position_.y >= groundY_) {
		position_.y = groundY_;
		verticalVelocity_ = 0.f;
		isOnGround_ = true;
		jumpPhase_ = JumpPhase::Land;
		jumpLandTimer_ = jumpLandDuration_;
	}
}

//--------------------------------------------------------------------------
// --------------- Move ---------------

void Movement::moveLeft(float deltaTime)
{
	if (dashPhase_ != DashPhase::None)
		return;

	position_.x = (position_.x - speed_ * deltaTime > 0 ? position_.x - speed_ * deltaTime : 0);
	isLookingRight_ = false;
	isMoving_ = true;
}


void Movement::moveRight(float deltaTime)
{
	if (dashPhase_ != DashPhase::None)
		return;

	position_.x = (position_.x + speed_ * deltaTime < Constants::Window::Width - Constants::Player::Size
		? position_.x + speed_ * deltaTime
		: Constants::Window::Width - Constants::Player::Size);
	isLookingRight_ = true;
	isMoving_ = true;
}

//--------------------------------------------------------------------------
// --------------- Dash ---------------

void Movement::dashLeft()
{
	if (dashCooldownTimer_ > 0.f || dashPhase_ != DashPhase::None)
		return;

	dashPhase_ = DashPhase::Start;
	dashTimer_ = 0.f;
	dashToRight_ = false;

	dashCooldownTimer_ = dashCooldown_;
}


void Movement::dashRight()
{
	if (dashCooldownTimer_ > 0.f || dashPhase_ != DashPhase::None)
		return;

	dashPhase_ = DashPhase::Start;
	dashTimer_ = 0.f;
	dashToRight_ = true;

	dashCooldownTimer_ = dashCooldown_;
}


bool Movement::isDashReady() const
{
	return dashCooldownTimer_ <= 0.f;
}


void Movement::performDash()
{
	if (!dashToRight_)
		position_.x = std::max(position_.x - dashDistance_, 0.f);
	else
		position_.x = std::min(position_.x + dashDistance_, static_cast<float>(Constants::Window::Width - Constants::Player::Size));

	dashPhase_ = DashPhase::End;
}

//--------------------------------------------------------------------------
// --------------- Jump ---------------

void Movement::jump()
{
	if (dashPhase_ != DashPhase::None)
		return;

	if (!isOnGround_)
		return;

	verticalVelocity_ = jumpStrength_;
	isOnGround_ = false;

	jumpPhase_ = JumpPhase::Start;
	jumpStartTimer_ = jumpStartDuration_;
}

//--------------------------------------------------------------------------

void Movement::setCrouching(bool crouching)
{
	isCrouching_ = crouching;
}

void Movement::setPosition(sf::Vector2f position)
{
	position_ = position;
}

//--------------------------------------------------------------------------
// --------------- Queries ---------------

sf::Vector2f Movement::getPosition() const { return position_; }
bool Movement::isLookingRight() const { return isLookingRight_; }
bool Movement::isMoving() const { return isMoving_; }
bool Movement::isCrouching() const { return isCrouching_; }
bool Movement::isDashing() const { return dashPhase_ != DashPhase::None; }
Movement::DashPhase Movement::getDashPhase() const { return dashPhase_; }
Movement::JumpPhase Movement::getJumpPhase() const { return jumpPhase_; }