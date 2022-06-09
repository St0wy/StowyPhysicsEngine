#pragma once

#include <vector>
#include "Collisions.hpp"

class Solver
{
public:
	virtual void Solve(const std::vector<Collision>& collsions, float deltaTime) = 0;
};