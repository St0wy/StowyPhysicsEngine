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

Vector2 Vector2::operator+(const Vector2& other) const
{
	return { this->x + other.x, this->y + other.y };
}

Vector2 Vector2::operator-(const Vector2& other) const
{
	return { this->x - other.x, this->y - other.y };
}

Vector2 Vector2::operator*(const Vector2& other) const
{
	return { this->x * other.x, this->y * other.y };
}

Vector2 Vector2::operator/(const Vector2& other) const
{
	return { this->x / other.x, this->y / other.y };
}

Vector2 Vector2::operator+=(const Vector2& other)
{
	this->x += other.x;
	this->y += other.y;
	return *this;
}

Vector2 Vector2::operator-=(const Vector2& other)
{
	this->x -= other.x;
	this->y -= other.y;
	return *this;
}

Vector2 Vector2::operator*=(const Vector2& other)
{
	this->x *= other.x;
	this->y *= other.y;
	return *this;
}

Vector2 Vector2::operator/=(const Vector2& other)
{
	this->x /= other.x;
	this->y /= other.y;
	return *this;
}

Vector2 Vector2::operator+=(const double scalar)
{
	this->x += scalar;
	this->y += scalar;
	return *this;
}

Vector2 Vector2::operator-=(const double scalar)
{
	this->x -= scalar;
	this->y -= scalar;
	return *this;
}

Vector2 Vector2::operator*=(const double scalar)
{
	this->x *= scalar;
	this->y *= scalar;
	return *this;
}

Vector2 Vector2::operator/=(const double scalar)
{
	this->x /= scalar;
	this->y /= scalar;
	return *this;
}


Vector2 operator+(Vector2 vec, const double scalar)
{
	return vec += scalar;
}

Vector2 operator-(Vector2 vec, const double scalar)
{
	return vec -= scalar;
}

Vector2 operator*(Vector2 vec, const double scalar)
{
	return vec *= scalar;
}

Vector2 operator/(Vector2 vec, const double scalar)
{
	return vec /= scalar;
}
