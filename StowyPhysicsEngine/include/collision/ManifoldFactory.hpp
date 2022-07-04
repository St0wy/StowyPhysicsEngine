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

	Manifold FindAabbAabbCollisionPoints(
		const AabbCollider* a, const Transform* ta,
		const AabbCollider* b, const Transform* tb);

	Manifold FindAabbCircleCollisionPoints(
		const AabbCollider* a, const Transform* ta,
		const CircleCollider* b, const Transform* tb);

	Vector2 Support(
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB,
		const Vector2& direction
	);

	Manifold Gjk(
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB
	);

	bool NextSimplex(const Simplex& points, Vector2& direction);
	bool SameDirection(Vector2 direction, Vector2 ao);

	bool Line(const Simplex& points, Vector2& direction);
	bool Triangle(const Simplex& points, Vector2& direction);

	Manifold Epa(
		const Simplex& simplex,
		const Collider* colliderA,
		const Transform* transformA,
		const Collider* colliderB,
		const Transform* transformB
	);
}