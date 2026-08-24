#include "Player/Samurai.h"
#include "Graphics/AnimationLoader.h"
#include "Player/CharacterConfigLoader.h"


Samurai::Samurai(const ResourceManager& resourceManager) : Character(resourceManager, CharacterConfigLoader::loadFromJson("Assets/Configs/Samurai_Stats.json"))
{
	sprite_.emplace(resourceManager_.getTexture("Assets/Sprites/Samurai/Samurai.png"));
	initializeSprite();

	AnimationLoader::loadFromJson(animation_, "Assets/Sprites/Samurai/Samurai.json");
	animation_.play("Idle");

	dashReadyIndicator_.emplace(resourceManager_.getTexture("Assets/Sprites/Dash/DashReady.png"));
	dashReloadIndicator_.emplace(resourceManager.getTexture("Assets/Sprites/Dash/DashReload.png"));
	initializeDashIndicators();
}