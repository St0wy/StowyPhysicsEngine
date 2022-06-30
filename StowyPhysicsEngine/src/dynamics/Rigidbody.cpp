#include "dynamics/Rigidbody.hpp"

Rigidbody::Rigidbody()
	:
	_mass(1),
	_takesGravity(true)
{
	_isDynamic = true;
}

const sf::Vector2f& Rigidbody::GravityForce() const
{
	return _gravityForce;
}

void Rigidbody::SetGravityForce(const sf::Vector2f& gravityForce)
{
	_gravityForce = gravityForce;
}

const sf::Vector2f& Rigidbody::Force() const
{
	return _force;
}

void Rigidbody::ApplyForce(const sf::Vector2f& addedForce)
{
	this->_force += addedForce;
}

void Rigidbody::SetForce(const sf::Vector2f& force)
{
	_force = force;
}

const sf::Vector2f& Rigidbody::Velocity() const
{
	return _velocity;
}

void Rigidbody::SetVelocity(const sf::Vector2f& velocity)
{
	_velocity = velocity;
}

float Rigidbody::Mass() const
{
	return _mass;
}

float Rigidbody::InvMass() const
{
	return 1.0f / Mass();
}

void Rigidbody::SetMass(const float mass)
{
	_mass = mass;
}

bool Rigidbody::TakesGravity() const
{
	return _takesGravity;
}

void Rigidbody::SetTakesGravity(const bool takesGravity)
{
	_takesGravity = takesGravity;
}

float Rigidbody::StaticFriction() const
{
	return _staticFriction;
}

void Rigidbody::SetStaticFriction(const float staticFriction)
{
	_staticFriction = staticFriction;
}

float Rigidbody::DynamicFriction() const
{
	return _dynamicFriction;
}

void Rigidbody::SetDynamicFriciton(const float dynamicFriciton)
{
	_dynamicFriction = dynamicFriciton;
}

float Rigidbody::Restitution() const
{
	return _restitution;
}

void Rigidbody::SetRestitution(const float restitution)
{
	_restitution = restitution;
}
