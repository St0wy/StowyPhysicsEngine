#include "dynamics/ImpulseSolver.hpp"

#include "collision/Collision.hpp"

#include "dynamics/Rigidbody.hpp"

void ImpulseSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	for (const auto& [bodyA, bodyB, manifold] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		Vector2 aVel = aBody->Velocity();
		Vector2 bVel = bBody->Velocity();
		Vector2 relativeVelocity = bVel - aVel;

		// Calculate relative velocity in terms of the normal direction
		float velocityAlongNormal = relativeVelocity.Dot(manifold.normal);

		// Do not resolve if velocities are separating
		if (velocityAlongNormal >= 0) continue;

		const float aInvMass = aBody ? aBody->InvMass() : 1.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 1.0f;

		// Impulse

		const float e = std::min(aBody ? aBody->Restitution() : 1.0f, bBody ? bBody->Restitution() : 1.0f);
		const float j = -(1.0f + e) * velocityAlongNormal / (aInvMass + bInvMass);

		const Vector2 impulse = j * manifold.normal;

		if (aBody ? aBody->IsKinematic() : false)
		{
			aVel -= impulse * aInvMass;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			bVel += impulse * bInvMass;
		}

		// Friction
		relativeVelocity = bVel - aVel;
		velocityAlongNormal = relativeVelocity.Dot(manifold.normal);

		Vector2 tangent = Vector2::Normalize(relativeVelocity - velocityAlongNormal * manifold.normal);

		const float fVel = relativeVelocity.Dot(tangent);

		const float aSf = aBody ? aBody->StaticFriction() : 0.0f;
		const float bSf = bBody ? bBody->StaticFriction() : 0.0f;
		const float aDf = aBody ? aBody->DynamicFriction() : 0.0f;
		const float bDf = bBody ? bBody->DynamicFriction() : 0.0f;
		float mu = Vector2(aSf, bSf).Magnitude();
		const float f = -fVel / (aInvMass + bInvMass);

		Vector2 friction;
		if (std::abs(f) < j * mu)
		{

			friction = f * tangent;
		}
		else
		{
			mu = Vector2(aDf, bDf).Magnitude();
			friction = -j * tangent * mu;
		}

		if (aBody ? aBody->IsKinematic() : false)
		{
			aBody->SetVelocity(aVel - friction * aInvMass);
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			bBody->SetVelocity(bVel + friction * bInvMass);
		}
	}
}
