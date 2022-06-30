#include "Sphere.hpp"

Sphere::Sphere(DynamicsWorld& dynWorld, const float radius, const sf::Vector2f pos)
	: Entity(dynWorld, pos),
	_shape(radius),
	_collider(std::make_unique<CircleCollider>())
{
	_collider->radius = radius;
	_dynWorld.AddRigidbody(RigidBody());
	_rb->SetCollider(_collider.get());
}

Sphere::~Sphere()
{
	_dynWorld.RemoveCollisionBody(RigidBody());
}

void Sphere::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_shape, states);
}
