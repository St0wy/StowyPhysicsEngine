/**
 * @file ImpulseSolver.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the ImpulseSolver class.
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
* \brief Solver with impulse and friction.
*/
class ImpulseSolver final : public Solver
{
public:
	void Solve(const std::vector<Collision>& collisions, float deltaTime) override;
};
}