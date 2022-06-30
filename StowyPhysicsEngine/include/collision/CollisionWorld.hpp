#pragma once

#include <vector>

#include "CollisionBody.hpp"
#include "Collisions.hpp"
#include "Solver.hpp"

class CollisionWorld
{
public:
	void AddCollisionBody(CollisionBody* body);
	void RemoveCollisionBody(CollisionBody* body);

	void AddSolver(Solver* solver);
	void RemoveSolver(Solver* solver);

	void SetCollisionCallback(const std::function<void(Collision&, float)>& callback);

	void SolveCollisions(const std::vector<Collision>& collisions, float deltaTime) const;

	void SendCollisionCallbacks(std::vector<Collision>& collisions, float deltaTime) const;

	void ResolveCollisions(float deltaTime) const;

protected:
	std::vector<CollisionBody*> _bodies;
	std::vector<Solver*> _solvers;

	std::function<void(Collision&, float)> _onCollision;
};
