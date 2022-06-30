#pragma once

#include <SFML/System.hpp>

#include "collision/CollisionWorld.hpp"
#include "Rigidbody.hpp"

class DynamicsWorld : public CollisionWorld
{
public:
	void AddRigidbody(Rigidbody* rigidbody);
	void ApplyGravity() const;
	void MoveBodies(float deltaTime) const;
	void Step(float deltaTime) const;

private:
	sf::Vector2f _gravity = {0, 9.81f};
};
