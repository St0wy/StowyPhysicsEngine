#pragma once

#include "math/Vector2.hpp"

namespace stw
{
struct Edge
{
    Vector2 max;
    Vector2 p1;
    Vector2 p2;

    [[nodiscard]] float VecDot(const Vector2& v) const;
    [[nodiscard]] Vector2 EdgeVector() const;
};
}
