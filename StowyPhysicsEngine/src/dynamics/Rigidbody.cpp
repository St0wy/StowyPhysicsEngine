#include "dynamics/Rigidbody.hpp"

Rigidbody::Rigidbody()
	:
	_invMass(1),
	_takesGravity(true)
{
	_isDynamic = true;
}

const Vector2& Rigidbody::GravityForce() const
{
	return _gravityForce;
}

void Rigidbody::SetGravityForce(const Vector2& gravityForce)
{
	_gravityForce = gravityForce;
}

const Vector2& Rigidbody::Force() const
{
	return _force;
}

void Rigidbody::ApplyForce(const Vector2& addedForce)
{
	this->_force += addedForce;
}

void Rigidbody::SetForce(const Vector2& force)
{
	_force = force;
}

const Vector2& Rigidbody::Velocity() const
{
	return _velocity;
}

void Rigidbody::SetVelocity(const Vector2& velocity)
{
	_velocity = velocity;
}

float Rigidbody::Mass() const
{
	return 1.0f / _invMass;
}

float Rigidbody::InvMass() const
{
	return _invMass;
}

void Rigidbody::SetMass(const float mass)
{
	_invMass = 1.0f / mass;
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
