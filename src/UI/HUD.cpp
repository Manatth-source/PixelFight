#include "UI/HUD.h"
#include "Player/Character.h"
#include "Core/Constants.h"


//--------------------------------------------------------------------------

HUD::HUD(const ResourceManager& resourceManager)
	: dashIndicatorPlayer1_(resourceManager, Constants::Dash::IndicatorXPlayer1, Constants::Dash::IndicatorY)
	, dashIndicatorPlayer2_(resourceManager, Constants::Dash::IndicatorXPlayer2, Constants::Dash::IndicatorY)
{
}

//--------------------------------------------------------------------------

void HUD::update(const Character& player1, const Character& player2)
{
	dashIndicatorPlayer1_.update(player1.isDashReady());
	dashIndicatorPlayer2_.update(player2.isDashReady());
}

//--------------------------------------------------------------------------

void HUD::render(sf::RenderWindow& window) const
{
	dashIndicatorPlayer1_.render(window);
	dashIndicatorPlayer2_.render(window);
}

//--------------------------------------------------------------------------