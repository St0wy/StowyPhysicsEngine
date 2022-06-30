#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"
#include "collision/Collider.hpp"

class Box : public Entity
{
public:
	Box(DynamicsWorld& dynWorld, sf::Vector2f size, sf::Vector2f pos);
	~Box() override;

	const sf::RectangleShape& Shape() const;

	void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
	sf::RectangleShape _shape;
	std::unique_ptr<BoxCollider> _collider;
	
};