#include "Player/Wizard.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Wizard::Wizard(const sf::Texture& texture) : Character(texture, CharacterConfigLoader::loadFromJson("Assets/Configs/Wizard_Stats.json"))
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Wizard/Wizard.json");
	animation_.play("Idle");
}