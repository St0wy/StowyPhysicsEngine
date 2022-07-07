#pragma once

#include "CollisionBody.hpp"

#include <vector>

class BroadPhaseGrid
{
public:
	BroadPhaseGrid(float minX, float maxX, float minY, float maxY, float cellSize);
	void Update(const std::vector<CollisionBody*>& bodies);
	std::vector<std::pair<std::uint64_t, std::uint64_t>> GetCollisionPairs() const;

private:
	std::vector<std::vector<std::vector<CollisionBody*>>> _grid;
	Vector2 _min;
	Vector2 _max;
	float _cellSize;

	static bool HasBeenChecked(
		const std::unordered_multimap<CollisionBody*, CollisionBody*>& checkedCollisions,
		const std::pair<CollisionBody*, CollisionBody*>& bodyPair);
};