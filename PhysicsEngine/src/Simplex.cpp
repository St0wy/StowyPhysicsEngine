#include "Simplex.hpp"

Simplex& Simplex::operator=(std::initializer_list<sf::Vector2f> list)
{
	for (auto v = list.begin(); v != list.end(); v++)
	{
		_points[std::distance(list.begin(), v)] = *v;
	}

	_size = list.size();
	return *this;
}

sf::Vector2f Simplex::operator[](const unsigned i) const
{
	return _points[i];
}

void Simplex::PushFront(const sf::Vector2f point)
{
	_points = { point, _points[0], _points[1] };
	_size = std::min(_size + 1, MAX_SIZE);
}

std::size_t Simplex::Size() const
{
	return _size;
}

auto Simplex::End() const
{
	return _points.end();
}

auto Simplex::Begin() const
{
	return _points.begin();
}
