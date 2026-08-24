#pragma once

#include "Player/Character.h"


class Goblin : public Character
{
public:
	Goblin(const sf::Texture& texture, const sf::Texture& dashReadyTexture, const sf::Texture& dashReloadTexture);
};