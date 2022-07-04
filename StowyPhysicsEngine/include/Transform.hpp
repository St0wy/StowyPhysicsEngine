#pragma once

#include "math/Vector2.hpp"

#include <SFML/System.hpp>

struct Transform
{
public:
	Vector2 position;
	Vector2 scale{1, 1};
	float rotation{};
};