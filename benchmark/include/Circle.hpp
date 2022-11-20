#pragma once

#include "Entity.hpp"

#include "collision/Collider.hpp"

class Circle final : public Entity
{
public:
	Circle(stw::DynamicsWorld& dynWorld, float radius, stw::Vector2 pos);
private:
	std::unique_ptr<stw::CircleCollider> _collider;
};
