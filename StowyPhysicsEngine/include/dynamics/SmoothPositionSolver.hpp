/**
 * @file SmoothPositionSolver.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the SmoothPositionSolver class.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once
#include "Solver.hpp"

namespace stw
{
/**
* \brief A solver to smooth out collision with collider that are in a tower placement.
*/
class SmoothPositionSolver : public Solver
{
public:
    void Solve(const std::vector<Collision>& collisions, float deltaTime) override;
};
}
