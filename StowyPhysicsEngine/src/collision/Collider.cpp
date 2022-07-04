// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
#include "collision/Collider.hpp"

#include <array>

#include "collision/Manifold.hpp"
#include "collision/ManifoldFactory.hpp"

Manifold BoxCollider::TestCollision(const Transform* transform, const Collider* collider,
	const Transform* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

Manifold BoxCollider::TestCollision(const Transform* transform, const BoxCollider* collider,
	const Transform* boxTransform) const
{
	return algo::FindBoxBoxCollisionPoints(this, transform, collider, boxTransform);
}

Manifold BoxCollider::TestCollision(
	const Transform* transform,
	const CircleCollider* collider,
	const Transform* circleTransform
) const
{
	return algo::FindBoxCircleCollisionPoints(this, transform, collider, circleTransform);
}

Manifold BoxCollider::TestCollision(const Transform* transform, const AabbCollider* collider,
	const Transform* circleTransform) const
{
	// TODO : Implement
	return Manifold::Empty();
}

Vector2 BoxCollider::FindFurthestPoint(const Transform* transform, const Vector2& direction) const
{
	Vector2 maxPoint;
	float maxDistance = -std::numeric_limits<float>::max();

	for (const Vector2& vertex : GetTransformedVertices(*transform))
	{
		const float distance = vertex.Dot(direction);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = vertex;
		}
	}

	return maxPoint;
}

std::array<Vector2, 4> BoxCollider::GetVertices() const
{
	return GetTransformedVertices(
		{
			{0, 0},
			{1, 1},
			0
		}
	);
}

std::array<Vector2, 4> BoxCollider::GetTransformedVertices(const Transform& transform) const
{
	const float scaledHalfWidth = halfWidth * transform.scale.x;
	const float scaledHalfHeight = halfHeight * transform.scale.y;
	const Vector2 newCenter = center + transform.position;

	Vector2 topLeft = { newCenter.x - scaledHalfWidth, newCenter.y + scaledHalfHeight };
	Vector2 topRight = { newCenter.x + scaledHalfWidth, newCenter.y + scaledHalfHeight };
	Vector2 bottomRight = { newCenter.x + scaledHalfWidth, newCenter.y - scaledHalfHeight };
	Vector2 bottomLeft = { newCenter.x - scaledHalfWidth, newCenter.y - scaledHalfHeight };

	topLeft.RotateAround(newCenter, transform.rotation);
	topRight.RotateAround(newCenter, transform.rotation);
	bottomRight.RotateAround(newCenter, transform.rotation);
	bottomLeft.RotateAround(newCenter, transform.rotation);

	return
	{
		topLeft,
		topRight,
		bottomRight,
		bottomLeft,
	};
}

Manifold CircleCollider::TestCollision(const Transform* transform, const Collider* collider,
	const Transform* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

Manifold CircleCollider::TestCollision(const Transform* transform, const BoxCollider* collider,
	const Transform* boxTransform) const
{
	return algo::FindCircleBoxCollisionPoints(this, transform, collider, boxTransform);
}

Manifold CircleCollider::TestCollision(const Transform* transform, const CircleCollider* collider,
	const Transform* circleTransform) const
{
	return algo::FindCircleCirlceCollisionPoints(this, transform, collider, circleTransform);
}

Manifold CircleCollider::TestCollision(const Transform* transform, const AabbCollider* collider,
	const Transform* circleTransform) const
{
	// TODO : Implement
	return Manifold::Empty();
}

Vector2 CircleCollider::FindFurthestPoint(const Transform* transform, const Vector2& direction) const
{
	return center + transform->position + radius * direction.Normalized() * transform->scale.Major();
}

Manifold AabbCollider::TestCollision(const Transform* transform, const Collider* collider,
	const Transform* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

Manifold AabbCollider::TestCollision(const Transform* transform, const BoxCollider* collider,
	const Transform* boxTransform) const
{
	// TODO : Implement
	return Manifold::Empty();
}

Manifold AabbCollider::TestCollision(const Transform* transform, const CircleCollider* collider,
	const Transform* circleTransform) const
{
	// TODO : Implement
	return Manifold::Empty();
}

Manifold AabbCollider::TestCollision(const Transform* transform, const AabbCollider* collider,
	const Transform* aabbTransform) const
{
	return algo::FindAabbAabbCollisionPoints(this, transform, collider, aabbTransform);
}

Vector2 AabbCollider::FindFurthestPoint(const Transform* transform, const Vector2& direction) const
{
	return Vector2();
}
