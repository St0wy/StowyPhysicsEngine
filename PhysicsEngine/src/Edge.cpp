#include "Edge.hpp"

#include "VecUtils.hpp"

float Edge::VecDot(const sf::Vector2f& v) const
{
	return Dot(EdgeVector(), v);
}

sf::Vector2f Edge::EdgeVector() const
{
	return p2 - p1;
}

