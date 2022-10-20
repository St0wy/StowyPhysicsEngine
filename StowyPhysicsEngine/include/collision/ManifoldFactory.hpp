/**
 * @file ManifoldFactory.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the algo namespace which contains the
 * functions to detect a collision.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include "Collider.hpp"
#include "Manifold.hpp"
#include "Simplex.hpp"
#include "Transform.hpp"

namespace stw
{
class CollisionBody;

/**
 * \brief Namespace containing all the methods to get manifolds from collisions.
 * This is here to separate the logic from the Collider class.
 * Avoids the problem where we don't know if the circle-box collision resolution should be
 * in the CircleCollider class or the box ColliderClass.
 */
namespace algo
{
/**
 * \brief Finds the collision manifold between A and B.
 * \param a Circle collider of the object A.
 * \param ta Transform of the object A.
 * \param b Circle collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindCircleCircleManifold(
	const CircleCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a Circle collider of the object A.
 * \param ta Transform of the object A.
 * \param b Box collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindCircleBoxManifold(
	const CircleCollider* a, const Transform* ta,
	const BoxCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a Box collider of the object A.
 * \param ta Transform of the object A.
 * \param b Circle collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindBoxCircleManifold(
	const BoxCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a Box collider of the object A.
 * \param ta Transform of the object A.
 * \param b Box collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindBoxBoxManifold(
	const BoxCollider* a, const Transform* ta,
	const BoxCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a AABB collider of the object A.
 * \param ta Transform of the object A.
 * \param b AABB collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindAabbAabbManifold(
	const AabbCollider* a, const Transform* ta,
	const AabbCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a AABB collider of the object A.
 * \param ta Transform of the object A.
 * \param b Circle collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindAabbCircleManifold(
	const AabbCollider* a, const Transform* ta,
	const CircleCollider* b, const Transform* tb);

/**
 * \brief Finds the collision manifold between A and B.
 * \param a Circle collider of the object A.
 * \param ta Transform of the object A.
 * \param b AABB collider of the object B.
 * \param tb Transform of the object B.
 * \return The manifold of the collisions between A and B.
 */
Manifold FindCircleAabbManifold(
	const CircleCollider* a, const Transform* ta,
	const AabbCollider* b, const Transform* tb);

/**
 * \brief Support function of the GJK algorithm.
 * \param colliderA Collider of object A.
 * \param transformA Transform of object A.
 * \param colliderB Collider of object B.
 * \param transformB Transform of object B.
 * \param direction Direction in which to find the vector.
 * \return The vertex found by the support function.
 */
Vector2 Support(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB,
	const Vector2& direction
);

/**
 * \brief Finds the manifold between A and B using GJK.
 * \param colliderA Collider of object A.
 * \param transformA Transform of object A.
 * \param colliderB Collider of object B.
 * \param transformB Transform of object B.
 * \return Returns the manifold of the objects using the GJK algorithm.
 */
Manifold Gjk(
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
);

/**
 * \brief Finds the next simplex for the GJK algorithm.
 * \param points Current simplex.
 * \param direction Direction in which to find the next simplex.
 * \return True if we found the origin.
 */
bool NextSimplex(const Simplex& points, Vector2& direction);
/**
 * \brief Finds if both vectors are going in the same direction.
 * \param direction Direction vector.
 * \param ao Vector between a and the origin.
 * \return True if both of the vectors are going in the same direction.
 */
bool SameDirection(Vector2 direction, Vector2 ao);

/**
 * \brief Line case for the NextSimplex function.
 * \param points Points of the line simplex.
 * \param direction Direction of the next point.
 * \return True if we found the origin.
 */
bool Line(const Simplex& points, Vector2& direction);
/**
 * \brief Triangle case for the NextSimplex function.
 * \param points Points of the Triangle simplex.
 * \param direction Direction of the next point.
 * \return True if we found the origin.
 */
bool Triangle(const Simplex& points, Vector2& direction);

/**
 * \brief Find the manifold from the last simplex of the GJK algorithm.
 * \param simplex Last simplex of the GJK.
 * \param colliderA Collider of object A.
 * \param transformA Transform of object A.
 * \param colliderB Collider of object B.
 * \param transformB Transform of object B.
 * \return The manifold found.
 */
Manifold Epa(
	const Simplex& simplex,
	const Collider* colliderA,
	const Transform* transformA,
	const Collider* colliderB,
	const Transform* transformB
);

Manifold Sat(
	const BoxCollider* colliderA,
	const Transform* transformA,
	const BoxCollider* colliderB,
	const Transform* transformB
);
}
}
