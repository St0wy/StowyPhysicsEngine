/**
 * @file Vector2.hpp
 * @author Fabian Huber (fabian.hbr@protonmail.ch)
 * @brief Contains the Vector2 struct.
 * @version 1.0
 * @date 05.07.2022
 *
 * @copyright SAE (c) 2022
 *
 */
#pragma once

#include <string>

namespace stw
{
/**
  * \brief A struct representing a 2D Vector.
  */
struct Vector2
{
	constexpr Vector2()
		: Vector2(0, 0)
	{}

	constexpr Vector2(const float x, const float y)
		: x(x), y(y)
	{}

	/**
	 * \brief The X component of the 2D Vector.
	 */
	float x;
	/**
	 * \brief The Y component of the 2D Vector.
	 */
	float y;

	/**
	 * \brief Normalizes the given vector.
	 * \param v The vector to normalize.
	 * \return The normalized vector.
	 */
	static Vector2 Normalize(const Vector2& v);
	/**
	 * \brief Linearly interpolates between A and B.
	 * \param a Start vector.
	 * \param b End vector.
	 * \param t Value indicating the progression between a and b. Should be between 0 and 1.
	 * \return The linear interpolation between a and b.
	 */
	static Vector2 Lerp(const Vector2& a, const Vector2& b, float t);
	/**
	 * \brief Compute the triple product with all of these vectors as 3d vectors with z = 0.
	 * p = a x (b x c)
	 * \param a Vector a.
	 * \param b Vector b.
	 * \param c Vector c.
	 * \return The triple product with a, b and c.
	 */
	static Vector2 TripleProduct(const Vector2& a, const Vector2& b, const Vector2& c);

	/**
	 * \brief Gets the magnitude of this vector.
	 * \return The magnitude of this vector.
	 */
	[[nodiscard]] float Magnitude() const;

	/**
	 * \brief Gets the squared magnitude of this vector.
	 * It is faster that Magnitude, so it should be used for size comparison.
	 * \return The squared magnitude of this vector.
	 */
	[[nodiscard]] float SqrMagnitude() const;

	/**
	 * \brief Gets this vector normalized.
	 * \return This vector normalized.
	 */
	[[nodiscard]] Vector2 Normalized() const;

	/**
	 * \brief Computes the dot product between this and other.
	 * \param other The other vector.
	 * \return The dot product between this and other.
	 */
	[[nodiscard]] float Dot(const Vector2& other) const;

	/**
	 * \brief Computes the distance between this and other.
	 * \param other The other vector.
	 * \return The distance between this and other.
	 */
	[[nodiscard]] float Distance(const Vector2& other) const;

	/**
	 * \brief Computes the angle between this and other.
	 * \param other The other vector.
	 * \return The angle between this and other.
	 */
	[[nodiscard]] float Angle(const Vector2& other) const;

	/**
	 * \brief Gets the biggest component of this vector.
	 * \return The biggest component of this vector.
	 */
	[[nodiscard]] float Major() const;

	/**
	 * \brief Computes the perpendicular vector in +90 degrees.
	 * \return The perpendicular vector in the positive direction.
	 */
	[[nodiscard]] Vector2 PositivePerpendicular() const;

	/**
	 * \brief Computes the perpendicular vector in -90 degrees.
	 * \return The perpendicular vector in the negative direction.
	 */
	[[nodiscard]] Vector2 NegativePerpendicular() const;

	/**
	 * \brief Sets the magnitude of this vector.
	 * \param newMagnitude The new magnitude.
	 */
	[[nodiscard]] Vector2 NewMagnitude(float newMagnitude) const;

	/**
	 * \brief Rotates this vector around the provided axis.
	 * \param center The axis to rotate around.
	 * \param angle The angle by which this vector should be rotated.
	 */
	void RotateAround(const Vector2& center, float angle);

	/**
	 * \brief Gets a string representing this vector.
	 * \return A string representing this vector.
	 */
	[[nodiscard]] std::string ToString() const;

	constexpr static Vector2 Zero();

	Vector2 operator+(const Vector2& other) const;
	Vector2 operator-(const Vector2& other) const;
	Vector2 operator+=(const Vector2& other);
	Vector2 operator-=(const Vector2& other);
	Vector2 operator+=(float scalar);
	Vector2 operator-=(float scalar);
	Vector2 operator*=(float scalar);
	Vector2 operator/=(float scalar);
	bool operator==(const Vector2& other) const;
	Vector2 operator-() const;

	friend Vector2 operator+(Vector2 vec, float scalar);
	friend Vector2 operator-(Vector2 vec, float scalar);
	friend Vector2 operator*(Vector2 vec, float scalar);
	friend Vector2 operator*(float scalar, Vector2 vec);
	friend Vector2 operator/(Vector2 vec, float scalar);
};

constexpr Vector2 Vector2::Zero()
{
	return { 0.0f, 0.0f };
}

std::ostream& operator<<(std::ostream& os, const Vector2& vec);
}
