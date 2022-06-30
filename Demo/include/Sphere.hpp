#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "collision/Collider.hpp"

class Sphere : public Entity
{
public:
	Sphere(DynamicsWorld& dynWorld, float radius, sf::Vector2f pos);
	~Sphere() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::CircleShape _shape;
	std::unique_ptr<CircleCollider> _collider;
	
};