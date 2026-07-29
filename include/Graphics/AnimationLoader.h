#pragma once 

#include "Graphics/Animation.h"


class AnimationLoader 
{
public:
	static void loadFromJson(Animation& animation, const std::string& JsonPath);
};