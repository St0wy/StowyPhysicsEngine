#pragma once

#include "CollisionBody.hpp"

struct Collision
{
	CollisionBody* bodyA{};
	CollisionBody* bodyB{};
	Manifold manifold;
};