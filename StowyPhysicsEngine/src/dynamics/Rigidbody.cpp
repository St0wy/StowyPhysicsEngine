#include "dynamics/Rigidbody.hpp"

namespace stw
{
Rigidbody::Rigidbody()
	: _invMass(1),
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
	if (mass == 0)  // NOLINT(clang-diagnostic-float-equal)
	{
		_invMass = 0;
	}

	_invMass = 1.0f / mass;

	// If the mass is too big, the float becomes subnormal, so it's clamped to the closest float to 0
	if (std::fpclassify(_invMass) == FP_SUBNORMAL)
	{
		_invMass = std::numeric_limits<float>::min();
	}
}

bool Rigidbody::TakesGravity() const
{
	return _takesGravity;
}

void Rigidbody::SetTakesGravity(const bool takesGravity)
{
	_takesGravity = takesGravity;
	if (!_takesGravity)
	{
		SetGravityForce(Vector2(0, 0));
	}
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

void Rigidbody::SetDynamicFriction(const float dynamicFriction)
{
	_dynamicFriction = dynamicFriction;
}

float Rigidbody::Restitution() const
{
	return _restitution;
}

void Rigidbody::SetRestitution(const float restitution)
{
	_restitution = restitution;
}
}
