#pragma once

#include <SFML/Graphics.hpp>
#include <memory>

#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/Rigidbody.hpp"

class Entity
	: public sf::Drawable, public sf::Transformable
{
public:
	explicit Entity(DynamicsWorld& dynWorld);
	Entity(DynamicsWorld& dynWorld, Vector2 pos);

	Rigidbody* RigidBody() const;

	void Push(Vector2 force) const;

	/**
	 * \brief The update function that is called at each frame.
	 * \param deltaTime Time elapsed since the last frame.
	 */
	virtual void Update(sf::Time deltaTime);

protected:
	DynamicsWorld& _dynWorld;
	std::unique_ptr<Rigidbody> _rb;
};