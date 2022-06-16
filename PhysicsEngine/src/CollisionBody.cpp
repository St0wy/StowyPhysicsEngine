#include "CollisionBody.hpp"

Transform* CollisionBody::Trans()
{
	return &_transform;
}

void CollisionBody::SetTransform(const Transform& transform)
{
	_transform = transform;
}

Collider* CollisionBody::Col() const
{
	return _collider;
}

void CollisionBody::SetCollider(Collider* collider)
{
	_collider = collider;
}

bool CollisionBody::IsTrigger() const
{
	return _isTrigger;
}

void CollisionBody::SetIsTrigger(const bool isTrigger)
{
	_isTrigger = isTrigger;
}

void CollisionBody::SetCollisionCallback(const std::function<void(const Collision&, float)>& callback)
{
	_onCollisions = callback;
}

void CollisionBody::OnCollision(const Collision& collision, const float deltaTime) const
{
	if (_onCollisions)
	{
		_onCollisions(collision, deltaTime);
	}
}

const sf::Vector2f& CollisionBody::Position() const
{
	return _transform.position;
}

void CollisionBody::SetPosition(const sf::Vector2f& position)
{
	_transform.position = position;
}

bool CollisionBody::IsDynamic() const
{
	return _isDynamic;
}
