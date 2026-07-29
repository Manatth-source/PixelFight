#include "Player/Samurai.h"
#include "Graphics/AnimationLoader.h"


Samurai::Samurai(const sf::Texture& texture) : Character(texture)
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Samurai/Samurai.json");
	animation_.play("Idle");
}