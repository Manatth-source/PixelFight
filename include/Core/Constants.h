#pragma once

#include <SFML/Graphics.hpp>


namespace Constants
{
    namespace Window {
        constexpr unsigned int Width = 1280;
        constexpr unsigned int Height = 720;
    }

    namespace Player {
        constexpr float PositionY = 250.f;
        constexpr float PositionX = 0.f;

        constexpr int Size = 128;
        constexpr float SpriteScale = 1.1f;
    }

    namespace Attack {
        constexpr float HitboxWidth = 60.f;
    }

    namespace Dash {
        constexpr float IndicatorSize = 50.f;
        constexpr float IndicatorXPlayer1 = 50.f;
        constexpr float IndicatorXPlayer2 = 1180.f;
        constexpr float IndicatorY = 500.f;
    }

    namespace UI {
        constexpr float VictoryPlaqueHeight = 35.f;
        constexpr float VictoryPlaqueWidthMargin = 700.f;
        constexpr float VictoryPlaqueX = 350.f;
        constexpr float VictoryPlaqueYOffset = 100.f;
    }

    namespace Color {
        const sf::Color Ground(55, 45, 38);
        const sf::Color Sky(135, 206, 235);
        const sf::Color Plaque = sf::Color::Yellow;
    }
}