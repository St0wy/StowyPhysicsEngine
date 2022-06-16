#include "Collisions.hpp"

#include "VecUtils.hpp"

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

	const sf::Vector2f scaledAToB = bPos - aPos;

	return {
		aPos,
		bPos,
		Normalized(scaledAToB),
		Magnitude(scaledAToB),
		true
	};
}

CollisionPoints algo::FindCircleBoxCollisionPoints(const CircleCollider* a, const Transform* ta, const BoxCollider* b,
	const Transform* tb)
{
	// TODO : Implement
	return {};
}

CollisionPoints algo::FindBoxCircleCollisionPoints(const BoxCollider* a, const Transform* ta, const CircleCollider* b,
	const Transform* tb)
{
	// TODO : Implement
	return {};
}

CollisionPoints algo::FindBoxBoxCollisionPoints(const BoxCollider* a, const Transform* ta, const BoxCollider* b,
	const Transform* tb)
{
	// TODO : Implement
	return {};
}
