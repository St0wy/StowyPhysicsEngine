#pragma once

#include "math/Vector2.hpp"

struct Manifold
{
public:
	Vector2 a;
	Vector2 b;
	Vector2 normal;
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