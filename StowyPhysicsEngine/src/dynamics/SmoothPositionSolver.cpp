#include "dynamics/SmoothPositionSolver.hpp"

#include <vector>

#include "dynamics/Rigidbody.hpp"
#include "collision/Collision.hpp"

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

		constexpr float percent = 0.8f;
		constexpr float slop = 0.01f;

		const Vector2 correction = points.normal * percent
			* std::max(resolution.Magnitude() - slop, 0.0f)
			/ (aInvMass + bInvMass);

		if (aBody ? aBody->IsKinematic() : false)
		{
			const Vector2 deltaA = -aInvMass * correction;
			aBody->Trans()->position += deltaA;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			const Vector2 deltaB = bInvMass * correction;
			bBody->Trans()->position += deltaB;
		}
	}
}
