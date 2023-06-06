#include "collision/Simplex.hpp"

#include <algorithm>

namespace stw
{
Simplex &Simplex::operator=(std::initializer_list<Vector2> list)
{
    for (auto v = list.begin(); v != list.end(); v++)
    {
        _points[std::distance(list.begin(), v)] = *v;
    }

    _size = list.size();
    return *this;
}

Vector2 Simplex::operator[](const std::size_t i) const
{
    return _points[i];
}

void Simplex::PushFront(const Vector2 point)
{
    _points = {point, _points[0], _points[1]};
    IncrementSize();
}

std::size_t Simplex::Size() const
{
    return _size;
}

void Simplex::IncrementSize()
{
    _size = std::min(_size + 1ull, MAX_SIZE);
}

std::array<Vector2, Simplex::MAX_SIZE>::const_iterator Simplex::End() const
{
    return _points.end();
}

std::array<Vector2, Simplex::MAX_SIZE>::const_iterator Simplex::Begin() const
{
    return _points.begin();
}
} // namespace stw
