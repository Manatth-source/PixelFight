#include "Player/Character.h"

Character::Character(const sf::Texture& texture)
	: sprite_(texture)
	, position_(0.f, 0.f)
	, health_(100)
{
}

Character::~Character() 
{
}

void Character::render(sf::RenderWindow& window) 
{
	window.draw(*sprite_);
}