#include "Graphics/Animation.h"


Animation::Animation(sf::Sprite& sprite)
    : sprite_(&sprite)
    , currentFrame_(0)
    , timer_(0.f)
{
}

//--------------------------------------------------------------------------

void Animation::addFrame(const std::string& clipName, const sf::IntRect& frame, float duration)
{
    clips_[clipName].push_back({ frame, duration });
}

//--------------------------------------------------------------------------

void Animation::play(const std::string& clipName)
{
    if (currentClip_ == clipName)
        return; // we're already playing this clip — don't reset to 0 frame every call

    currentClip_ = clipName;
    currentFrame_ = 0;
    timer_ = 0.f;

    auto it = clips_.find(clipName);
    if (it != clips_.end() && !it->second.empty())
    {
        sprite_->setTextureRect(it->second[0].rect);
    }
}

//--------------------------------------------------------------------------

void Animation::update(float deltaTime)
{
    auto it = clips_.find(currentClip_);
    if (it == clips_.end() || it->second.empty())
        return;

    const auto& frames = it->second;

    timer_ += deltaTime;

    if (timer_ >= frames[currentFrame_].duration)
    {
        timer_ = 0.f;
        currentFrame_++;

        if (currentFrame_ >= frames.size())
            currentFrame_ = 0;

        sprite_->setTextureRect(frames[currentFrame_].rect);
    }
}