#pragma once

#include <array>
#include <SFML/System.hpp>

struct Simplex
{
public:
	static constexpr unsigned long long MAX_SIZE = 3ull;

	Simplex()
		: _points({ sf::Vector2f(0, 0),{0, 0}, {0, 0} }), _size(0)
	{}

	Simplex& operator=(std::initializer_list<sf::Vector2f> list);
	sf::Vector2f operator[] (std::size_t i) const;
	void PushFront(sf::Vector2f point);
	[[nodiscard]] std::size_t Size() const;
	[[nodiscard]] std::array<sf::Vector2f, MAX_SIZE>::const_iterator Begin() const;
	[[nodiscard]] std::array<sf::Vector2f, MAX_SIZE>::const_iterator End() const;
	void IncrementSize();

private:
	std::array<sf::Vector2f, MAX_SIZE> _points;
	std::size_t _size;
};
