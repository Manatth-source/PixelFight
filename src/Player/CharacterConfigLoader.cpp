#include "Player/CharacterConfigLoader.h"
#include "Utils/Logger.h"
#include <nlohmann/json.hpp>
#include <iostream>
#include <fstream>

using json = nlohmann::json;


CharacterStats CharacterConfigLoader::loadFromJson(const std::string& JsonPath) 
{
	CharacterStats stats{};

	std::ifstream fin(JsonPath);

	if (!fin.is_open()) {
		Logger::error("Couldn't open character config: " + JsonPath);
		return stats;
	}

	json data; fin >> data;

	stats.startHealth = data["startHealth"];
	stats.speed = data["speed"];
	stats.speedSit = data["speedSit"];

	stats.dashDistance = data["dashDistance"];
	stats.dashCooldown = data["dashCooldown"];

	stats.gravity = data["gravity"];
	stats.jumpStrength = data["jumpStrength"];

	stats.jumpStartDuration = data["jumpStartDuration"];
	stats.jumpLandDuration = data["jumpLandDuration"];

	stats.attackDuration = data["attackDuration"];
	stats.attackCooldown = data["attackCooldown"];
	stats.attackDamage = data["attackDamage"];

	return stats;
}