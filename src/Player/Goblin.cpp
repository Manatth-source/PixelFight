#include "Player/Goblin.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Goblin::Goblin(const sf::Texture& texture) : Character(texture, CharacterConfigLoader::loadFromJson("Assets/Configs/Goblin_Stats.json"))
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Goblin/Goblin.json");
	animation_.play("Idle");
}