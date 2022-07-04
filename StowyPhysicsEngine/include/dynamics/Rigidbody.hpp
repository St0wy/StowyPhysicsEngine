#pragma once

#include "collision/CollisionBody.hpp"

struct Rigidbody : public CollisionBody
{
public:
	Rigidbody();

	[[nodiscard]] const Vector2& GravityForce() const;
	void SetGravityForce(const Vector2& gravityForce);

	[[nodiscard]] const Vector2& Force() const;
	void ApplyForce(const Vector2& addedForce);
	void SetForce(const Vector2& force);

	[[nodiscard]] const Vector2& Velocity() const;
	void SetVelocity(const Vector2& velocity);

	[[nodiscard]] float Mass() const;
	[[nodiscard]] float InvMass() const;
	void SetMass(float mass);

	[[nodiscard]] bool TakesGravity() const;
	void SetTakesGravity(bool takesGravity);

	[[nodiscard]] float StaticFriction() const;
	void SetStaticFriction(float staticFriction);

	[[nodiscard]] float DynamicFriction() const;
	void SetDynamicFriciton(float dynamicFriciton);

	[[nodiscard]] float Restitution() const;
	void SetRestitution(float restitution);

private:
	Vector2 _gravityForce;
	Vector2 _force;
	Vector2 _velocity;

	float _invMass{};
	bool _takesGravity{};

	float _staticFriction{};
	float _dynamicFriction{};
	float _restitution{};
};
