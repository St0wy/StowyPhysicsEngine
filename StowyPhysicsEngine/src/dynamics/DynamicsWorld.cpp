#include "dynamics/DynamicsWorld.hpp"

#include <ranges>

#include "collision/CollisionBody.hpp"

namespace stw
{
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
	for (const auto body : _bodies | std::views::values)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;
		const Vector2 force = rigidbody->GravityForce() * rigidbody->Mass();
		rigidbody->ApplyForce(force);
	}
}

void DynamicsWorld::MoveBodies(const float deltaTime) const
{
	const auto dynamics = [](const CollisionBody* body) { return body->IsDynamic(); };

	for (const CollisionBody* body : _bodies | std::views::values | std::views::filter(dynamics))
	{
		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;

		const Vector2 vel = rigidbody->Velocity() + rigidbody->Force() * rigidbody->InvMass() * deltaTime;
		rigidbody->SetVelocity(vel);

		Vector2 pos = rigidbody->Position() + rigidbody->Velocity() * deltaTime;
		rigidbody->SetPosition(pos);

		rigidbody->SetForce({ 0, 0 });
	}
}

void DynamicsWorld::Step(const float deltaTime)
{
	ApplyGravity();
	ResolveCollisions(deltaTime);
	MoveBodies(deltaTime);
}

void DynamicsWorld::SetWorldGravity(const Vector2 gravity)
{
	_gravity = gravity;
}
}
