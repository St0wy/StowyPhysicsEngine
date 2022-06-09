#pragma once

#include <SFML/System.hpp>

struct Body
{
public:
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Vector2f force;
	float mass{};
};