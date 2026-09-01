#include "Player/Goblin.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Goblin::Goblin(const ResourceManager& resourceManager) : Character(resourceManager, CharacterConfigLoader::loadFromJson("Assets/Configs/Goblin_Stats.json"))
{
	sprite_.emplace(resourceManager_.getTexture("Assets/Sprites/Goblin/Goblin.png"));
	initializeSprite();

	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Goblin/Goblin.json");
	animation_.play("Idle");
}