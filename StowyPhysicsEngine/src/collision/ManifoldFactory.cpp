#include "collision/ManifoldFactory.hpp"

#include <limits>
#include <vector>
#include <spdlog/spdlog.h>

#include "collision/Collider.hpp"
#include "collision/Manifold.hpp"
#include "collision/Simplex.hpp"

Manifold algo::FindCircleCirlceCollisionPoints(
	const CircleCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb)
{
	Vector2 aPos = a->center + ta->position;
	Vector2 bPos = b->center + tb->position;

	const float aRadius = a->radius * ta->scale.Major();
	const float bRadius = b->radius * tb->scale.Major();

	const Vector2 aToB = bPos - aPos;
	const Vector2 bToA = aPos - bPos;

	if (aToB.Magnitude() > aRadius + bRadius)
	{
		return Manifold::Empty();
	}

	aPos += aToB.Normalized() * aRadius;
	bPos += bToA.Normalized() * bRadius;

	const Vector2 collisionPointsDistance = bPos - aPos;

	return {
		aPos,
		bPos,
		collisionPointsDistance.Normalized(),
		collisionPointsDistance.Magnitude(),
		true
	};
}

Manifold algo::FindCircleBoxCollisionPoints(
	const CircleCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return FindBoxCircleCollisionPoints(b, tb, a, ta);
}

Manifold algo::FindBoxCircleCollisionPoints(const BoxCollider* a, const Transform* ta, const CircleCollider* b,
	const Transform* tb)
{
	return Gjk(a, ta, b, tb);
}

Manifold algo::FindBoxBoxCollisionPoints(
	const BoxCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return Gjk(a, ta, b, tb);
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
		colliderA, transformA,
		colliderB, transformB,
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

bool algo::NextSimplex(Simplex& points, Vector2& direction)
{
	switch (points.Size())
	{
	case 2: return Line(points, direction);
	case 3: return Triangle(points, direction);
	default: return false;
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

bool algo::Triangle(Simplex& points, Vector2& direction)
{
	Vector2 a = points[0];
	Vector2 b = points[1];
	Vector2 c = points[2];

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
	while (minDistance == std::numeric_limits<float>::infinity())  // NOLINT(clang-diagnostic-float-equal)
	{
		if (iterations++ > maxIter)
		{
			spdlog::debug("Too many iterations. Breaking.");
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

	Manifold points;
	points.normal = minNormal;
	points.depth = minDistance;
	points.hasCollision = true;

	return points;
}
