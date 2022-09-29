/**
 * @file BroadPhaseGrid.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the BroadPhaseGrid class.
 * @version 1.0
 * @date 07.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <vector>

#include "CollisionBody.hpp"

namespace stw
{
/**
* \brief A grid in which the physical object are placed in.
* This is used to optimize performance by only checking collision with colliders
* that are in the same cell.
*
* A collider that spans on multiple cells will have a pointer on every cell.
*/
class BroadPhaseGrid
{
public:
    /**
     * \brief Constructs a new grid.
     * \param minX X coordinate on the bottom left point of the grid.
     * \param maxX X coordinate on the top right point of the grid.
     * \param minY Y coordinate on the bottom left point of the grid.
     * \param maxY Y coordinate on the top right point of the grid.
     * \param cellSize Size (in meter) of a cell.
     */
    BroadPhaseGrid(float minX, float maxX, float minY, float maxY, float cellSize);

    /**
     * \brief Updates the layout of the grid.
     * \param bodies Bodies in the physical world.
     */
    void Update(const std::unordered_map<std::uint64_t, CollisionBody*>& bodies);

    /**
     * \brief Find all the pair of objects that are in the same cell.
     * Doesn't contain any duplicates.
     * \return The pair of objects that will collide.
     */
    [[nodiscard]] std::vector<std::pair<std::uint64_t, std::uint64_t>> GetCollisionPairs() const;

private:
    std::vector<std::vector<std::vector<CollisionBody*>>> _grid;
    Vector2 _min;
    Vector2 _max;
    float _cellSize;
    std::size_t _gridWidth;
    std::size_t _gridHeight;

    static bool HasBeenChecked(
        const std::unordered_multimap<CollisionBody*, CollisionBody*>& checkedCollisions,
        const std::pair<CollisionBody*, CollisionBody*>& bodyPair);
};
}
