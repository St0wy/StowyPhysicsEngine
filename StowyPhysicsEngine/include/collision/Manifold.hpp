#pragma once

#include "math/Vector2.hpp"
#include "spdlog/fmt/ostr.h"

struct Manifold
{
public:
	Manifold(const Vector2& a, const Vector2& b, const Vector2& normal, float depth);
	Manifold(const Vector2& normal, float depth);
	Manifold();

	Vector2 a;
	Vector2 b;
	Vector2 normal;
	float depth{};
	bool hasCollision{};

	static Manifold Empty()
	{
		return {};
	}
};

std::ostream& operator<<(std::ostream& os, const Manifold& manifold);