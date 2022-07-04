#pragma once

#include "math/Vector2.hpp"

#include <array>

struct Simplex
{
public:
	static constexpr unsigned long long MAX_SIZE = 3ull;

	Simplex()
		: _points({ Vector2(0, 0),{0, 0}, {0, 0} }), _size(0)
	{}

	Simplex& operator=(std::initializer_list<Vector2> list);
	Vector2 operator[] (std::size_t i) const;
	void PushFront(Vector2 point);
	[[nodiscard]] std::size_t Size() const;
	[[nodiscard]] std::array<Vector2, MAX_SIZE>::const_iterator Begin() const;
	[[nodiscard]] std::array<Vector2, MAX_SIZE>::const_iterator End() const;
	void IncrementSize();

private:
	std::array<Vector2, MAX_SIZE> _points;
	std::size_t _size;
};
