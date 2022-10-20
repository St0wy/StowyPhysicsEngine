#include "collision/ManifoldFactory.hpp"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

#include "collision/Collider.hpp"
#include "collision/Manifold.hpp"
#include "collision/Simplex.hpp"

namespace stw
{
Manifold algo::FindCircleCircleManifold(
	const CircleCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb)
{
	Vector2 aPos = a->center + ta->position;
	Vector2 bPos = b->center + tb->position;

	const float aRadius = a->radius * ta->scale.Major();
	const float bRadius = b->radius * tb->scale.Major();

	const Vector2 aToB = bPos - aPos;
	const Vector2 bToA = aPos - bPos;

	if (aToB.Magnitude() > aRadius + bRadius) return Manifold::Empty();

	aPos += aToB.NewMagnitude(aRadius);
	bPos += bToA.NewMagnitude(bRadius);

	const Vector2 collisionPointsDistance = bPos - aPos;

	return {
		aPos,
		bPos,
		collisionPointsDistance.Normalized(),
		collisionPointsDistance.Magnitude()
	};
}

Manifold algo::FindCircleBoxManifold(
	const CircleCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return FindBoxCircleManifold(b, tb, a, ta);
}

Manifold algo::FindBoxCircleManifold(const BoxCollider* a, const Transform* ta, const CircleCollider* b,
	const Transform* tb)
{
	return Gjk(a, ta, b, tb);
}

Manifold algo::FindBoxBoxManifold(
	const BoxCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return Gjk(a, ta, b, tb);
	//return Sat(a, ta, b, tb);
}

Manifold algo::FindAabbAabbManifold(
	const AabbCollider* a, const Transform* ta,
	const AabbCollider* b, const Transform* tb)
{
	const Vector2 transformedCenterA = ta->position + a->center;
	const float aScaledHWidth = a->halfWidth * ta->scale.x;
	const float aScaledHHeight = a->halfHeight * ta->scale.y;

	const Vector2 transformedCenterB = tb->position + b->center;
	const float bScaledHWidth = b->halfWidth * tb->scale.x;
	const float bScaledHHeight = b->halfHeight * tb->scale.y;

	const Vector2 aToB = transformedCenterB - transformedCenterA;
	const float xOverlap = aScaledHWidth + bScaledHWidth - std::abs(aToB.x);

	// Overlap test on x axis
	if (xOverlap <= 0.0f) return Manifold::Empty();

	const float yOverlap = aScaledHHeight + bScaledHHeight - std::abs(aToB.y);

	// Overlap test on y axis
	if (yOverlap <= 0.0f) return Manifold::Empty();

	// Find out which axis is axis of least penetration
	if (xOverlap > yOverlap)
	{
		// Point towards B knowing that aToB points from A to B
		Vector2 normal;

		float aY;
		float bY;
		if (aToB.y > 0.0f)
		{
			normal = Vector2(0.0f, -1.0f);
			aY = transformedCenterA.y + aScaledHHeight;
			bY = transformedCenterB.y - bScaledHHeight;
		}
		else
		{
			normal = Vector2(0.0f, 1.0f);
			aY = transformedCenterA.y - aScaledHHeight;
			bY = transformedCenterB.y + bScaledHHeight;
		}

		float x;
		if (aToB.x > 0.0f)
		{
			x = transformedCenterA.x + aScaledHWidth - xOverlap / 2.0f;
		}
		else
		{
			x = transformedCenterA.x - aScaledHWidth + xOverlap / 2.0f;
		}

		return { {x, aY},{x, bY}, normal, yOverlap };
	}

	// Point towards B knowing that aToB points from A to B
	Vector2 normal;

	float y;
	if (aToB.y > 0.0f)
	{
		y = transformedCenterA.x + aScaledHWidth - xOverlap / 2.0f;
	}
	else
	{
		y = transformedCenterA.x - aScaledHWidth + xOverlap / 2.0f;
	}

	float aX;
	float bX;
	if (aToB.x > 0.0f)
	{
		normal = Vector2(-1.0f, 0.0f);
		aX = transformedCenterA.x + aScaledHWidth;
		bX = transformedCenterB.x - bScaledHWidth;
	}
	else
	{
		normal = Vector2(1.0f, 0.0f);
		aX = transformedCenterA.x - aScaledHWidth;
		bX = transformedCenterB.x + bScaledHWidth;
	}
	return { {aX, y}, {bX, y}, normal, xOverlap };
}

Manifold algo::FindAabbCircleManifold(
	const AabbCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb)
{
	// Apply the transform to the AabbCollider
	const Vector2 aabbCenter = ta->position + a->center;
	const float scaledHWidth = a->halfWidth * ta->scale.x;
	const float scaledHHeight = a->halfHeight * ta->scale.y;

	// Apply the transform to the circle collider
	const Vector2 circleCenter = tb->position + b->center;
	const float scaledRadius = b->radius * tb->scale.Major();

	const Vector2 aabbToCircle = circleCenter - aabbCenter;

	Vector2 clampedPoint;

	// Clamp point to the edge of the AABB
	clampedPoint.x = std::clamp(aabbToCircle.x, -scaledHWidth, scaledHWidth);
	clampedPoint.y = std::clamp(aabbToCircle.y, -scaledHHeight, scaledHHeight);

	bool isCircleCenterInside = false;

	// If they're equal, the center of the circle is inside the AABB
	if (clampedPoint == aabbToCircle)
	{
		isCircleCenterInside = true;

		// We still want one point on the side of the AABB, so we find the nearest border, and clamp on it
		const float distToPosWidth = std::abs(scaledHWidth - clampedPoint.x);
		const float distToNegWidth = std::abs(-scaledHWidth - clampedPoint.x);
		const float distToPosHeight = std::abs(scaledHHeight - clampedPoint.y);
		const float distToNegHeight = std::abs(-scaledHHeight - clampedPoint.y);

		const float smallest = std::min({ distToPosWidth, distToNegWidth, distToPosHeight, distToNegHeight });

		if (smallest == distToPosWidth) // NOLINT(clang-diagnostic-float-equal)
		{
			clampedPoint.x = scaledHWidth;
		}
		else if (smallest == distToNegWidth) // NOLINT(clang-diagnostic-float-equal)
		{
			clampedPoint.x = -scaledHWidth;
		}
		else if (smallest == distToPosHeight) // NOLINT(clang-diagnostic-float-equal)
		{
			clampedPoint.y = scaledHHeight;
		}
		else if (smallest == distToNegHeight) // NOLINT(clang-diagnostic-float-equal)
		{
			clampedPoint.y = -scaledHHeight;
		}
	}

	// Put the point in "world space" because it was relative to the center
	const Vector2 closestPointOnAabb = aabbCenter + clampedPoint;

	const Vector2 circleToClosestPoint = closestPointOnAabb - circleCenter;

	// Distance between the circle center and the clamped point
	const float squaredDistance = circleToClosestPoint.SqrMagnitude();

	if (!isCircleCenterInside && squaredDistance >= scaledRadius * scaledRadius) return Manifold::Empty();

	// This is the collision point around the circle
	Vector2 aroundCirclePoint = circleToClosestPoint.NewMagnitude(scaledRadius);
	if (isCircleCenterInside)
	{
		aroundCirclePoint = -aroundCirclePoint;
	}

	Vector2 worldAroundCirclePoint = aroundCirclePoint + circleCenter;

	const Vector2 diff = worldAroundCirclePoint - closestPointOnAabb;

	//return { closestPointOnAabb, worldAroundCirclePoint, circleToClosestPoint, depth };
	return { closestPointOnAabb, worldAroundCirclePoint, diff.Normalized(), diff.Magnitude() };
}

Manifold algo::FindCircleAabbManifold(const CircleCollider* a, const Transform* ta, const AabbCollider* b,
	const Transform* tb)
{
	return FindAabbCircleManifold(b, tb, a, ta).Swaped();
}

Vector2 algo::Support(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB,
	const Vector2& direction
)
{
	return colliderA->FindFurthestPoint(transformA, direction) -
		colliderB->FindFurthestPoint(transformB, -direction);
}

Manifold algo::Gjk(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
)
{
	Vector2 direction = Vector2::Normalize(transformB->position - transformA->position);

	Vector2 support = Support(
		colliderA,
		transformA,
		colliderB,
		transformB,
		direction);

	Simplex points;
	points.PushFront(support);

	// New direction is towards the origin
	direction = Vector2::Normalize(-support);

	while (true)
	{
		support = Support(colliderA, transformA, colliderB, transformB, direction);

		if (support.Dot(direction) <= 0)
		{
			return Manifold::Empty();
		}

		points.PushFront(support);

		if (NextSimplex(points, direction))
		{
			return Epa(points, colliderA, transformA, colliderB, transformB);
		}
	}
}

bool algo::NextSimplex(const Simplex& points, Vector2& direction)
{
	switch (points.Size())
	{
	case 2:
		return Line(points, direction);
	case 3:
		return Triangle(points, direction);
	default:
		return false;
	}
}

bool algo::SameDirection(const Vector2 direction, const Vector2 ao)
{
	return direction.Dot(ao) > 0;
}

bool algo::Line(const Simplex& points, Vector2& direction)
{
	const Vector2 a = points[0];
	const Vector2 b = points[1];
	const Vector2 ab = Vector2::Normalize(b - a);
	const Vector2 ao = Vector2::Normalize(-a);
	direction = Vector2::TripleProduct(ab, ao, ab);

	return false;
}

bool algo::Triangle(const Simplex& points, Vector2& direction)
{
	const Vector2 a = points[0];
	const Vector2 b = points[1];
	const Vector2 c = points[2];

	const Vector2 ab = Vector2::Normalize(b - a);
	const Vector2 ac = Vector2::Normalize(c - a);
	const Vector2 ao = Vector2::Normalize(-a);

	//const Vector2 tripple = TripleProduct(ac, ac, ab);
	const Vector2 abf = Vector2::TripleProduct(ac, ab, ab);
	const Vector2 acf = Vector2::TripleProduct(ab, ac, ac);

	if (SameDirection(abf, ao))
	{
		direction = abf;
		return false;
		//return Line(points = { a, b }, direction);
	}
	if (SameDirection(acf, ao))
	{
		direction = acf;
		return false;
		//return Line(points = { a, c }, direction);
	}
	return true;
}

Manifold algo::Epa(
	const Simplex& simplex,
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
)
{
	std::vector polytope(simplex.Begin(), simplex.End());

	Vector2 minNormal;
	float minDistance = std::numeric_limits<float>::infinity();
	std::size_t minIndex = 0;

	std::size_t iterations = 0;
	constexpr std::size_t maxIter = 30;
	while (minDistance == std::numeric_limits<float>::infinity()) // NOLINT(clang-diagnostic-float-equal)
	{
		if (iterations++ > maxIter)
		{
			break;
		}

		for (std::size_t i = 0; i < polytope.size(); i++)
		{
			const std::size_t j = (i + 1) % polytope.size();

			Vector2 vertexI = polytope[i];
			Vector2 vertexJ = polytope[j];

			Vector2 ij = vertexJ - vertexI;

			Vector2 normal = ij.NegativePerpendicular().Normalized();
			float distance = normal.Dot(vertexI);

			if (distance < 0.0f)
			{
				distance *= -1.0f;
				normal *= -1.0f;
			}

			if (distance < minDistance)
			{
				minDistance = distance;
				minNormal = normal;
				minIndex = i;
			}
		}

		Vector2 support = Support(colliderA, transformA, colliderB, transformB, minNormal);
		const float sDistance = minNormal.Dot(support);

		if (std::abs(sDistance - minDistance) > 0.001f)
		{
			minDistance = std::numeric_limits<float>::infinity();
			const auto convIndex = static_cast<long long>(minIndex);
			polytope.insert(polytope.begin() + convIndex + 1ll, support);
		}
	}

	if (minDistance == std::numeric_limits<float>::infinity()) // NOLINT(clang-diagnostic-float-equal)
	{
		return Manifold::Empty();
	}

	return { minNormal, minDistance };
}

Manifold algo::Sat(
	const BoxCollider* colliderA, const Transform* transformA,
	const BoxCollider* colliderB, const Transform* transformB
)
{
	float overlap = std::numeric_limits<float>::max();
	Vector2 smallestAxis;

	const auto verticesA = colliderA->GetTransformedVertices(*transformA);
	const auto verticesB = colliderB->GetTransformedVertices(*transformB);

	const auto axesA = BoxCollider::GetAxes(verticesA);
	const auto axesB = BoxCollider::GetAxes(verticesB);

	auto findCollision = [&](const Vector2 axis)
	{
		const Projection pA = BoxCollider::Project(axis, verticesA);
		const Projection pB = BoxCollider::Project(axis, verticesB);

		if (!pA.Overlaps(pB))
		{
			return false;
		}

		const float o = pA.GetOverlap(pB);

		if (o < overlap)
		{
			overlap = o;
			smallestAxis = axis;
		}

		return true;
	};

	for (const auto& axis : axesA)
	{
		if (!findCollision(axis))
		{
			return Manifold::Empty();
		}
	}

	for (const auto& axis : axesB)
	{
		if (!findCollision(axis))
		{
			return Manifold::Empty();
		}
	}

	return { smallestAxis, overlap };
}
}
