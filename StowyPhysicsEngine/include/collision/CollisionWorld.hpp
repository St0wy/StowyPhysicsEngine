/**
 * @file CollisionWorld.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the CollisionWorld class.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <vector>

#include "BroadPhaseGrid.hpp"
#include "CollisionBody.hpp"

#include "dynamics/Solver.hpp"

namespace stw
{
/**
* \brief Represents a world where collisions can happen.
* It does not have dynamics, for this you will need the DynamicsWorld.
* \see DynamicsWorld
*/
class CollisionWorld
{
public:
    CollisionWorld();
    CollisionWorld(std::unordered_map<std::uint64_t, CollisionBody*> bodies, std::vector<Solver*> solvers);

    bool useSpacePartitioning = true;

    /**
     * \brief Adds a collision body to the world.
     * \param body Body to add.
     */
    void AddCollisionBody(CollisionBody* body);

    /**
     * \brief Removes a collision body to the world.
     * \param body Body to remove.
     */
    void RemoveCollisionBody(const CollisionBody* body);

    /**
     * \brief Adds a solver to the world.
     * \param solver Solver to add.
     */
    void AddSolver(Solver* solver);

    /**
     * \brief Removes the solver from the world.
     * \param solver Solver to remove.
     */
    void RemoveSolver(Solver* solver);

    /**
     * \brief Sets the collision callback of this world.
     * \param callback Callback to set.
     */
    void SetCollisionCallback(const std::function<void(Collision&, float)>& callback);

    /**
     * \brief Solves the collisions with the provided solvers.
     * \param collisions Collisions to solve.
     * \param deltaTime Time elapsed since the last frame.
     */
    void SolveCollisions(const std::vector<Collision>& collisions, float deltaTime) const;

    /**
     * \brief Calls the callbacks of all the bodies in each collisions.
     * \param collisions Collisions to send callback from.
     * \param deltaTime Time elapsed since the last frame.
     */
    void SendCollisionCallbacks(std::vector<Collision>& collisions, float deltaTime) const;

    /**
     * \brief Resolves all the collisions that happened in this world.
     * \param deltaTime Time elapsed since the last frame.
     */
    void ResolveCollisions(float deltaTime);

    void FindCollisions(std::uint64_t firstId, std::uint64_t secondId, std::vector<Collision>& collisions, std::vector<Collision>& triggers);

protected:
    std::unordered_map<std::uint64_t, CollisionBody*> _bodies;
    std::vector<Solver*> _solvers;
    BroadPhaseGrid _grid;

    std::function<void(Collision&, float)> _onCollision;
};
}
