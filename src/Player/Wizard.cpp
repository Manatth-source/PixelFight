#include "Player/Wizard.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Wizard::Wizard(const ResourceManager& resourceManager) : Character(resourceManager, CharacterConfigLoader::loadFromJson("Assets/Configs/Wizard_Stats.json"))
{
	sprite_.emplace(resourceManager_.getTexture("Assets/Sprites/Wizard/Wizard.png"));
	initializeSprite();

	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Wizard/Wizard.json");
	animation_.play("Idle");
}