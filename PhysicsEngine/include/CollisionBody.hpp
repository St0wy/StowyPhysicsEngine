#pragma once

#include <functional>

#include "Transform.hpp"
#include "Collider.hpp"
#include "Collisions.hpp"


struct CollisionBody
{
public:
	Transform* transform{};
	Collider* collider{};
	bool isTrigger = false;

	void SetCollisionCallback(const std::function<void(const Collision&, float)>& callback);
	void OnCollision(const Collision& collisions, float deltaTime) const;

	[[nodiscard]] bool IsDynamic() const;

protected:
	bool _isDynamic = false;
	std::function<void(const Collision&, float)> _onCollisions;
};
