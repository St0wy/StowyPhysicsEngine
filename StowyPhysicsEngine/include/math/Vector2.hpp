#pragma once
#include <string>
#include "spdlog/fmt/ostr.h"

struct Vector2
{
public:
	Vector2() : Vector2(0, 0) {  }

	Vector2(const float x, const float y) : x(x), y(y) {  }

	float x;
	float y;

	static Vector2 Normalize(const Vector2& v);
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	static Vector2 TripleProduct(const Vector2& a, const Vector2& b, const Vector2& c);

	[[nodiscard]] float Magnitude() const;
	[[nodiscard]] float SqrMagnitude() const;
	[[nodiscard]] Vector2 Normalized() const;
	[[nodiscard]] float Dot(const Vector2& other) const;
	[[nodiscard]] float Distance(const Vector2& other) const;
	[[nodiscard]] float Angle(const Vector2& other) const;
	[[nodiscard]] float Major() const;
	[[nodiscard]] Vector2 PositivePerpendicular() const;
	[[nodiscard]] Vector2 NegativePerpendicular() const;
	void SetMagnitude(float newMagnitude);
	void RotateAround(const Vector2& center, float angle);

	[[nodiscard]] std::string ToString() const;

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator+=(float scalar);
	Vector2 operator-=(float scalar);
	Vector2 operator*=(float scalar);
	Vector2 operator/=(float scalar);
	Vector2 operator-() const;

	friend Vector2 operator+(Vector2 vec, float scalar);
	friend Vector2 operator-(Vector2 vec, float scalar);
	friend Vector2 operator*(Vector2 vec, float scalar);
	friend Vector2 operator*(float scalar, Vector2 vec);
	friend Vector2 operator/(Vector2 vec, float scalar);
};

std::ostream& operator<<(std::ostream& os, const Vector2& vec);
