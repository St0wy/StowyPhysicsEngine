#pragma once

struct Projection
{
	float min;
	float max;

	[[nodiscard]] bool Overlap(const Projection& other) const;
	[[nodiscard]] float GetOverlap(const Projection& other) const;
};