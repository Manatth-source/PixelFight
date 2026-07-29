#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <string>
#include <unordered_map>


struct AnimationFrame
{
    sf::IntRect rect;
    float duration; // in seconds
};


class Animation
{
private:
    sf::Sprite* sprite_;

    std::unordered_map<std::string, std::vector<AnimationFrame>> clips_;
    std::string currentClip_;

    std::size_t currentFrame_;
    float timer_;

public:
    Animation(sf::Sprite& sprite);

    void addFrame(const std::string& clipName, const sf::IntRect& frame, float duration);
    void play(const std::string& clipName);
    void update(float deltaTime);
};