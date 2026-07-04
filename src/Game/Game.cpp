#include "Game/Game.h"

Game::Game() 
{
	window_.create(
		sf::VideoMode({1280, 720}),
		"PixelFight"
	);

	player1_ = std::make_unique<Samurai>(resourceManager_.getTexture("Assets/Sprites/test_character.png"));
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
	}
}

void Game::update(float deltaTime) 
{
	//float speed = 100.f; // speed pixels per second
}


void Game::render() 
{
	window_.clear(sf::Color::White);
	player1_->render(window_);
	window_.display();
}