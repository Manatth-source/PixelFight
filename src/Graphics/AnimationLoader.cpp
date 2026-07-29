#include "Graphics/AnimationLoader.h"
#include <nlohmann/json.hpp>
#include <fstream>
#include <iostream>

using json = nlohmann::json;

void AnimationLoader::loadFromJson(Animation& animation, const std::string& JsonPath)
{
	std::ifstream fin(JsonPath);

	if (!fin.is_open()) {
		std::cout << "Couldn't open animation json: " << JsonPath << std::endl;
		return;
	}

	json data; fin >> data;

	std::vector <sf::IntRect> frameRect;
	std::vector <float> frameDuration;

	for (const auto& frameEntry : data["frames"]) {
		int x = frameEntry["frame"]["x"];
		int y = frameEntry["frame"]["y"];
		int w = frameEntry["frame"]["w"];
		int h = frameEntry["frame"]["h"];
		float duration = (frameEntry["duration"] / 1000.f);

		frameRect.push_back(sf::IntRect({ x, y }, { w, h }));
		frameDuration.push_back(duration);
	}

	for (const auto& tag: data["meta"]["frameTags"]) {
		std::string name = tag["name"];

		int start = tag["from"], end = tag["to"];

		for (int i = start; i <= end; ++i) {
			animation.addFrame(name, frameRect[i], frameDuration[i]);
		}
	}
}
