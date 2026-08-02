#pragma once

#include "Input/IInputSource.h"
#include <SFML/Window.hpp>
#include <unordered_map>


class KeyboardInputSource : public IInputSource
{
private:
	std::unordered_map<InputAction, std::vector<sf::Keyboard::Key>> heldBindings_;
	std::unordered_map<InputAction, std::vector<sf::Keyboard::Key>> pressedBindings_;

	std::unordered_map<InputAction, bool> pressedThisFrame_;
public:
	KeyboardInputSource();

	bool isActionHeld(InputAction action) const override;
	bool isActionPressed(InputAction action) const override;

	void onKeyPressed(sf::Keyboard::Key key);
	void resetFrame();
};