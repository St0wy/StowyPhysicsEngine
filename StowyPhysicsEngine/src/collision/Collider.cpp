// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
#include "collision/Collider.hpp"

#include <array>

#include "collision/Manifold.hpp"
#include "VecUtils.hpp"
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

sf::Vector2f BoxCollider::FindFurthestPoint(const Transform* transform, const sf::Vector2f& direction) const
{
	sf::Vector2f maxPoint;
	float maxDistance = -std::numeric_limits<float>::max();

	for (const sf::Vector2f& vertex : GetTransformedVertices(*transform))
	{
		const float distance = Dot(vertex, direction);
		if (distance > maxDistance)
		{
			maxDistance = distance;
			maxPoint = vertex;
		}
	}

	return maxPoint;
}

std::array<sf::Vector2f, 4> BoxCollider::GetVertices() const
{
	return GetTransformedVertices(
		{
			{0, 0},
			{1, 1},
			0
		}
	);
}

std::array<sf::Vector2f, 4> BoxCollider::GetTransformedVertices(const Transform& transform) const
{
	const float scaledHalfWidth = halfWidth * transform.scale.x;
	const float scaledHalfHeight = halfHeight * transform.scale.y;
	const sf::Vector2f newCenter = center + transform.position;

	sf::Vector2f topLeft = { newCenter.x - scaledHalfWidth, newCenter.y + scaledHalfHeight };
	sf::Vector2f topRight = { newCenter.x + scaledHalfWidth, newCenter.y + scaledHalfHeight };
	sf::Vector2f bottomRight = { newCenter.x + scaledHalfWidth, newCenter.y - scaledHalfHeight };
	sf::Vector2f bottomLeft = { newCenter.x - scaledHalfWidth, newCenter.y - scaledHalfHeight };

	topLeft = RotateAround(topLeft, newCenter, transform.rotation);
	topRight = RotateAround(topRight, newCenter, transform.rotation);
	bottomRight = RotateAround(bottomRight, newCenter, transform.rotation);
	bottomLeft = RotateAround(bottomLeft, newCenter, transform.rotation);

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

sf::Vector2f CircleCollider::FindFurthestPoint(const Transform* transform, const sf::Vector2f& direction) const
{
	return center + transform->position + radius * Normalized(direction) * Major(transform->scale);
}
