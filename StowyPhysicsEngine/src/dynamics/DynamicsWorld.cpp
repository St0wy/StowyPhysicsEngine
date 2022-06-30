#include "dynamics/DynamicsWorld.hpp"

#include "collision/CollisionBody.hpp"

void DynamicsWorld::AddRigidbody(Rigidbody* rigidbody)
{
	if (rigidbody->TakesGravity())
	{
		rigidbody->SetGravityForce(_gravity);
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
		rigidbody->ApplyForce(rigidbody->GravityForce() * rigidbody->Mass());
	}
}

void DynamicsWorld::MoveBodies(const float deltaTime) const
{
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;

		const sf::Vector2f vel = rigidbody->Velocity() + rigidbody->Force() / rigidbody->Mass() * deltaTime;
		rigidbody->SetVelocity(vel);

		//rigidbody->UpdateLastTransform();

		sf::Vector2f pos = rigidbody->Position() + rigidbody->Velocity() * deltaTime;
		rigidbody->SetPosition(pos);

		rigidbody->SetForce({ 0, 0 });
	}
}

void DynamicsWorld::Step(const float deltaTime) const
{
	ApplyGravity();
	ResolveCollisions(deltaTime);
	MoveBodies(deltaTime);
}

void DynamicsWorld::SetWorldGravity(const sf::Vector2f gravity)
{
	_gravity = gravity;
}
