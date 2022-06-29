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
	sf::Vector2f operator[] (unsigned i) const;
	void PushFront(sf::Vector2f point);
	[[nodiscard]] std::size_t Size() const;
	[[nodiscard]] auto Begin() const;
	[[nodiscard]] auto End() const;

private:
	std::array<sf::Vector2f, 3> _points;
	std::size_t _size;
};
