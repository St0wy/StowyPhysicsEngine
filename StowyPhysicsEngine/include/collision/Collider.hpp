#pragma once

#include <array>

#include "Manifold.hpp"
#include "Transform.hpp"
#include "VecUtils.hpp"


struct CircleCollider;
struct BoxCollider;

struct Collider
{
protected:
	~Collider() = default;
public:
	virtual Manifold TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const = 0;

	virtual Manifold TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const = 0;

	virtual Manifold TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const = 0;

	[[nodiscard]] virtual sf::Vector2f FindFurthestPoint(
		const Transform* transform,
		const sf::Vector2f& direction
	) const = 0;
};

struct BoxCollider : Collider
{
	sf::Vector2f center;
	float halfWidth;
	float halfHeight;

	Manifold TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override;

	Manifold TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const override;

	Manifold TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const override;

	[[nodiscard]] sf::Vector2f FindFurthestPoint(
		const Transform* transform,
		const sf::Vector2f& direction
	) const override;

	[[nodiscard]] std::array<sf::Vector2f, 4> GetTransformedVertices(const Transform& transform) const;
	[[nodiscard]] std::array<sf::Vector2f, 4> GetVertices() const;
};

struct CircleCollider final : Collider
{
public:
	sf::Vector2f center;
	float radius;

	Manifold TestCollision(
		const Transform* transform,
		const Collider* collider,
		const Transform* colliderTransform
	) const override;

	Manifold TestCollision(
		const Transform* transform,
		const BoxCollider* collider,
		const Transform* boxTransform
	) const override;

	Manifold TestCollision(
		const Transform* transform,
		const CircleCollider* collider,
		const Transform* circleTransform
	) const override;

	[[nodiscard]] sf::Vector2f FindFurthestPoint(
		const Transform* transform,
		const sf::Vector2f& direction
	) const override;
};
