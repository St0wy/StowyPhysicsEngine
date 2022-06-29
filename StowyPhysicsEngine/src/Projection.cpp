#include "Projection.hpp"

#include <algorithm>

bool Projection::Overlap(const Projection& other) const
{
	return !(min > other.max || other.min > max);
}

float Projection::GetOverlap(const Projection& other) const
{
	return std::max(
		0.0f,
		std::min(max, other.max) - std::max(min, other.min)
	);
}
