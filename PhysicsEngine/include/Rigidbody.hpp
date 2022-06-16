#pragma once

#include <SFML/System.hpp>

#include "CollisionBody.hpp"

struct Rigidbody : CollisionBody
{
public:
	sf::Vector2f gravityForce;
	sf::Vector2f force;
	sf::Vector2f velocity;

	float mass{};
	bool takesGravity{};

	float staticFriction{};
	float dynamicFriction{};
	float restitution{};

	void ApplyForce(const sf::Vector2f& addedForce);

	[[nodiscard]] sf::Vector2f Position() const;
	void SetPosition(const sf::Vector2f& position) const;
};