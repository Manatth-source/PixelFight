#include "Player/Wizard.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Wizard::Wizard(const sf::Texture& texture, const sf::Texture& dashReadyTexture, const sf::Texture& dashReloadTexture) : Character(texture, dashReadyTexture, dashReloadTexture, CharacterConfigLoader::loadFromJson("Assets/Configs/Wizard_Stats.json"))
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Wizard/Wizard.json");
	animation_.play("Idle");
}