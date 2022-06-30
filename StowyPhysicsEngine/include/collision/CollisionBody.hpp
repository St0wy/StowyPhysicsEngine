#pragma once

#include <functional>

#include "Transform.hpp"
#include "Collider.hpp"
#include "Collisions.hpp"

struct Collision;

struct CollisionBody
{
public:
	Transform* Trans();
	void SetTransform(const Transform& transform);

	Transform* LastTransform();
	void UpdateLastTransform();

	[[nodiscard]] Collider* Col() const;
	void SetCollider(Collider* collider);

	[[nodiscard]] bool IsTrigger() const;
	void SetIsTrigger(bool isTrigger);

	void SetCollisionCallback(const std::function<void(const Collision&, float)>& callback);
	void OnCollision(const Collision& collision, float deltaTime) const;

	[[nodiscard]] const sf::Vector2f& Position() const;
	void SetPosition(const sf::Vector2f& position);

	[[nodiscard]] bool IsKinematic() const;
	void SetIsKinematic(bool isKinematic);

	[[nodiscard]] bool IsDynamic() const;

protected:
	Transform _transform{};
	Transform _lastTransform{};
	Collider* _collider{};

	bool _isTrigger = false;
	bool _isKinematic = false;
	bool _isDynamic = false;

	std::function<void(const Collision&, float)> _onCollisions;
};
