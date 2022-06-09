#pragma once

#include "CollisionPoints.hpp"
#include "Transform.hpp"

struct CircleCollider;
struct BoxCollider;

struct Collider
{
protected:
	~Collider() = default;
public:
	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const = 0;

	virtual CollisionPoints TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const = 0;
};

struct BoxCollider final : Collider
{
	sf::Vector2f center;
	float width;
	float height;

	CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override;

	CollisionPoints TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const override;

	CollisionPoints TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const override;
};

struct CircleCollider final : Collider
{
public:
	sf::Vector2f center;
	float radius;

	CollisionPoints TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override;

	CollisionPoints TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const override;

	CollisionPoints TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const override;
};
