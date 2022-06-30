#pragma once

#include <SFML/System/Vector2.hpp>

sf::Vector2f SpeVecToSfml(const sf::Vector2f& v)
{
	return { v.x, -v.y };
}