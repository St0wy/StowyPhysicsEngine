#pragma once

#include "Solver.hpp"

class ImpulseSolver : public Solver
{
public:
	void Solve(const std::vector<Collision>& collisions, float deltaTime) override;
};