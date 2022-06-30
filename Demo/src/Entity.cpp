#include "Entity.hpp"

#include <memory>

#include "MathUtils.hpp"

Entity::Entity(DynamicsWorld& dynWorld)
	: Entity(dynWorld, sf::Vector2f(0, 0))
{

}

Entity::Entity(DynamicsWorld& dynWorld, const sf::Vector2f pos)
	: _dynWorld(dynWorld), _rb(std::make_unique<Rigidbody>())
{
	_rb->SetTransform({ pos, sf::Vector2f(1, 1), 0 });
	_rb->SetTakesGravity(true);
	_rb->SetIsKinematic(true);
}

Rigidbody* Entity::RigidBody() const
{
	return _rb.get();
}

void Entity::Push(const sf::Vector2f force) const
{
	_rb->ApplyForce(force);
}

void Entity::Update(sf::Time deltaTime)
{
	setPosition(SpeVecToSfml(_rb->Trans()->position));
	setScale(_rb->Trans()->scale);
	setRotation(_rb->Trans()->rotation);
}
