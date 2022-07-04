#pragma once

#include "collision/CollisionWorld.hpp"
#include "Rigidbody.hpp"

class DynamicsWorld : public CollisionWorld
{
public:
	void AddRigidbody(Rigidbody* rigidbody);
	void ApplyGravity() const;
	void MoveBodies(float deltaTime) const;
	void Step(float deltaTime) const;
	void SetWorldGravity(Vector2 gravity);

private:
	Vector2 _gravity = {0, -9.81f};
};
