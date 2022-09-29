#pragma once

#include <SFML/Graphics.hpp>

#include "Entity.hpp"

#include "collision/Collider.hpp"

class AabbBox final : public Entity
{
public:
    AabbBox(stw::DynamicsWorld& dynWorld, stw::Vector2 size, stw::Vector2 pos, bool takesGravity);

    sf::RectangleShape& Shape();
    void SetColor(const sf::Color& color);

    void Update(sf::Time deltaTime) override;
    void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
private:
    sf::RectangleShape _shape;
    std::unique_ptr<stw::AabbCollider> _collider;
};
