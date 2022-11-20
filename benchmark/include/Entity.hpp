#pragma once

#include <memory>

#include "dynamics/DynamicsWorld.hpp"
#include "dynamics/Rigidbody.hpp"

#include "math/Vector2.hpp"

class Entity
{
public:
    explicit Entity(stw::DynamicsWorld& dynWorld);
    Entity(stw::DynamicsWorld& dynWorld, stw::Vector2 pos);
    ~Entity();

    [[nodiscard]] stw::Rigidbody* RigidBody() const;

    void Push(stw::Vector2 force) const;

protected:
    stw::DynamicsWorld& _dynWorld;
    std::unique_ptr<stw::Rigidbody> _rb;
};
