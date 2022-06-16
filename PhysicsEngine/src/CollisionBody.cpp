#include "CollisionBody.hpp"

void CollisionBody::SetCollisionCallback(const std::function<void(const Collision&, float)>& callback)
{
	_onCollisions = callback;
}

void CollisionBody::OnCollision(const Collision& collision, const float deltaTime) const
{
	if(_onCollisions)
	{
		_onCollisions(collision, deltaTime);
	}
}

bool CollisionBody::IsDynamic() const
{
	return _isDynamic;
}
