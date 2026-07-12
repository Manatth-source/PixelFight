#include "Player/Goblin.h"


Goblin::Goblin(const sf::Texture& texture) : Character(texture)
{
	for (int i = 0; i <= 2; ++i)
		animation_.addFrame("Idle", sf::IntRect({ 2 + i * 128, 2 }, { 128, 128 }));

	for (int i = 3; i <= 6; ++i)
		animation_.addFrame("Walk", sf::IntRect({ 2 + i * 128, 2 }, { 128, 128 }));

	for (int i = 9; i <= 14; ++i)
		animation_.addFrame("Jump_Loop", sf::IntRect({ 2 + i * 128, 2 }, { 128, 128 }));

	animation_.addFrame("Sit", sf::IntRect({ 2 + 16 * 128, 2 }, { 128, 128 }));

	animation_.play("Idle");
}