#pragma once

#include <cmath>
#include <algorithm>

#include "SFML/System/Vector2.hpp"

template<typename T>
sf::Vector2<T> Normalized(const sf::Vector2<T>& vec)
{
	if (vec.x == 0 && vec.y == 0)  // NOLINT(clang-diagnostic-float-equal)
		return {};

	T length = Magnitude<T>(vec);

	if (length != 0.0f)
	{
		return vec / length;
	}

	return { 0, 0 };
}

template<typename T>
T SquaredMagnitude(const sf::Vector2<T>& vec)
{
	return vec.x * vec.x + vec.y * vec.y;
}

/**
 * \brief Gets the magnitude of the vector.
 * \tparam T Number type of the vector.
 * \param vec The vector to get the magnitude from.
 * \return The length of the vector.
 */
template<typename T>
T Magnitude(const sf::Vector2<T>& vec)
{
	return std::sqrt(SquaredMagnitude(vec));
}

template<typename T>
T Major(const sf::Vector2<T>& vec)
{
	if (vec.x > vec.y)
	{
		return vec.x;
	}
	return vec.y;
}

template<typename T>
sf::Vector2<T> Lerp(const sf::Vector2<T>& a, const sf::Vector2<T>& b, float t)
{
	t = std::clamp(t, 0.0f, 1.0f);
	return {
		a.x + (b.x - a.x) * t,
		a.y + (b.y - a.y) * t,
	};
}

template<typename T>
T Dot(const sf::Vector2<T>& a, const sf::Vector2<T>& b)
{
	return a.x * b.x + a.y * b.y;
}

template<typename T>
sf::Vector2<T> Rotate(const sf::Vector2<T>& v, const T angle)
{
	const T ca = std::cos(angle);
	const T sa = std::sin(angle);
	return sf::Vector2<T>(ca * v.x - sa * v.y, sa * v.x + ca * v.y);
}

template<typename T>
sf::Vector2<T> RotateAround(const sf::Vector2<T>& v, const sf::Vector2<T>& center, const T angle)
{
	const sf::Vector2<T> relative = v - center;
	const T ca = std::cos(angle);
	const T sa = std::sin(angle);
	const auto rotated = sf::Vector2<T>(ca * relative.x - sa * relative.y, sa * relative.x + ca * relative.y);
	return rotated + center;
}

/**
 * Rotates the vector by +90 degrees
 */
template<typename T>
sf::Vector2<T> Normal(const sf::Vector2<T>& v)
{
	return { -v.y, v.x };
}

/**
 * Rotates the vector by -90 degrees
 */
template<typename T>
sf::Vector2<T> OppositeNormal(const sf::Vector2<T>& v)
{
	return { v.y, -v.x };
}

template<typename T>
sf::Vector2<T> SetMagnitude(const sf::Vector2<T>& v, T newMagnitude)
{
	T magnitude = Magnitude(v);
	return v / magnitude * newMagnitude;
}

/**
 * \brief Computes the triple product such as p = a x (b x c)
 * \tparam T number type supported by SFML.
 * \param a first vector
 * \param b second vector
 * \param c third vector
 * \return The triple product of these vectors.
 */
template<typename T>
sf::Vector2<T> TripleProduct(const sf::Vector2<T>& a, const sf::Vector2<T>& b, const sf::Vector2<T>& c)
{
	return {
		a.y * (b.x * c.y - b.y * c.x),
		a.x * (b.y * c.x - b.x * c.y)
	};
}
