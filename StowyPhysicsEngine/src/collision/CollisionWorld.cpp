#include "collision/CollisionWorld.hpp"
#include <spdlog/spdlog.h>

void CollisionWorld::AddCollisionBody(CollisionBody* body)
{
	_bodies.push_back(body);
}

void CollisionWorld::RemoveCollisionBody(CollisionBody* body)
{
	if (!body) return;

	const auto itr = std::ranges::find(_bodies, body);

	if (itr == _bodies.end()) return;

	_bodies.erase(itr);
}

void CollisionWorld::AddSolver(Solver* solver)
{
	_solvers.push_back(solver);
}

void CollisionWorld::RemoveSolver(Solver* solver)
{
	if (!solver) return;

	const auto itr = std::ranges::find(_solvers, solver);

	if (itr == _solvers.end()) return;

	_solvers.erase(itr);
}

void CollisionWorld::SetCollisionCallback(const std::function<void(Collision&, float)>& callback)
{
	_onCollision = callback;
}

void CollisionWorld::SolveCollisions(const std::vector<Collision>& collisions, const float deltaTime) const
{
	for (Solver* solver : _solvers)
	{
		solver->Solve(collisions, deltaTime);
	}
}

void CollisionWorld::SendCollisionCallbacks(std::vector<Collision>& collisions, const float deltaTime) const
{
	for (Collision& collision : collisions)
	{
		if (_onCollision)
			_onCollision(collision, deltaTime);

		collision.bodyA->OnCollision(collision, deltaTime);
		collision.bodyB->OnCollision(collision, deltaTime);
	}
}

void CollisionWorld::ResolveCollisions(const float deltaTime) const
{
	std::vector<Collision> collisions;
	std::vector<Collision> triggers;

	//for (CollisionBody* a : _bodies)
	//{
	//	for (CollisionBody* b : _bodies)
	//	{
	//		if (a == b) break;
	for (std::size_t i = 0; i < _bodies.size(); ++i)
	{
		for (std::size_t j = i + 1; j < _bodies.size(); ++j)
		{
			CollisionBody* a = _bodies[i];
			CollisionBody* b = _bodies[j];

			if (!a->Col() || !b->Col()) continue;

			const Manifold manifold = a->Col()->TestCollision(
				a->Trans(), b->Col(), b->Trans());


			if (!manifold.hasCollision) continue;

			if (a->IsTrigger() || b->IsTrigger())
			{
				triggers.emplace_back(a, b, manifold);
			}
			else
			{
				collisions.emplace_back(a, b, manifold);
			}
		}
	}

	SolveCollisions(collisions, deltaTime);

	SendCollisionCallbacks(collisions, deltaTime);
	SendCollisionCallbacks(triggers, deltaTime);
}
