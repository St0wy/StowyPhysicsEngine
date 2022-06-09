#include "PhysicsWorld.hpp"

#include "Collisions.hpp"

void PhysicsWorld::AddBody(CollisionBody* body)
{
	_bodies.push_back(body);
}

void PhysicsWorld::RemoveBody(CollisionBody* body)
{
	if (!body) return;

	const auto itr = std::ranges::find(_bodies, body);

	if (itr == _bodies.end()) return;

	_bodies.erase(itr);
}

void PhysicsWorld::AddSolver(Solver* solver)
{
	_solvers.push_back(solver);
}

void PhysicsWorld::RemoveSolver(Solver* solver)
{
	if (!solver) return;

	const auto itr = std::ranges::find(_solvers, solver);

	if (itr == _solvers.end()) return;

	_solvers.erase(itr);
}

void PhysicsWorld::ResolveCollisions(const float deltaTime) const
{
	std::vector<Collision> collisions;

	for (CollisionBody* a : _bodies)
	{
		for (CollisionBody* b : _bodies)
		{
			if (a == b) break;

			if (!a->collider || !b->collider) continue;

			CollisionPoints points = a->collider->TestCollision(a->transform, b->collider, b->transform);

			if (points.hasCollision)
			{
				collisions.emplace_back(a, b, points);
			}
		}
	}

	for (Solver* solver : _solvers)
	{
		solver->Solve(collisions, deltaTime);
	}
}

void PhysicsWorld::Step(const float deltaTime) const
{
	ResolveCollisions(deltaTime);

	for (CollisionBody* body : _bodies)
	{
		// Apply gravity
		body->force += body->mass * _gravity;

		// Update velocity and position
		body->velocity += body->force / body->mass * deltaTime;
		body->transform->position += body->velocity * deltaTime;

		// Reset force
		body->force = sf::Vector2f(0, 0);
	}
}
