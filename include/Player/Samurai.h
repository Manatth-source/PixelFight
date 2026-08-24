#pragma once

#include "Player/Character.h"


class Samurai : public Character 
{
public:
	Samurai(const sf::Texture& texture, const sf::Texture& dashReadyTexture, const sf::Texture& dashReloadTexture);
};