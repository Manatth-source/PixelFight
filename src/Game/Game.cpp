#include "Game/Game.h"

Game::Game() 
{
	window_.create(
		sf::VideoMode({1280, 720}),
		"PixelFight"
	);

	window_.setKeyRepeatEnabled(false);

	player_ = std::make_unique<Samurai>(resourceManager_.getTexture("Assets/Sprites/Samurai_test.png"));
}

void Game::run() 
{
	while (window_.isOpen()) {
		float deltaTime = clock_.restart().asSeconds();

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents() 
{
	while (const auto event = window_.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window_.close();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			if (keyPressed->code == sf::Keyboard::Key::LShift)
			{
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
				{
					player_->dashLeft();
				}
				else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
				{
					player_->dashRight();
				}
			}
		}
	}
}

void Game::update(float deltaTime)
{
	player_->updateCooldowns(deltaTime);

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player_->moveLeft(deltaTime);
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player_->moveRight(deltaTime);
	}
}


void Game::render() 
{
	window_.clear(sf::Color::White);
	player_->render(window_);
	window_.display();
}