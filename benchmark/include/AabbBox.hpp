#pragma once


#include "Entity.hpp"

#include "collision/Collider.hpp"


class AabbBox final : public Entity
{
public:
    AabbBox(stw::DynamicsWorld& dynWorld, stw::Vector2 size, stw::Vector2 pos, bool takesGravity);

private:
    std::unique_ptr<stw::AabbCollider> _collider;
};
