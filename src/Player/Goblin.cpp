#include "Player/Goblin.h"
#include "Graphics/AnimationLoader.h"


Goblin::Goblin(const sf::Texture& texture) : Character(texture)
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Goblin/Goblin.json");
	animation_.play("Idle");
}