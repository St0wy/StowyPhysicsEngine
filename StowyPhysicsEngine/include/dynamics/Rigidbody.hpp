/**
 * @file Rigidbody.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Rigidbody struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include "collision/CollisionBody.hpp"

namespace stw
{
/**
* \brief A Rigidbody that has dynamics.
*/
struct Rigidbody : CollisionBody
{
	Rigidbody();

    /**
     * \brief Gets the force of the gravity on this body.
     * \return The force of the gravity.
     */
    [[nodiscard]] const Vector2& GravityForce() const;
    /**
     * \brief Sets the gravity force.
     * \param gravityForce New gravity force.
     */
    void SetGravityForce(const Vector2& gravityForce);

    /**
     * \brief Gets the force on this body.
     * \return The force on this body.
     */
    [[nodiscard]] const Vector2& Force() const;
    /**
     * \brief Adds force to this body.
     * \param addedForce The force to add to this body.
     */
    void ApplyForce(const Vector2& addedForce);
    /**
     * \brief Sets the force of this body.
     * \param force The new force.
     */
    void SetForce(const Vector2& force);

    /**
     * \brief Gets the velocity of this body.
     * \return The velocity of this body.
     */
    [[nodiscard]] const Vector2& Velocity() const;
    /**
     * \brief Sets the velocity of this body.
     * \param velocity The new velocity.
     */
    void SetVelocity(const Vector2& velocity);

    /**
     * \brief Computes the mass of this body. Only the inverted mass is stored,
     * so it's computed as 1 / InvMass();
     * \see InvMass()
     * \return The mass of this body.
     */
    [[nodiscard]] float Mass() const;
    /**
     * \brief Returns 1 / Mass of this body.
     * \return The inverted mass of this body.
     */
    [[nodiscard]] float InvMass() const;
    /**
     * \brief Sets the mass of this body.
     * \param mass The new mass.
     */
    void SetMass(float mass);

    /**
     * \brief Gets a boolean indicating whether this body takes gravity.
     * \return True if this body takes gravity.
     */
    [[nodiscard]] bool TakesGravity() const;
    /**
     * \brief Sets a boolean indicating whether this body takes gravity.
     * \param takesGravity The new takesGravity.
     */
    void SetTakesGravity(bool takesGravity);

    /**
     * \brief Gets the static friction of this body.
     * \return The static friction.
     */
    [[nodiscard]] float StaticFriction() const;
    /**
     * \brief Sets the static friction of this body.
     * \param staticFriction The new static friction.
     */
    void SetStaticFriction(float staticFriction);

    /**
     * \brief Gets the dynamic friction of this body.
     * \return The dynamic friction.
     */
    [[nodiscard]] float DynamicFriction() const;
    /**
     * \brief Sets the dynamic friction of this body.
     * \param dynamicFriction The new dynamic friction.
     */
    void SetDynamicFriction(float dynamicFriction);

    /**
     * \brief Gets the restitution of this body. Can be seen as the "Bounciness".
     * \return The restitution.
     */
    [[nodiscard]] float Restitution() const;
    /**
     * \brief Sets the restitution of this body. Can be seen as the "Bounciness".
     * \param restitution The new restitution.
     */
    void SetRestitution(float restitution);

private:
    Vector2 _gravityForce;
    Vector2 _force;
    Vector2 _velocity;

    float _invMass{};
    bool _takesGravity{};

    float _staticFriction{};
    float _dynamicFriction{};
    float _restitution{};
};
}
