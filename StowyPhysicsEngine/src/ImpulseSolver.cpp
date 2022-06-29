#include "ImpulseSolver.hpp"

#include "Rigidbody.hpp"
#include "VecUtils.hpp"

void ImpulseSolver::Solve(const std::vector<Collision>& collisions, float deltaTime)
{
	for (const auto& [bodyA, bodyB, points] : collisions)
	{
		// ReSharper disable CppCStyleCast
		Rigidbody* aBody = bodyA->IsDynamic() ? (Rigidbody*)bodyA : nullptr;
		Rigidbody* bBody = bodyB->IsDynamic() ? (Rigidbody*)bodyB : nullptr;
		// ReSharper restore CppCStyleCast

		sf::Vector2f aVel = aBody ? aBody->Velocity() : sf::Vector2f(0, 0);
		sf::Vector2f bVel = bBody ? bBody->Velocity() : sf::Vector2f(0, 0);
		sf::Vector2f rVel = bVel - aVel;
		float nVel = Dot(rVel, points.normal);

		if (nVel >= 0) continue;

		const float aInvMass = aBody ? aBody->InvMass() : 0.0f;
		const float bInvMass = bBody ? bBody->InvMass() : 0.0f;

		// Impulse

		const float e = (aBody ? aBody->Restitution() : 0.0f) * (bBody ? bBody->Restitution() : 0.0f);
		const float j = -(1.0f + e) * nVel / (aInvMass + bInvMass);

		sf::Vector2f impulse = j * points.normal;

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
		nVel = Dot(rVel, points.normal);

		sf::Vector2f tangent = Normalized(rVel - nVel * points.normal);
		const float fVel = Dot(rVel, tangent);

		const float aSf = aBody ? aBody->StaticFriction() : 0.0f;
		const float bSf = bBody ? bBody->StaticFriction() : 0.0f;
		const float aDf = aBody ? aBody->DynamicFriction() : 0.0f;
		const float bDf = bBody ? bBody->DynamicFriction() : 0.0f;
		float mu = Magnitude(sf::Vector2f(aSf, bSf));
		const float f = -fVel / (aInvMass + bInvMass);

		sf::Vector2f friction;
		if (std::abs(f) < j * mu)
		{
			friction = f * tangent;
		}
		else
		{
			mu = Magnitude(sf::Vector2f(aDf, bDf));
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
