#pragma once

#include <vector>

#include "CollisionBody.hpp"
#include "Solver.hpp"

class PhysicsWorld
{
public:
	void AddBody(CollisionBody* body);
	void RemoveBody(CollisionBody* body);

	void AddSolver(Solver* solver);
	void RemoveSolver(Solver* solver);

	void Step(float deltaTime) const;
	void ResolveCollisions(float deltaTime) const;

private:
	std::vector<CollisionBody*> _bodies;
	std::vector<Solver*> _solvers;
	sf::Vector2f _gravity;
};
