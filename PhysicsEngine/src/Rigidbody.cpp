#include "Rigidbody.hpp"

void Rigidbody::ApplyForce(const sf::Vector2f& addedForce)
{
	this->force += addedForce;
}

sf::Vector2f Rigidbody::Position() const
{
	return transform->position;
}

void Rigidbody::SetPosition(const sf::Vector2f& position) const
{
	transform->position = position;
}
