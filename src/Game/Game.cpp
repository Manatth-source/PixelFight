#include "Game/Game.h"

Game::Game() {
	window_.create(
		sf::VideoMode({1280, 720}),
		"PixelFight"
	);

	sprite_.emplace(resourceManager.getTexture("Assets/Sprites/test_character.png"));
	sprite_->setScale({0.6f, 0.6f});
	sprite_->setPosition({ 300.f, 100.f });
}

void Game::run() {
	while (window_.isOpen()) {
		float deltaTime = clock_.restart().asSeconds();

		processEvents();
		update(deltaTime);
		render();
	}
}

void Game::processEvents() {
	while (const auto event = window_.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window_.close();
		}
	}
}

void Game::update(float deltaTime) {
	float speed = 100.f;

	sf::Vector2f pos = sprite_->getPosition();
	if (!reverseMode_) {
		pos.x += speed * deltaTime;

		if (pos.x >= 800) {
			reverseMode_ = true;
		}
	}
	else {
		pos.x -= speed * deltaTime;

		if (pos.x <= 300) {
			reverseMode_ = false;
		}
	}

	sprite_->setPosition(pos);
}

void Game::render() {
	window_.clear(sf::Color::White);
	window_.draw(*sprite_);
	window_.display();
}