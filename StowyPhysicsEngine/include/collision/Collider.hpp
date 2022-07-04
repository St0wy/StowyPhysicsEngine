#pragma once

#include <array>

#include "Manifold.hpp"
#include "Transform.hpp"

#include "math/Vector2.hpp"

struct CircleCollider;
struct BoxCollider;
struct AabbCollider;

struct Collider
{
public:
	Collider() = default;
	Collider(Collider&& col) noexcept = default;
	virtual ~Collider() = default;
	Collider& operator=(Collider&& col) = default;
	Collider& operator=(const Collider& col) = default;
	Collider(const Collider& col) = default;

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

	virtual Manifold TestCollision(
		const Transform* transform,
		const AabbCollider* collider,
		const Transform* circleTransform
	) const = 0;

	[[nodiscard]] virtual Vector2 FindFurthestPoint(
		const Transform* transform,
		const Vector2& direction
	) const = 0;
};

struct BoxCollider final : Collider
{
	Vector2 center;
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

	Manifold TestCollision(const Transform* transform, const AabbCollider* collider,
		const Transform* circleTransform) const override;

	[[nodiscard]] Vector2 FindFurthestPoint(
		const Transform* transform,
		const Vector2& direction
	) const override;

	[[nodiscard]] std::array<Vector2, 4> GetTransformedVertices(const Transform& transform) const;
	[[nodiscard]] std::array<Vector2, 4> GetVertices() const;
	
};

struct CircleCollider final : Collider
{
public:
	Vector2 center;
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

	Manifold TestCollision(const Transform* transform, const AabbCollider* collider,
		const Transform* circleTransform) const override;

	[[nodiscard]] Vector2 FindFurthestPoint(
		const Transform* transform,
		const Vector2& direction
	) const override;
};

struct AabbCollider final : Collider
{
	Vector2 center;
	float halfWidth;
	float halfHeight;

	Manifold TestCollision(const Transform* transform, const Collider* collider,
		const Transform* colliderTransform) const override;
	Manifold TestCollision(const Transform* transform, const BoxCollider* collider,
		const Transform* boxTransform) const override;
	Manifold TestCollision(const Transform* transform, const CircleCollider* collider,
		const Transform* circleTransform) const override;
	Manifold TestCollision(const Transform* transform, const AabbCollider* collider,
		const Transform* aabbTransform) const override;
	[[nodiscard]] Vector2 FindFurthestPoint(const Transform* transform, const Vector2& direction) const override;
};
