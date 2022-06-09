#pragma once

#include <SFML/System.hpp>

#include "Transform.hpp"
#include "Collider.hpp"
#include "Collisions.hpp"

#include <functional>

struct CollisionBody
{
public:
	[[nodiscard]] const Transform& GetTransform() const;
	void SetTransform(const Transform& transform) const;

	// TODO : Add getter setters


protected:
	Transform* _transform{};
	Collider* _collider{};
	bool _isTrigger = false;
	bool _isDynamic = false;

	std::function<void(const Collision&, float)> _onCollisions;
};

inline const Transform& CollisionBody::GetTransform() const
{
	return *_transform;
}

inline void CollisionBody::SetTransform(const Transform& transform) const
{
	*this->_transform = transform;
}
