#pragma once

#include <SFML/System.hpp>

#include "collision/CollisionBody.hpp"

struct Rigidbody : public CollisionBody
{
public:
	Rigidbody();

	[[nodiscard]] const sf::Vector2f& GravityForce() const;
	void SetGravityForce(const sf::Vector2f& gravityForce);

	[[nodiscard]] const sf::Vector2f& Force() const;
	void ApplyForce(const sf::Vector2f& addedForce);
	void SetForce(const sf::Vector2f& force);

	[[nodiscard]] const sf::Vector2f& Velocity() const;
	void SetVelocity(const sf::Vector2f& velocity);

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
	sf::Vector2f _gravityForce;
	sf::Vector2f _force;
	sf::Vector2f _velocity;

	float _mass{};
	bool _takesGravity{};

	float _staticFriction{};
	float _dynamicFriction{};
	float _restitution{};
};
