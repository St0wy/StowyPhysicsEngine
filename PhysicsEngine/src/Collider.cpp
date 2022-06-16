// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
#include "Collider.hpp"
#include "Collisions.hpp"
#include "CollisionPoints.hpp"

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