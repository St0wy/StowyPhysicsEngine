#include "Circle.hpp"

Circle::Circle(stw::DynamicsWorld& dynWorld, const float radius, const stw::Vector2 pos)
	: Entity(dynWorld, pos),
	_shape(radius),
	_collider(std::make_unique<stw::CircleCollider>())
{
	_collider->radius = radius;
	_dynWorld.AddRigidbody(RigidBody());
	_rb->SetCollider(_collider.get());
	_shape.setOrigin(radius, radius);
}

void Circle::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_shape, states);
}
