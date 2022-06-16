#include "DynamicsWorld.hpp"

void DynamicsWorld::AddRigidbody(Rigidbody* rigidbody)
{
	if (rigidbody->takesGravity)
	{
		rigidbody->gravityForce = _gravity;
	}

	AddCollisionBody(rigidbody);
}

void DynamicsWorld::ApplyGravity() const
{
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;
		rigidbody->ApplyForce(rigidbody->gravityForce * rigidbody->mass);
	}
}

void DynamicsWorld::MoveBodies(const float deltaTime) const
{
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;

		const sf::Vector2f vel = rigidbody->velocity + rigidbody->force / rigidbody->mass * deltaTime;
		rigidbody->velocity = vel;

		sf::Vector2f pos = rigidbody->Position() + rigidbody->velocity * deltaTime;
		rigidbody->SetPosition(pos);

		rigidbody->force = { 0, 0 };
	}
}

void DynamicsWorld::Step(const float deltaTime) const
{
	ApplyGravity();
	ResolveCollisions(deltaTime);
	MoveBodies(deltaTime);
}
