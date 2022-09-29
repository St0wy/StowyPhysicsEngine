/**
 * @file DynamicsWorld.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the DynamicsWorld class.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include "Rigidbody.hpp"

#include "collision/CollisionWorld.hpp"

namespace stw
{
/**
* \brief A world with dynamics in it.
*/
class DynamicsWorld : public CollisionWorld
{
public:
    /**
     * \brief Adds a rigidbody in the world.
     * \param rigidbody Rigidbody to add.
     */
    void AddRigidbody(Rigidbody* rigidbody);

    /**
     * \brief Applies the gravity to all the rigidbody.
     */
    void ApplyGravity() const;

    /**
     * \brief Moves all the rigidbodies.
     * \param deltaTime Time elapsed since the last frame.
     */
    void MoveBodies(float deltaTime) const;

    /**
     * \brief Steps the world.
     * \param deltaTime Time elapsed since the last frame.
     */
    void Step(float deltaTime);

    /**
     * \brief Sets the gravity in the world.
     * \param gravity Gravity to set.
     */
    void SetWorldGravity(Vector2 gravity);

private:
    Vector2 _gravity = {0, -9.81f};
};
}
