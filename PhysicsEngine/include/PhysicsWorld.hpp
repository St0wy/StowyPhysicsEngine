#pragma once

#include <vector>

#include "Body.hpp"

class PhysicsWorld
{
public:
	void AddBody(Body* body);
	void RemoveBody(Body* body);

	void Step(float deltaTime) const;

private:
	std::vector<Body*> _bodies;
	sf::Vector2f _gravity;
};
