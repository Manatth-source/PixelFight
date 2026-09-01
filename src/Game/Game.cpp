#include "Game/Game.h"

#define ON 1
#define OFF 0


Game::Game() : hud_(resourceManager_)
{
	window_.create(
		sf::VideoMode({ Constants::Window::Width, Constants::Window::Height }),
		"PixelFight"
	);

	window_.setKeyRepeatEnabled(false);

	background_ = sf::Sprite(resourceManager_.getTexture("Assets/Maps/Map1.png"));

#if OFF
	player1_ = std::make_unique<Samurai>(resourceManager_);
#endif
#if ON
	player1_ = std::make_unique<Wizard>(resourceManager_);
#endif
#if OFF
	player1_ = std::make_unique<Goblin>(resourceManager_);
#endif


#if ON
	player2_ = std::make_unique<Goblin>(resourceManager_);
#endif
#if OFF
	player2_ = std::make_unique<Samurai>(resourceManager_);
#endif

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

		if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
			inputSource_.onKeyPressed(keyPressed->code);
		}
	}
}

//--------------------------------------------------------------------------

void Game::update(float deltaTime)
{
	player1_->updateCooldowns(deltaTime);
	player2_->updateCooldowns(deltaTime);

	player1_->updatePhysics(deltaTime);
	player2_->updatePhysics(deltaTime);

	if (inputSource_.isActionPressed(InputAction::Jump)) {
		player1_->jump();
	}
	if (inputSource_.isActionPressed(InputAction::BasicAttack)) {
		player1_->basicAttack();
	}

	if (inputSource_.isActionPressed(InputAction::DashLeft)) {
		player1_->dashLeft();
	}
	if (inputSource_.isActionPressed(InputAction::DashRight)) {
		player1_->dashRight();
	}

	bool moved = false;
	if (inputSource_.isActionHeld(InputAction::MoveLeft)) {
		player1_->moveLeft(deltaTime);
		moved = true;
	}
	if (inputSource_.isActionHeld(InputAction::MoveRight)) {
		player1_->moveRight(deltaTime);
		moved = true;
	}

	player1_->setMoving(moved);
	player1_->setCrouching(inputSource_.isActionHeld(InputAction::Crouch));

	if (inputSource_.isActionHeld(InputAction::Shild)) {
		player1_->shild();
	}

	player1_->update(deltaTime);
	player2_->update(deltaTime);

	inputSource_.resetFrame();

		//Attack
	if (!player1_->hasPerformedAttack() && player1_->getAttackHitbox().findIntersection(player2_->getBodyBounds()).has_value()) {
		player2_->takeDamage(player1_->getAttackDamage(), player1_->getAttackTypes());
		player1_->markHit();
	}

	if (!player2_->hasPerformedAttack() && player2_->getAttackHitbox().findIntersection(player1_->getBodyBounds()).has_value()) {
		player1_->takeDamage(player2_->getAttackDamage(), player2_->getAttackTypes());
		player2_->markHit();
	}

	hud_.update(*player1_, *player2_);

}

//--------------------------------------------------------------------------

void Game::render()
{
	window_.clear();

	window_.draw(*background_);


	if (player1_->isAlive()) player1_->render(window_);
	if (player2_->isAlive()) player2_->render(window_);


	if (!player1_->isAlive() || !player2_->isAlive())
		window_.draw(victory_plaque_);

	hud_.render(window_);

	window_.display();
}

//--------------------------------------------------------------------------