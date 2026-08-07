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

#if ON
	player2_ = std::make_unique<Samurai>(resourceManager_.getTexture("Assets/Sprites/Samurai/Samurai.png"));
#endif

#if ON
	player_ = std::make_unique<Wizard>(resourceManager_.getTexture("Assets/Sprites/Wizard/Wizard.png"));
#endif

#if OFF
	player_ = std::make_unique<Goblin>(resourceManager_.getTexture("Assets/Sprites/Goblin/Goblin.png"));
#endif

#if OFF
	player2_ = std::make_unique<Goblin>(resourceManager_.getTexture("Assets/Sprites/Goblin/Goblin.png"));
#endif
	player2_->setPosition(Constants::Window::Width - Constants::Player::Size - 200, Constants::Player::PositionY);

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

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			inputSource_.onKeyPressed(keyPressed->code);
		}
	}
}

//--------------------------------------------------------------------------

void Game::update(float deltaTime)
{
	player_->updateCooldowns(deltaTime);
	player_->updatePhysics(deltaTime);

	if (inputSource_.isActionPressed(InputAction::Jump)) {
		player_->jump();
	}
	if (inputSource_.isActionPressed(InputAction::Attack)) {
		player_->attack();
	}
	if (inputSource_.isActionPressed(InputAction::DashLeft)) {
		player_->dashLeft();
	}
	if (inputSource_.isActionPressed(InputAction::DashRight)) {
		player_->dashRight();
	}

	bool moved = false;
	if (inputSource_.isActionHeld(InputAction::MoveLeft)) {
		player_->moveLeft(deltaTime);
		moved = true;
	}
	if (inputSource_.isActionHeld(InputAction::MoveRight)) {
		player_->moveRight(deltaTime);
		moved = true;
	}

	player_->setMoving(moved);
	player_->setCrouching(inputSource_.isActionHeld(InputAction::Crouch));

	player_->update(deltaTime);

	inputSource_.resetFrame();


	//*********************************************
	player2_->updateCooldowns(deltaTime);
	player2_->updatePhysics(deltaTime);
	player2_->update(deltaTime);
	//*********************************************

		//Attack
	if (!player_->hasHitThisAttack() && player_->getAttackHitbox().findIntersection(player2_->getBodyBounds()).has_value()) {
		player2_->takeDamage(player_->getAttackDamage());
	}

	if (!player2_->hasHitThisAttack() && player2_->getAttackHitbox().findIntersection(player_->getBodyBounds()).has_value()) {
		player_->takeDamage(player2_->getAttackDamage());
	}
	
	player_->markHit();
	player2_->markHit();
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