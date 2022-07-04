#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "collision/Collider.hpp"

class Circle : public Entity
{
public:
	Circle(DynamicsWorld& dynWorld, float radius, Vector2 pos);
	~Circle() override;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::CircleShape _shape;
	std::unique_ptr<CircleCollider> _collider;
	
};