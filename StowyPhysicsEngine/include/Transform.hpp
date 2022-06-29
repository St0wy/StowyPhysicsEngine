#pragma once

#include <SFML/System.hpp>

struct Transform
{
public:
	sf::Vector2f position;
	sf::Vector2f scale{1, 1};
	float rotation{};
};