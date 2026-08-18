#include "Player/Samurai.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Samurai::Samurai(const sf::Texture& texture, const sf::Texture& dashReadyTexture, const sf::Texture& dashReloadTexture) : Character(texture, dashReadyTexture, dashReloadTexture, CharacterConfigLoader::loadFromJson("Assets/Configs/Samurai_Stats.json"))
{
	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Samurai/Samurai.json");
	animation_.play("Idle");
}