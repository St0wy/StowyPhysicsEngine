#include "Entity.hpp"

#include <memory>

#include "MathUtils.hpp"

Entity::Entity(DynamicsWorld& dynWorld)
	: Entity(dynWorld, Vector2(0, 0))
{

}

Entity::Entity(DynamicsWorld& dynWorld, const Vector2 pos)
	: _dynWorld(dynWorld), _rb(std::make_unique<Rigidbody>())
{
	_rb->SetTransform({ pos, Vector2(1, 1), 0 });
	_rb->SetTakesGravity(true);
	_rb->SetIsKinematic(true);
	_rb->SetRestitution(1.0f);
}

Rigidbody* Entity::RigidBody() const
{
	return _rb.get();
}

void Entity::Push(const Vector2 force) const
{
	auto vel = _rb->Velocity();
	vel += force;
	_rb->SetVelocity(force);
}

void Entity::Update(sf::Time deltaTime)
{
	setPosition(SpePosToSfml(_rb->Trans()->position));
	setScale(SpeVecToSfml(_rb->Trans()->scale));
	setRotation(_rb->Trans()->rotation);
}
