#pragma once

#include <SFML/System.hpp>

struct Edge
{
	sf::Vector2f max;
	sf::Vector2f p1;
	sf::Vector2f p2;

	float VecDot(const sf::Vector2f& v) const;
	[[nodiscard]] sf::Vector2f EdgeVector() const;
};