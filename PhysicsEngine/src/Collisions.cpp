#include "Collisions.hpp"

#include <limits>
#include <vector>

#include "VecUtils.hpp"
#include "Simplex.hpp"

CollisionPoints algo::FindCircleCirlceCollisionPoints(
	const CircleCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb)
{
	sf::Vector2f aPos = a->center + ta->position;
	sf::Vector2f bPos = b->center + tb->position;

	const float aRadius = a->radius * Major(ta->scale);
	const float bRadius = b->radius * Major(tb->scale);

	const sf::Vector2f aToB = bPos - aPos;
	const sf::Vector2f bToA = aPos - bPos;

	if (Magnitude(aToB) > aRadius + bRadius)
	{
		return CollisionPoints::Empty();
	}

	aPos += Normalized(aToB) * aRadius;
	bPos += Normalized(bToA) * bRadius;

	const sf::Vector2f collisionPointsDistance = bPos - aPos;

	return {
		aPos,
		bPos,
		Normalized(collisionPointsDistance),
		Magnitude(collisionPointsDistance),
		true
	};
}

CollisionPoints algo::FindCircleBoxCollisionPoints(
	const CircleCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return FindBoxCircleCollisionPoints(b, tb, a, ta);
}

CollisionPoints algo::FindBoxCircleCollisionPoints(const BoxCollider* a, const Transform* ta, const CircleCollider* b,
	const Transform* tb)
{
	return Gjk(a, ta, b, tb);
}

CollisionPoints algo::FindBoxBoxCollisionPoints(
	const BoxCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	return Gjk(a, ta, b, tb);
}

CollisionPoints algo::Sat(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
)
{
	// Not working, but I keep the code just in case
	//float overlap = std::numeric_limits<float>::max();
	//sf::Vector2f smallestAxis;

	//const auto verticesA = a->GetTransformedVertices(*ta);
	//const auto verticesB = b->GetTransformedVertices(*tb);
	//const auto axesA = BoxCollider::GetAxes(*ta, verticesA);
	//const auto axesB = BoxCollider::GetAxes(*tb, verticesB);

	//auto findCollision = [&](const sf::Vector2f& axis)
	//{
	//	const Projection pA = BoxCollider::Project(axis, verticesA);
	//	const Projection pB = BoxCollider::Project(axis, verticesB);

	//	if (!pA.Overlap(pB))
	//	{
	//		return false;
	//	}

	//	const float o = pA.GetOverlap(pB);

	//	if (o < overlap)
	//	{
	//		overlap = o;
	//		smallestAxis = axis;
	//	}

	//	return true;
	//};

	//for (const auto& axis : axesA)
	//{
	//	if (!findCollision(axis))
	//	{
	//		return CollisionPoints::Empty();
	//	}
	//}

	//for (const auto& axis : axesB)
	//{
	//	if (!findCollision(axis))
	//	{
	//		return CollisionPoints::Empty();
	//	}
	//}

	//CollisionPoints points;
	//points.normal = smallestAxis;
	//points.depth = overlap;
	//points.hasCollision = true;

	return {};
}

sf::Vector2f algo::Support(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB,
	const sf::Vector2f& direction
)
{
	return colliderA->FindFurthestPoint(transformA, direction) -
		colliderB->FindFurthestPoint(transformB, -direction);
}

CollisionPoints algo::Gjk(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
)
{
	sf::Vector2f support = Support(colliderA, transformA, colliderB, transformB, sf::Vector2f(1, 0));

	Simplex points;
	points.PushFront(support);

	// New direction is towards the origin
	sf::Vector2f direction = -support;

	while (true)
	{
		support = Support(colliderA, transformA, colliderB, transformB, direction);

		if (Dot(support, direction) <= 0)
		{
			return CollisionPoints::Empty();
		}

		points.PushFront(support);

		if (NextSimplex(points, direction))
		{
			return Epa(points, colliderA, transformA, colliderB, transformB);
		}
	}
}

bool algo::NextSimplex(Simplex& points, sf::Vector2f& direction)
{
	switch (points.Size())
	{
	case 2: return Line(points, direction);
	case 3: return Triangle(points, direction);
	default: return false;
	}
}

bool algo::SameDirection(const sf::Vector2f direction, const sf::Vector2f ao)
{
	return Dot(direction, ao) > 0;
}

bool algo::Line(Simplex& points, sf::Vector2f& direction)
{
	sf::Vector2f a = points[0];
	const sf::Vector2f b = points[0];
	const sf::Vector2f ab = b - a;
	const sf::Vector2f ao = -a;

	if (SameDirection(ab, ao))
	{
		direction = TripleProduct(ab, ao, ab);
	}
	else
	{
		points = { a };
		direction = ao;
	}

	return false;
}

bool algo::Triangle(Simplex& points, sf::Vector2f& direction)
{
	sf::Vector2f a = points[0];
	sf::Vector2f b = points[1];
	sf::Vector2f c = points[2];

	const sf::Vector2f ab = b - a;
	const sf::Vector2f ac = c - a;
	const sf::Vector2f ao = -a;

	const sf::Vector2f tripple = TripleProduct(ac, ac, ab);
	if (SameDirection(tripple, ao))
	{
		if (SameDirection(ac, ao))
		{
			points = { a, c };
			direction = TripleProduct(ac, ao, ac);
		}
		else
		{
			return Line(points = { a, b }, direction);
		}
	}
	else
	{
		if (SameDirection(TripleProduct(ab, ab, ac), ao))
		{
			return Line(points = { a, b }, direction);
		}
		return true;
	}

	return false;
}

CollisionPoints algo::Epa(
	const Simplex& simplex,
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
)
{
	std::vector polytope(simplex.Begin(), simplex.End());

	sf::Vector2f minNormal;
	float minDistance = std::numeric_limits<float>::infinity();
	std::size_t minIndex = 0;

	std::size_t iterations = 0;
	constexpr std::size_t maxIter = 30;
	while (minDistance == std::numeric_limits<float>::infinity())  // NOLINT(clang-diagnostic-float-equal)
	{
		if (iterations++ > maxIter)
		{
			break;
		}

		for (std::size_t i = 0; i < polytope.size(); ++i)
		{
			const std::size_t j = (i + 1) % polytope.size();

			sf::Vector2f vertexI = polytope[i];
			sf::Vector2f vertexJ = polytope[j];

			sf::Vector2f ij = vertexJ - vertexI;

			sf::Vector2f normal = Normalized(OppositeNormal(ij));
			float distance = Dot(normal, vertexI);

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

		sf::Vector2f support = Support(colliderA, transformA, colliderB, transformB, minNormal);
		const float sDistance = Dot(minNormal, support);

		if (std::abs(sDistance - minDistance) > 0.001f)
		{
			minDistance = std::numeric_limits<float>::infinity();
			const auto convIndex = static_cast<long long>(minIndex);
			polytope.insert(polytope.begin() + convIndex + 1ll, support);
		}
	}

	if (minDistance == std::numeric_limits<float>::infinity())  // NOLINT(clang-diagnostic-float-equal)
	{
		return CollisionPoints::Empty();
	}

	CollisionPoints points;
	points.normal = minNormal;
	points.depth = minDistance + 0.001f;
	points.hasCollision = true;

	return points;
}
