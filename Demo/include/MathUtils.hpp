#pragma once

#include <SFML/System/Vector2.hpp>

#include "math/Vector2.hpp"

/**
 * \brief Converts the Stowy Physics Engine (spe) position to an SFML position.
 * Will negate the y coordinate to because the y axis is from top to bottom in SFML.
 * \param pos Position to convert.
 * \return The converted position.
 */
inline sf::Vector2f SpePosToSfml(const stw::Vector2& pos)
{
    return {pos.x, -pos.y};
}

/**
 * \brief Converts the SFML position to a Stowy Physics Engine (spe) position.
 * Will negate the y coordinate to because the y axis is from top to bottom in SFML.
 * \param pos Position to convert.
 * \return The converted position.
 */
inline stw::Vector2 SfmlPosToSpe(const sf::Vector2f& pos)
{
    return {pos.x, -pos.y};
}

/**
 * \brief Converts the Stowy Physics Engine (spe) vector to an SFML vector.
 * Will *NOT* negate the y coordinate.
 * \param v Vector to convert.
 * \return Converted vector.
 */
inline sf::Vector2f SpeVecToSfml(const stw::Vector2& v)
{
    return {v.x, v.y};
}

/**
 * \brief Converts the SFML vector to a Stowy Physics Engine (spe) vector.
 * Will *NOT* negate the y coordinate.
 * \param v Vector to convert.
 * \return Converted vector.
 */
inline stw::Vector2 SfmlVecToSpe(const sf::Vector2f& v)
{
    return {v.x, v.y};
}
