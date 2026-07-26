#include "Game/Game.h"


Game::Game() 
{
	window_.create(
		sf::VideoMode({Constants::Window::Width, Constants::Window::Height}),
		"PixelFight"

	);

	window_.setKeyRepeatEnabled(false);

	ground_.setSize({ static_cast<float>(Constants::Window::Width), Constants::Window::Height - Constants::Player::PositionY });
	ground_.setFillColor(sf::Color(55, 45, 38));
	ground_.setPosition({ Constants::Player::PositionX, Constants::Player::PositionY + Constants::Player::Size });

	player_ = std::make_unique<Goblin>(resourceManager_.getTexture("Assets/Sprites/Goblin.png"));
}

//--------------------------------------------------------------------------

void Game::run() 
{
	while (window_.isOpen()) {
		float deltaTime = clock_.restart().asSeconds();

		processEvents();
		update(deltaTime);
		render();
	}
}

//--------------------------------------------------------------------------

void Game::processEvents() 
{
	while (const auto event = window_.pollEvent()) {
		if (event->is<sf::Event::Closed>()) {
			window_.close();
		}

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>())
		{
			// Dash
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
			// Jump
			if (keyPressed->code == sf::Keyboard::Key::W || keyPressed->code == sf::Keyboard::Key::Space) {
				player_->jump();
			}
		}
	}
}

//--------------------------------------------------------------------------

void Game::update(float deltaTime)
{
	player_->updateCooldowns(deltaTime);
	player_->updatePhysics(deltaTime);

	bool moved = false;

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
	{
		player_->moveLeft(deltaTime);
		moved = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
	{
		player_->moveRight(deltaTime);
		moved = true;
	}

	player_->setMoving(moved);
	player_->setCrouching(sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S) || sf::Keyboard::isKeyPressed(sf::Keyboard::Key::LControl));

	player_->update(deltaTime);
}

//--------------------------------------------------------------------------

void Game::render() 
{
	window_.clear(sf::Color::Cyan);

	window_.draw(ground_);
	player_->render(window_);

	window_.display();
}

//--------------------------------------------------------------------------