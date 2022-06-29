#include "Collisions.hpp"

#include <limits>

#include "VecUtils.hpp"
#include "Projection.hpp"
#include "Edge.hpp"
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
	sf::Vector2f circlePos = a->center + ta->position;
	sf::Vector2f boxPos = b->center + tb->position;

	const float circleRadius = a->radius * Major(ta->scale);
	const float scaledHalfWidth = b->width * tb->scale.x / 2.0f;
	const float scaledHalfHeight = b->height * tb->scale.y / 2.0f;

	return {};
}

CollisionPoints algo::FindBoxCircleCollisionPoints(const BoxCollider* a, const Transform* ta, const CircleCollider* b,
	const Transform* tb)
{
	// TODO : Implement
	return {};
}

CollisionPoints algo::FindBoxBoxCollisionPoints(
	const BoxCollider* a,
	const Transform* ta,
	const BoxCollider* b,
	const Transform* tb
)
{
	float overlap = std::numeric_limits<float>::max();
	sf::Vector2f smallestAxis;

	const auto verticesA = a->GetTransformedVertices(*ta);
	const auto verticesB = b->GetTransformedVertices(*tb);
	const auto axesA = BoxCollider::GetAxes(*ta, verticesA);
	const auto axesB = BoxCollider::GetAxes(*tb, verticesB);

	auto findCollision = [&](const sf::Vector2f& axis)
	{
		const Projection pA = BoxCollider::Project(axis, verticesA);
		const Projection pB = BoxCollider::Project(axis, verticesB);

		if (!pA.Overlap(pB))
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
			return CollisionPoints::Empty();
		}
	}

	for (const auto& axis : axesB)
	{
		if (!findCollision(axis))
		{
			return CollisionPoints::Empty();
		}
	}

	Edge edgeA = BoxCollider::GetBestEdge(smallestAxis, verticesA);
	Edge edgeB = BoxCollider::GetBestEdge(-smallestAxis, verticesB);

	Edge reference, incident;
	bool flip = false;

	if (std::abs(edgeA.VecDot(smallestAxis)) <= std::abs(edgeB.VecDot(smallestAxis)))
	{
		reference = edgeA;
		incident = edgeB;
	}
	else
	{
		reference = edgeB;
		incident = edgeA;
		flip = true;
	}

	sf::Vector2f referenceVector = Normalized(reference.EdgeVector());
	float o1 = Dot(referenceVector, reference.p1);

	// A Collision happenned 
	return {
	};
}

sf::Vector2f algo::Support(const Collider* colliderA, const Collider* colliderB, const sf::Vector2f& direction)
{
	return colliderA->FindFurthestPoint(direction) - colliderB->FindFurthestPoint(-direction);
}

bool algo::Gjk(const Collider* colliderA, const Collider* colliderB)
{
	sf::Vector2f support = Support(colliderA, colliderB, sf::Vector2f(1, 0));

	Simplex points;
	points.PushFront(support);

	// New direction is towards the origin
	sf::Vector2f direction = -support;

	while (true)
	{
		support = Support(colliderA, colliderB, direction);

		if (Dot(support, direction) <= 0)
		{
			return false;
		}

		points.PushFront(support);

		if (NextSimplex(points, direction))
		{
			return true;
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
