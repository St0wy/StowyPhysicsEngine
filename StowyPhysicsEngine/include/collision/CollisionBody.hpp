/**
 * @file CollisionBody.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the CollisionBody struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <functional>

#include "Collider.hpp"
#include "Transform.hpp"

namespace stw
{
struct Collision;

/**
 * \brief A body that can receive collisions.
 */
class CollisionBody
{
public:
    CollisionBody();

    std::uint64_t id;

    /**
     * \brief Gets the transform of the body.
     * \return The transform of the body.
     */
    Transform* Trans();

    /**
     * \brief Sets the transform of the body.
     * \param transform Transform to set to the body.
     */
    void SetTransform(const Transform& transform);

    //Transform* LastTransform();
    //void UpdateLastTransform();

    /**
     * \brief Gets the collider of the body.
     * \return The collider of the body.
     */
    [[nodiscard]] Collider* Col() const;

    /**
     * \brief Sets the collider of the body.
     * \param collider The collider to set on the body.
     */
    void SetCollider(Collider* collider);

    /**
     * \brief A boolean saying if the collider is a trigger collider.
     * This means that it will not have a collision response and will only have a callback.
     * \return If the collider is a trigger collider.
     */
    [[nodiscard]] bool IsTrigger() const;

    /**
     * \brief Sets is trigger on the body.
     * True means that it will not have a collision response and will only have a callback.
     * \param isTrigger The boolean saying if the collider is trigger.
     */
    void SetIsTrigger(bool isTrigger);

    /**
     * \brief Sets the collision callback function.
     * \param callback The callback function.
     */
    void SetCollisionCallback(const std::function<void(const Collision&, float)>& callback);

    /**
     * \brief Triggers the collision callback function.
     * \param collision Object representing the collision.
     * \param deltaTime The time elapsed since the last frame.
     */
    void OnCollision(const Collision& collision, float deltaTime) const;

    /**
     * \brief Gets the position of the body in the world.
     * \return The position of the body in the world.
     */
    [[nodiscard]] const Vector2& Position() const;

    /**
     * \brief Sets the position of the body in the world.
     * \param position The new position of the body.
     */
    void SetPosition(const Vector2& position);

    /**
     * \brief Gets a boolean that indicates if this body will receive a collision response.
     * \return A boolean that indicates if this body is kinematic.
     */
    [[nodiscard]] bool IsKinematic() const;

    /**
     * \brief Sets a boolean that indicates if this body will receive a collision response.
     * \param isKinematic The new isKinematic status.
     */
    void SetIsKinematic(bool isKinematic);

    /**
     * \brief Gets a boolean indicating if this body is dynamic. This means that this is a Rigidbody.
     * \see Rigidbody
     * \return A boolean indicating if this body is dynamic.
     */
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
}
