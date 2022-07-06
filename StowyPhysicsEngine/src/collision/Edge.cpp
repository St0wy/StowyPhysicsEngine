#include "collision/Edge.hpp"

float Edge::VecDot(const Vector2& v) const
{
	return EdgeVector().Dot(v);
}

Vector2 Edge::EdgeVector() const
{
	return p2 - p1;
}
