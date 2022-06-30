#pragma once

#include <vector>
#include "collision/Collision.hpp"

class Solver
{
public:
	virtual void Solve(const std::vector<Collision>& collisions, float deltaTime) = 0;
};