/**
 * @file Transform.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Transform struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include "math/Vector2.hpp"

namespace stw
{
/**
* \brief A transform of an object.
* Contains position, scale and rotation.
*/
struct Transform
{
public:
    /**
     * \brief The position of this object.
     */
    Vector2 position{};

    /**
     * \brief The scale of this object.
     */
    Vector2 scale{1, 1};

    /**
     * \brief The rotation of this object.
     */
    float rotation{};
};
}
