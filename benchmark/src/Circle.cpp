#include "Circle.hpp"

Circle::Circle(stw::DynamicsWorld& dynWorld, const float radius, const stw::Vector2 pos)
	: Entity(dynWorld, pos),
	_collider(std::make_unique<stw::CircleCollider>())
{
	_collider->radius = radius;
	_dynWorld.AddRigidbody(RigidBody());
	_rb->SetCollider(_collider.get());
}