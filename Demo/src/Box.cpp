#include "Box.hpp"

#include "MathUtils.hpp"

#include <spdlog/spdlog.h>

Box::Box(DynamicsWorld& dynWorld, const Vector2 size, const Vector2 pos)
	: Entity(dynWorld, pos),
	_shape(SpeVecToSfml(size)),
	_collider(std::make_unique<AabbCollider>())
{
	const Vector2 halfSize = size / 2.0f;
	_collider->halfWidth = halfSize.x;
	_collider->halfHeight = halfSize.y;
	_dynWorld.AddRigidbody(RigidBody());
	_rb->SetCollider(_collider.get());
	_shape.setOrigin(halfSize.x, halfSize.y);
	_rb->SetCollisionCallback([&](const Collision& col, float num)
	{
		_shape.setFillColor(sf::Color::Red);
	});
}

Box::~Box()
{
	_dynWorld.RemoveCollisionBody(RigidBody());
}

const sf::RectangleShape& Box::Shape() const
{
	return _shape;
}

void Box::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
	states.transform *= getTransform();
	target.draw(_shape, states);
}
