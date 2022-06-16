#pragma once

#include "CollisionPoints.hpp"
#include "Collider.hpp"
#include "Transform.hpp"

struct CollisionBody;

namespace algo
{
	CollisionPoints FindCircleCirlceCollisionPoints(
		const CircleCollider* a, const Transform* ta,
		const CircleCollider* b, const Transform* tb);

	CollisionPoints FindCircleBoxCollisionPoints(
		const CircleCollider* a, const Transform* ta,
		const BoxCollider* b, const Transform* tb);

	CollisionPoints FindBoxCircleCollisionPoints(
		const BoxCollider* a, const Transform* ta,
		const CircleCollider* b, const Transform* tb);

	CollisionPoints FindBoxBoxCollisionPoints(
		const BoxCollider* a, const Transform* ta,
		const BoxCollider* b, const Transform* tb);
}

struct Collision
{
	CollisionBody* bodyA{};
	CollisionBody* bodyB{};
	CollisionPoints points;
};