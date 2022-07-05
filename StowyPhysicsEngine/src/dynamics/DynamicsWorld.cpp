#include "dynamics/DynamicsWorld.hpp"

#include "collision/CollisionBody.hpp"

#include "spdlog/spdlog.h"

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
		const Vector2 force = rigidbody->GravityForce() * rigidbody->Mass();
		rigidbody->ApplyForce(force);
	}
}

void DynamicsWorld::MoveBodies(const float deltaTime) const
{
	for (CollisionBody* body : _bodies)
	{
		if (!body->IsDynamic()) continue;

		// ReSharper disable once CppCStyleCast
		const auto rigidbody = (Rigidbody*)body;

		const Vector2 vel = rigidbody->Velocity() + rigidbody->Force() * rigidbody->InvMass() * deltaTime;
		if(std::isnan(vel.x))
		{
			spdlog::error("Bad vel: {}", vel);
			return;
		}
		rigidbody->SetVelocity(vel);

		//rigidbody->UpdateLastTransform();

		Vector2 pos = rigidbody->Position() + rigidbody->Velocity() * deltaTime;
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

void DynamicsWorld::SetWorldGravity(const Vector2 gravity)
{
	_gravity = gravity;
}
