#pragma once

#include "Manifold.hpp"
#include "Collider.hpp"
#include "Simplex.hpp"
#include "Transform.hpp"

struct CollisionBody;

namespace algo
{
	Manifold FindCircleCirlceCollisionPoints(
		const CircleCollider* a, const Transform* ta,
		const CircleCollider* b, const Transform* tb);

	Manifold FindCircleBoxCollisionPoints(
		const CircleCollider* a, const Transform* ta,
		const BoxCollider* b, const Transform* tb);

	Manifold FindBoxCircleCollisionPoints(
		const BoxCollider* a, const Transform* ta,
		const CircleCollider* b, const Transform* tb);

	Manifold FindBoxBoxCollisionPoints(
		const BoxCollider* a, const Transform* ta,
		const BoxCollider* b, const Transform* tb);

	sf::Vector2f Support(
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB,
		const sf::Vector2f& direction
	);

	Manifold Gjk(
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB
	);

	bool NextSimplex(Simplex& points, sf::Vector2f& direction);
	bool SameDirection(sf::Vector2f direction, sf::Vector2f ao);

	bool Line(const Simplex& points, sf::Vector2f& direction);
	bool Triangle(Simplex& points, sf::Vector2f& direction);

	Manifold Epa(
		const Simplex& simplex,
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB
	);
}