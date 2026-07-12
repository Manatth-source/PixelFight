#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>

class Animation
{
private:
    sf::Sprite* sprite_;

    std::unordered_map<std::string, std::vector<sf::IntRect>> clips_;
    std::string currentClip_;

    std::size_t currentFrame_;
    float frameTime_;
    float timer_;

public:
    Animation(sf::Sprite& sprite);

    void addFrame(const std::string& clipName, const sf::IntRect& frame);
    void play(const std::string& clipName);
    void update(float deltaTime);
};