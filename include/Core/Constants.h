#pragma once

#include <SFML/Graphics.hpp>


namespace Constants
{
    namespace Window {
        constexpr unsigned int Width = 1280;
        constexpr unsigned int Height = 720;
    }

    namespace Player {
        constexpr float PositionY = 350.f;
        constexpr float PositionX = 0.f;

        constexpr int Size = 128;
        constexpr float SpriteScale = 1.6f;
    }

    namespace Attack {
        constexpr float HitboxWidth = 60.f;
    }

    namespace Dash {
        constexpr float IndicatorSize = 60.f;
        constexpr float IndicatorXPlayer1 = 50.f;
        constexpr float IndicatorXPlayer2 = 1180.f;
        constexpr float IndicatorY = 620.f;

        constexpr float DurationPhaseStartAndEnd = 0.15f;
    }

    namespace Shild {
        constexpr float Cooldown = 4.f;
    }

    namespace UI {
        constexpr float VictoryPlaqueHeight = 35.f;
        constexpr float VictoryPlaqueWidthMargin = 700.f;
        constexpr float VictoryPlaqueX = 350.f;
        constexpr float VictoryPlaqueYOffset = 100.f;
    }

    namespace Color {
        const sf::Color Plaque = sf::Color::Yellow;
    }
}