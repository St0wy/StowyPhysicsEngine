#include "dynamics/ImpulseSolver.hpp"

#include "dynamics/Rigidbody.hpp"
#include "collision/Collision.hpp"

void ImpulseSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	for (const auto& [bodyA, bodyB, points] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		Vector2 aVel = aBody ? aBody->Velocity() : Vector2(0, 0);
		Vector2 bVel = bBody ? bBody->Velocity() : Vector2(0, 0);
		Vector2 rVel = bVel - aVel;
		float nVel = rVel.Dot(points.normal);

		if (nVel >= 0) continue;

		const float aInvMass = aBody ? aBody->InvMass() : 0.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 0.0f;

		// Impulse

		const float e = (aBody ? aBody->Restitution() : 0.0f) * (bBody ? bBody->Restitution() : 0.0f);
		const float j = -(1.0f + e) * nVel / (aInvMass + bInvMass);

		const Vector2 impulse = j * points.normal;

		if (aBody ? aBody->IsKinematic() : false)
		{
			aVel -= impulse * aInvMass;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			bVel += impulse * bInvMass;
		}

		// Friction
		rVel = bVel - aVel;
		nVel = rVel.Dot(points.normal);

		Vector2 tangent = Vector2::Normalize(rVel - nVel * points.normal);
		const float fVel = rVel.Dot(tangent);

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
