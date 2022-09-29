#pragma once

#include <memory>

#include <SFML/Graphics.hpp>

#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/Rigidbody.hpp"

class Entity
    : public sf::Drawable, public sf::Transformable
{
public:
    explicit Entity(stw::DynamicsWorld& dynWorld);
    Entity(stw::DynamicsWorld& dynWorld, stw::Vector2 pos);
    ~Entity() override;

    stw::Rigidbody* RigidBody() const;

    void Push(stw::Vector2 force) const;

    /**
     * \brief The update function that is called at each frame.
     * \param deltaTime Time elapsed since the last frame.
     */
    virtual void Update(sf::Time deltaTime);
protected:
    stw::DynamicsWorld& _dynWorld;
    std::unique_ptr<stw::Rigidbody> _rb;
};
