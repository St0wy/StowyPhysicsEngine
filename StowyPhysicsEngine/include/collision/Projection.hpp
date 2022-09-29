/**
 * @file Projection.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Projection struct.
 * @version 1.0
 * @date 29.09.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

namespace stw
{
struct Projection
{
    float min;
    float max;

    [[nodiscard]] bool Overlaps(const Projection& other) const;
    [[nodiscard]] float GetOverlap(const Projection& other) const;
};
}
