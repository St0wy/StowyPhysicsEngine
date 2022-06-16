#include "SmoothPositionSolver.hpp"

#include <vector>

#include "Solver.hpp"
#include "Rigidbody.hpp"
#include "VecUtils.hpp"

void SmoothPositionSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	std::vector<std::pair<sf::Vector2f, sf::Vector2f>> deltas;

	for (const Collision& collision : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = collision.bodyA->IsDynamic() ? (Rigidbody*)collision.bodyA : nullptr;
		Rigidbody* bBody = collision.bodyB->IsDynamic() ? (Rigidbody*)collision.bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		const float aInvMass = aBody ? aBody->InvMass() : 0.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 0.0f;

		sf::Vector2f resolution = collision.points.b - collision.points.a;

		constexpr float percent = 0.8f;
		constexpr float slop = 0.01f;

		sf::Vector2f correction = collision.points.normal * percent
			* std::fmax(Magnitude(resolution) - slop, 0.0f)
			/ (aInvMass + bInvMass);

		sf::Vector2f deltaA;
		sf::Vector2f deltaB;

		if (aBody ? aBody->IsKinematic() : false)
		{
			deltaA = -aInvMass * correction;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			deltaB = bInvMass * correction;
		}

		deltas.emplace_back(deltaA, deltaB);
	}

	// TODO : Continue line 43
}
