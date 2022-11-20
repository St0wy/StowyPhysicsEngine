#include "AabbBox.hpp"

AabbBox::AabbBox(stw::DynamicsWorld& dynWorld, const stw::Vector2 size, const stw::Vector2 pos, const bool takesGravity)
	: Entity(dynWorld, pos),
	_collider(std::make_unique<stw::AabbCollider>())
{
	const stw::Vector2 halfSize = size / 2.0f;
	_collider->halfWidth = halfSize.x;
	_collider->halfHeight = halfSize.y;
	_rb->SetCollider(_collider.get());
	_rb->SetTakesGravity(takesGravity);
	_dynWorld.AddRigidbody(RigidBody());
}