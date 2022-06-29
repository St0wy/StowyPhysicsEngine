#pragma once

#include <array>

#include "CollisionPoints.hpp"
#include "Transform.hpp"
#include "Projection.hpp"
#include "Edge.hpp"


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

	[[nodiscard]] virtual sf::Vector2f FindFurthestPoint(const sf::Vector2f& direction) const = 0;
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

	[[nodiscard]] sf::Vector2f FindFurthestPoint(const sf::Vector2f& direction) const override;
	
	[[nodiscard]] std::array<sf::Vector2f, 4> GetVertices() const;
	[[nodiscard]] std::array<sf::Vector2f, 4> GetTransformedVertices(const Transform& transform) const;
	[[nodiscard]] static std::array<sf::Vector2f, 4> GetAxes(
		const Transform& transform,
		const std::array<sf::Vector2f, 4>& vertices
	);
	static Projection Project(const sf::Vector2f& axis, const std::array<sf::Vector2f, 4>& vertices);
	static Edge GetBestEdge(const sf::Vector2f& separationNormal, const std::array<sf::Vector2f, 4>& vertices);
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
