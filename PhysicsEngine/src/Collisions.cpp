#include "Collisions.hpp"

#include <limits>

#include "VecUtils.hpp"
#include "Projection.hpp"
#include "Edge.hpp"

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
