#include "dynamics/Solver.hpp"

#include "collision/Collision.hpp"

#include "dynamics/Rigidbody.hpp"

namespace stw
{
void ImpulseSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	for (const auto& [bodyA, bodyB, manifold] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		Vector2 aVel = aBody ? aBody->Velocity() : Vector2::Zero();
		Vector2 bVel = bBody ? bBody->Velocity() : Vector2::Zero();
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

void SmoothPositionSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	for (const auto& [bodyA, bodyB, points] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		const float aInvMass = aBody ? aBody->InvMass() : 0.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 0.0f;

		Vector2 resolution = points.b - points.a;

		constexpr float slop = 0.01f;
		constexpr float percent = 0.8f;

		const Vector2 correction = points.normal * percent
			* std::max(resolution.Magnitude() - slop, 0.0f)
			/ (aInvMass + bInvMass);

		if (aBody ? aBody->IsKinematic() : false)
		{
			const Vector2 deltaA = aInvMass * correction;
			aBody->Trans()->position -= deltaA;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			const Vector2 deltaB = bInvMass * correction;
			bBody->Trans()->position += deltaB;
		}
	}
}
}
