#include "Input/KeyboardInputSource.h"


KeyboardInputSource::KeyboardInputSource()
{
	heldBindings_[InputAction::MoveLeft] = { sf::Keyboard::Key::A };
	heldBindings_[InputAction::MoveRight] = { sf::Keyboard::Key::D };
	heldBindings_[InputAction::Crouch] = { sf::Keyboard::Key::S };

	pressedBindings_[InputAction::Jump] = { sf::Keyboard::Key::W, sf::Keyboard::Key::Space };
	pressedBindings_[InputAction::Attack] = { sf::Keyboard::Key::F };
}


bool KeyboardInputSource::isActionHeld(InputAction action) const
{
	auto it = heldBindings_.find(action);
	if (it == heldBindings_.end())
		return false;

	for (const auto& key : it->second)
	{
		if (sf::Keyboard::isKeyPressed(key))
			return true;
	}

	return false;
}


bool KeyboardInputSource::isActionPressed(InputAction action) const
{
	auto it = pressedThisFrame_.find(action);
	if (it == pressedThisFrame_.end())
		return false;

	return it->second;
}


void KeyboardInputSource::onKeyPressed(sf::Keyboard::Key key)
{
	for (const auto& [action, keys] : pressedBindings_)
	{
		for (const auto& boundKey : keys)
		{
			if (boundKey == key)
			{
				pressedThisFrame_[action] = true;
			}
		}
	}


	if (key == sf::Keyboard::Key::LShift)
	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A))
			pressedThisFrame_[InputAction::DashLeft] = true;
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D))
			pressedThisFrame_[InputAction::DashRight] = true;
	}
}


void KeyboardInputSource::resetFrame()
{
	pressedThisFrame_.clear();
}