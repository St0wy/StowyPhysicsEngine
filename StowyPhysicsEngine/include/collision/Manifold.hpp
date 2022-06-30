#pragma once

#include <SFML/System.hpp>

struct Manifold
{
public:
	sf::Vector2f a;
	sf::Vector2f b;
	sf::Vector2f normal;
	float depth{};
	bool hasCollision{};

	static Manifold Empty()
	{
		return {
			{0, 0},
			{0, 0},
			{0, 0},
			0,
			false
		};
	}
};