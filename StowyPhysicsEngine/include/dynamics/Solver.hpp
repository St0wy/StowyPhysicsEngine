/**
 * @file Solver.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Solver struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <vector>

#include "collision/Collision.hpp"

namespace stw
{

/**
* \brief Generic class for all solvers.
*/
class Solver
{
public:
    Solver() = default;
    virtual ~Solver() = default;
	Solver(const Solver& other) = default;
	Solver(Solver&& other) = default;
	Solver& operator=(const Solver& other) = delete;
	Solver& operator=(Solver&& other) = delete;

    /**
     * \brief Solves the provided collisions.
     * \param collisions Collisions to solve.
     * \param deltaTime Time elapsed since the last frame.
     */
    virtual void Solve(const std::vector<Collision>& collisions, float deltaTime) = 0;
};

/**
* \brief Solver with impulse and friction.
*/
class ImpulseSolver final : public Solver
{
public:
	void Solve(const std::vector<Collision>& collisions, float deltaTime) override;
};

/**
* \brief A solver to smooth out collision with collider that are in a tower placement.
*/
class SmoothPositionSolver final : public Solver
{
public:
    void Solve(const std::vector<Collision>& collisions, float deltaTime) override;
};
}
