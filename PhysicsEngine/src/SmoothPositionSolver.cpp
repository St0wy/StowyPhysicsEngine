#include "SmoothPositionSolver.hpp"

#include <vector>

#include "Rigidbody.hpp"
#include "VecUtils.hpp"

void SmoothPositionSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	//std::vector<std::pair<sf::Vector2f, sf::Vector2f>> deltas;

	for (const auto& [bodyA, bodyB, points] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		const float aInvMass = aBody ? aBody->InvMass() : 0.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 0.0f;

		sf::Vector2f resolution = points.b - points.a;

		constexpr float percent = 0.8f;
		constexpr float slop = 0.01f;

		sf::Vector2f correction = points.normal * percent
			* std::fmax(Magnitude(resolution) - slop, 0.0f)
			/ (aInvMass + bInvMass);

		if (aBody ? aBody->IsKinematic() : false)
		{
			const sf::Vector2f deltaA = -aInvMass * correction;
			aBody->Trans()->position += deltaA;
		}

		if (bBody ? bBody->IsKinematic() : false)
		{
			const sf::Vector2f deltaB = bInvMass * correction;
			bBody->Trans()->position += deltaB;
		}
	}
}
