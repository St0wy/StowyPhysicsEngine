// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
#include "Collider.hpp"

#include <array>

#include "Collisions.hpp"
#include "CollisionPoints.hpp"
#include "VecUtils.hpp"

CollisionPoints BoxCollider::TestCollision(const Transform* transform, const Collider* collider,
	const Transform* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

CollisionPoints BoxCollider::TestCollision(const Transform* transform, const BoxCollider* collider,
	const Transform* boxTransform) const
{
	return algo::FindBoxBoxCollisionPoints(this, transform, collider, boxTransform);
}

CollisionPoints BoxCollider::TestCollision(const Transform* transform, const CircleCollider* collider,
	const Transform* circleTransform) const
{
	return algo::FindBoxCircleCollisionPoints(this, transform, collider, circleTransform);
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
	const float halfWidth = width / 2.0f * transform.scale.x;
	const float halfHeight = height / 2.0f * transform.scale.y;
	const sf::Vector2f newCenter = center + transform.position;

	sf::Vector2f topLeft = { newCenter.x - halfWidth, newCenter.y + halfHeight };
	sf::Vector2f topRight = { newCenter.x + halfWidth, newCenter.y + halfHeight };
	sf::Vector2f bottomRight = { newCenter.x - halfWidth, newCenter.y - halfHeight };
	sf::Vector2f bottomLeft = { newCenter.x + halfWidth, newCenter.y - halfHeight };

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

std::array<sf::Vector2f, 4> BoxCollider::GetAxes(
	const Transform& transform,
	const std::array<sf::Vector2f, 4>& vertices
)
{
	std::array<sf::Vector2f, 4> axes;

	for (std::size_t i = 0; i < vertices.size(); ++i)
	{
		sf::Vector2f p1 = vertices[i];
		sf::Vector2f p2 = vertices[i + 1 % vertices.size()];
		sf::Vector2f edge = p1 - p2;
		sf::Vector2f normal = Normal(edge);
		axes[i] = Normalized(normal);
	}

	return axes;
}

Projection BoxCollider::Project(const sf::Vector2f& axis, const std::array<sf::Vector2f, 4>& vertices)
{
	float min = Dot(axis, vertices[0]);
	float max = min;

	for (const sf::Vector2f& vertex : vertices)
	{
		const float p = Dot(axis, vertex);
		if (p < min)
		{
			min = p;
		}
		else if (p > max)
		{
			max = p;
		}
	}

	return { min, max };
}

Edge BoxCollider::GetBestEdge(const sf::Vector2f& separationNormal, const std::array<sf::Vector2f, 4>& vertices)
{
	float max = -std::numeric_limits<float>::max();
	std::size_t index = 0;
	for (std::size_t i = 0; i < vertices.size(); ++i)
	{
		const float projection = Dot(separationNormal, vertices[i]);
		if (projection > max)
		{
			max = projection;
			index = i;
		}
	}

	const sf::Vector2f v = vertices[index];
	const sf::Vector2f v1 = vertices[index + 1 % vertices.size()];
	const sf::Vector2f v0 = vertices[index - 1 % vertices.size()];

	// TODO : Check that they both point towards the maximum point
	const sf::Vector2f v1ToV = Normalized(v - v1);
	const sf::Vector2f v0ToV = Normalized(v - v0);

	if (Dot(v0ToV, separationNormal) <= Dot(v1ToV, separationNormal))
	{
		return { v, v0, v };
	}
	return { v, v, v1 };
}

CollisionPoints CircleCollider::TestCollision(const Transform* transform, const Collider* collider,
	const Transform* colliderTransform) const
{
	return collider->TestCollision(colliderTransform, this, transform);
}

CollisionPoints CircleCollider::TestCollision(const Transform* transform, const BoxCollider* collider,
	const Transform* boxTransform) const
{
	return algo::FindCircleBoxCollisionPoints(this, transform, collider, boxTransform);
}

CollisionPoints CircleCollider::TestCollision(const Transform* transform, const CircleCollider* collider,
	const Transform* circleTransform) const
{
	return algo::FindCircleCirlceCollisionPoints(this, transform, collider, circleTransform);
}