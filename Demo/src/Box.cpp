#include "Box.hpp"

#include "MathUtils.hpp"

#include <spdlog/spdlog.h>

Box::Box(DynamicsWorld& dynWorld, const Vector2 size, const Vector2 pos, const bool takesGravity)
	: Entity(dynWorld, pos),
	_shape(SpeVecToSfml(size)),
	_collider(std::make_unique<BoxCollider>())
{
	const Vector2 halfSize = size / 2.0f;
	_collider->halfWidth = halfSize.x;
	_collider->halfHeight = halfSize.y;
	_rb->SetCollider(_collider.get());
	_rb->SetTakesGravity(takesGravity);
	_shape.setOrigin(halfSize.x, halfSize.y);
	_dynWorld.AddRigidbody(RigidBody());
}

Box::~Box()
{
	_dynWorld.RemoveCollisionBody(RigidBody());
}

sf::RectangleShape& Box::Shape()
{
	return _shape;
}

void Box::SetColor(const sf::Color& color)
{
	_shape.setFillColor(color);
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_shape, states);
}
