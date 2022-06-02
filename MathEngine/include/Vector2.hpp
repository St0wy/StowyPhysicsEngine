#pragma once
#include <string>

struct Vector2
{
public:
	Vector2() : Vector2(0, 0) {  }

	Vector2(const double x, const double y) : x(x), y(y) {  }

	double x;
	double y;

	[[nodiscard]] double Magnitude() const;
	[[nodiscard]] double SqrMagnitude() const;
	Vector2 Normalized();
	[[nodiscard]] std::string ToString() const;
};
