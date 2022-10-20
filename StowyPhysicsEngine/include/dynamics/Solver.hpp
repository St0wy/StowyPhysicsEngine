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
}
