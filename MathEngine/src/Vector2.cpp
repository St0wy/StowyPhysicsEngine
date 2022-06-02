#include "Vector2.hpp"

#include <cmath>
#include <sstream>

double Vector2::Magnitude() const
{
	return std::sqrt(SqrMagnitude());
}

double Vector2::SqrMagnitude() const
{
	return x * x + y * y;
}

Vector2 Vector2::Normalized()
{
	const double invMag = 1.0 / Magnitude();
	return { x * invMag, y * invMag };
}

std::string Vector2::ToString() const
{
	std::ostringstream ss;
	ss << "{x: " << x << ", y: " << y << "}";
	return ss.str();
}
