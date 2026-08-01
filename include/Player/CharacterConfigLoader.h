#pragma once

#include "CharacterStats.h"
#include <string>


class CharacterConfigLoader 
{
public:
	static CharacterStats loadFromJson(const std::string& JsonPath);
};