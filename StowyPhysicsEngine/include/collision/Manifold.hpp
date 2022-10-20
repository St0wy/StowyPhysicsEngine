/**
 * @file Manifold.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Manifold class.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <format>

#include "math/Vector2.hpp"

namespace stw
{
struct Manifold
{
	Manifold(const Vector2& a, const Vector2& b, const Vector2& normal, float depth);
    Manifold(const Vector2& normal, float depth);
    Manifold();

    /**
     * \brief Point a of the manifold.
     */
    Vector2 a;

    /**
     * \brief Point b of the manifold.
     */
    Vector2 b;

    /**
     * \brief The normal of the manifold.
     * Represents the direction in which the collision should be solved.
     */
    Vector2 normal;

    /**
     * \brief The depth of the collision. Can be seen as the magnitude of the normal.
     */
    float depth{};

    /**
     * \brief Boolean indicating whether a collision happened.
     */
    bool hasCollision{};

    /**
     * \brief Gets an empty manifold with no collisions.
     * \return An empty manifold.
     */
    static Manifold Empty()
    {
        return {};
    }

    [[nodiscard]] Manifold Swaped() const;
};

std::ostream& operator<<(std::ostream& os, const Manifold& manifold);
}
