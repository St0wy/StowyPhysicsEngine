#pragma once

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
