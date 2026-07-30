#pragma once

namespace Constants
{
    namespace Window {
        constexpr unsigned int Width = 1280;
        constexpr unsigned int Height = 720;
    }

    namespace Player {
        constexpr float Speed = 200.f;
        constexpr int StartHealth = 100;
        constexpr float SpeedSit = 70.f;

        constexpr float PositionY = 250.f;
        constexpr float PositionX = 0.f;

        constexpr int Size = 128;
        constexpr float SpriteScale = 1.1f;
    }

    namespace Attack {
        constexpr float Duration = 0.2f;
        constexpr float Cooldown = 1.0f;
        constexpr int Damage = 50;
        constexpr float HitboxWidth = 60.f;
    }

    namespace Jump {
        constexpr float Gravity = 1500.f;
        constexpr float Strength = -600.f;
        constexpr float LandDuration = 0.1f;
    }

    namespace Dash {
        constexpr float IndicatorSize = 50.f;
        constexpr float IndicatorX = 50.f;
        constexpr float IndicatorY = 500.f;
        constexpr float Distance = 150.f;
        constexpr float Cooldown = 2.5f;
    }

    namespace UI {
        constexpr float VictoryPlaqueHeight = 35.f;
        constexpr float VictoryPlaqueWidthMargin = 700.f;
        constexpr float VictoryPlaqueX = 350.f;
        constexpr float VictoryPlaqueYOffset = 100.f;
    }
}