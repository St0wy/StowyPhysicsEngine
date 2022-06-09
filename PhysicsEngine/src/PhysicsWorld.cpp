#include "PhysicsWorld.hpp"

void PhysicsWorld::AddBody(Body* body)
{
	_bodies.push_back(body);
}

void PhysicsWorld::RemoveBody(Body* body)
{
	if (!body) return;

	const auto itr = std::ranges::find(_bodies, body);

	if (itr == _bodies.end()) return;

	_bodies.erase(itr);
}

void PhysicsWorld::Step(const float deltaTime) const
{
	for (Body* body : _bodies)
	{
		// Apply gravity
		body->force += body->mass * _gravity;

		// Update velocity and position
		body->velocity += body->force / body->mass * deltaTime;
		body->position += body->velocity * deltaTime;

		// Reset force
		body->force = sf::Vector2f(0, 0);
	}
}
