#pragma once

#include "CollisionPoints.hpp"
#include "Collider.hpp"
#include "Simplex.hpp"
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

	sf::Vector2f Support(const Collider* colliderA, const Collider* colliderB, const sf::Vector2f& direction);

	bool Gjk(const Collider* colliderA, const Collider* colliderB);
	bool NextSimplex(Simplex& points, sf::Vector2f& direction);
	bool SameDirection(const sf::Vector2f direction, const sf::Vector2f ao);

	bool Line(Simplex& points, sf::Vector2f& direction);
	bool Triangle(Simplex& points, sf::Vector2f& direction);
}

struct Collision
{
	CollisionBody* bodyA{};
	CollisionBody* bodyB{};
	CollisionPoints points;
};