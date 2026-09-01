#include "UI/DashIndicator.h"
#include "Core/Constants.h"


//--------------------------------------------------------------------------

DashIndicator::DashIndicator(const ResourceManager& resourceManager, float x, float y)
	: readySprite_(resourceManager.getTexture("Assets/Sprites/Dash/DashReady.png"))
	, reloadSprite_(resourceManager.getTexture("Assets/Sprites/Dash/DashReload.png"))
{
	const sf::Vector2f indicatorSize(
		Constants::Dash::IndicatorSize,
		Constants::Dash::IndicatorSize
	);

	readySprite_->setScale({
		indicatorSize.x / readySprite_->getTexture().getSize().x,
		indicatorSize.y / readySprite_->getTexture().getSize().y
		});

	reloadSprite_->setScale({
		indicatorSize.x / reloadSprite_->getTexture().getSize().x,
		indicatorSize.y / reloadSprite_->getTexture().getSize().y
		});

	setPosition(x, y);

	// by default, the dash is ready — the reload indicator is hidden
	reloadSprite_->setColor(sf::Color(sf::Color::Transparent));
}

//--------------------------------------------------------------------------

void DashIndicator::setPosition(float x, float y)
{
	readySprite_->setPosition({ x, y });
	reloadSprite_->setPosition({ x, y });
}

//--------------------------------------------------------------------------

void DashIndicator::update(bool isReady)
{
	if (isReady) {
		readySprite_->setColor(sf::Color::White);
		reloadSprite_->setColor(sf::Color(sf::Color::Transparent));
	}
	else {
		readySprite_->setColor(sf::Color(sf::Color::Transparent));
		reloadSprite_->setColor(sf::Color::White);
	}
}

//--------------------------------------------------------------------------

void DashIndicator::render(sf::RenderWindow& window) const
{
	window.draw(*readySprite_);
	window.draw(*reloadSprite_);
}

//--------------------------------------------------------------------------