/**
 * @file Collision.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Collision struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include "CollisionBody.hpp"

 /**
  * \brief Struct representing a collision.
  */
struct Collision
{
	/**
	 * \brief Body A of the collision.
	 */
	CollisionBody* bodyA{};

	/**
	 * \brief Body B of the collision.
	 */
	CollisionBody* bodyB{};

	/**
	 * \brief Manifold of the collision.
	 */
	Manifold manifold;

	//Collision() = default;

	//Collision(CollisionBody* a, CollisionBody* b, const Manifold& manif);
};
