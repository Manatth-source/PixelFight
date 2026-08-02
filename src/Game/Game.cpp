#include "Game/Game.h"

#define ON 1
#define OFF 0


Game::Game()
{
	window_.create(
		sf::VideoMode({ Constants::Window::Width, Constants::Window::Height }),
		"PixelFight"
	);

	window_.setKeyRepeatEnabled(false);

	ground_.setSize({ static_cast<float>(Constants::Window::Width), Constants::Window::Height - Constants::Player::PositionY });
	ground_.setFillColor(Constants::Color::Ground);
	ground_.setPosition({ Constants::Player::PositionX, Constants::Player::PositionY + Constants::Player::Size });

#if OFF
	player_ = std::make_unique<Samurai>(resourceManager_.getTexture("Assets/Sprites/Samurai/Samurai.png"));
#endif

#if ON
	player_ = std::make_unique<Wizard>(resourceManager_.getTexture("Assets/Sprites/Wizard/Wizard.png"));
#endif

#if OFF
	player_ = std::make_unique<Goblin>(resourceManager_.getTexture("Assets/Sprites/Goblin/Goblin.png"));
#endif

	player2_ = std::make_unique<Goblin>(resourceManager_.getTexture("Assets/Sprites/Goblin/Goblin.png"));
	player2_->setPosition(Constants::Window::Width - Constants::Player::Size, Constants::Player::PositionY);

	victory_plaque_.setSize({ static_cast<float>(Constants::Window::Width) - Constants::UI::VictoryPlaqueWidthMargin, Constants::UI::VictoryPlaqueHeight });
	victory_plaque_.setFillColor(Constants::Color::Plaque);
	victory_plaque_.setPosition({ Constants::UI::VictoryPlaqueX, Constants::Player::PositionY - Constants::UI::VictoryPlaqueYOffset });
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
			//Attack
			if (keyPressed->code == sf::Keyboard::Key::F) {
				player_->attack();

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


//*********************************************
	player2_->updateCooldowns(deltaTime);
	player2_->updatePhysics(deltaTime);
	player2_->update(deltaTime);
//*********************************************

	//Attack
	if (!player_->hasHitThisAttack() && player_->getAttackHitbox().findIntersection(player2_->getBodyBounds()).has_value()) {
		player2_->takeDamage(player_->getAttackDamage());
		player_->markHit();
	}

	if (!player2_->hasHitThisAttack() && player2_->getAttackHitbox().findIntersection(player_->getBodyBounds()).has_value()) {
		player_->takeDamage(player2_->getAttackDamage());
		player2_->markHit();
	}
}

//--------------------------------------------------------------------------

void Game::render() 
{
	window_.clear(Constants::Color::Sky);

	window_.draw(ground_);


	if (player_->isAlive()) player_->render(window_);
	if (player2_->isAlive()) player2_->render(window_);


	if (!player_->isAlive() || !player2_->isAlive()) 
		window_.draw(victory_plaque_);

	window_.display();
}

//--------------------------------------------------------------------------