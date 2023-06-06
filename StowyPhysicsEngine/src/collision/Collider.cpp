// ReSharper disable CppClangTidyReadabilitySuspiciousCallArgument
#include "collision/Collider.hpp"

#include <array>

#include "collision/Manifold.hpp"
#include "collision/ManifoldFactory.hpp"

#include "math/Vector2.hpp"

namespace stw
{
#pragma region BoxCollider
Manifold BoxCollider::TestCollision(const Transform *transform, const Collider *collider,
                                    const Transform *colliderTransform) const
{
    return collider->TestCollision(colliderTransform, this, transform);
}

Manifold BoxCollider::TestCollision(const Transform *transform, const BoxCollider *collider,
                                    const Transform *boxTransform) const
{
    return algo::FindBoxBoxManifold(this, transform, collider, boxTransform);
}

Manifold BoxCollider::TestCollision(const Transform *transform, const CircleCollider *collider,
                                    const Transform *circleTransform) const
{
    return algo::FindBoxCircleManifold(this, transform, collider, circleTransform);
}

Manifold BoxCollider::TestCollision(const Transform *transform, const AabbCollider *collider,
                                    const Transform *circleTransform) const
{
    // TODO : Implement
    return Manifold::Empty();
}

Vector2 BoxCollider::FindFurthestPoint(const Transform *transform, const Vector2 &direction) const
{
    Vector2 maxPoint;
    float maxDistance = -std::numeric_limits<float>::max();

    for (const Vector2 &vertex : GetTransformedVertices(*transform))
    {
        const float distance = vertex.Dot(direction);
        if (distance > maxDistance)
        {
            maxDistance = distance;
            maxPoint = vertex;
        }
    }

    return maxPoint;
}

std::array<Vector2, 4> BoxCollider::GetVertices() const
{
    return GetTransformedVertices({{0, 0}, {1, 1}, 0});
}

Projection BoxCollider::Project(const Vector2 &axis, const std::array<Vector2, 4> &vertices)
{
    float min = axis.Dot(vertices[0]);
    float max = min;

    for (const auto &vertex : vertices)
    {
        const float p = axis.Dot(vertex);
        if (p < min)
        {
            min = p;
        }
        else if (p > max)
        {
            max = p;
        }
    }

    return {min, max};
}

std::array<Vector2, 4> BoxCollider::GetAxes(const std::array<Vector2, 4> &vertices)
{
    std::array<Vector2, 4> axes;

    for (std::size_t i = 0; i < 4; ++i)
    {
        Vector2 p1 = vertices[i];
        Vector2 p2 = vertices[(i + 1) % vertices.size()];
        Vector2 edge = p1 - p2;
        Vector2 normal = edge.PositivePerpendicular();
        axes[i] = normal.Normalized();
    }

    return axes;
}

Vector2 BoxCollider::GetBoundingBoxSize() const
{
    return {halfWidth * 2.0f, halfHeight * 2.0f};
}

std::array<Vector2, 4> BoxCollider::GetTransformedVertices(const Transform &transform) const
{
    const float scaledHalfWidth = halfWidth * transform.scale.x;
    const float scaledHalfHeight = halfHeight * transform.scale.y;
    const Vector2 newCenter = center + transform.position;

    Vector2 topLeft = {newCenter.x - scaledHalfWidth, newCenter.y + scaledHalfHeight};
    Vector2 topRight = {newCenter.x + scaledHalfWidth, newCenter.y + scaledHalfHeight};
    Vector2 bottomRight = {newCenter.x + scaledHalfWidth, newCenter.y - scaledHalfHeight};
    Vector2 bottomLeft = {newCenter.x - scaledHalfWidth, newCenter.y - scaledHalfHeight};

    topLeft.RotateAround(newCenter, transform.rotation);
    topRight.RotateAround(newCenter, transform.rotation);
    bottomRight.RotateAround(newCenter, transform.rotation);
    bottomLeft.RotateAround(newCenter, transform.rotation);

    return {
        topLeft,
        topRight,
        bottomRight,
        bottomLeft,
    };
}
#pragma endregion

#pragma region CircleCollider

CircleCollider::CircleCollider(float radius) : radius(radius)
{
}

Manifold CircleCollider::TestCollision(const Transform *transform, const Collider *collider,
                                       const Transform *colliderTransform) const
{
    return collider->TestCollision(colliderTransform, this, transform);
}

Manifold CircleCollider::TestCollision(const Transform *transform, const BoxCollider *collider,
                                       const Transform *boxTransform) const
{
    return algo::FindCircleBoxManifold(this, transform, collider, boxTransform);
}

Manifold CircleCollider::TestCollision(const Transform *transform, const CircleCollider *collider,
                                       const Transform *circleTransform) const
{
    return algo::FindCircleCircleManifold(this, transform, collider, circleTransform);
}

Manifold CircleCollider::TestCollision(const Transform *transform, const AabbCollider *collider,
                                       const Transform *aabbTransform) const
{
    return algo::FindCircleAabbManifold(this, transform, collider, aabbTransform);
}

Vector2 CircleCollider::FindFurthestPoint(const Transform *transform, const Vector2 &direction) const
{
    return center + transform->position + radius * direction.Normalized() * transform->scale.Major();
}

Vector2 CircleCollider::GetBoundingBoxSize() const
{
    return {radius * 2, radius * 2};
}
#pragma endregion

#pragma region AabbCollider
Manifold AabbCollider::TestCollision(const Transform *transform, const Collider *collider,
                                     const Transform *colliderTransform) const
{
    return collider->TestCollision(colliderTransform, this, transform);
}

Manifold AabbCollider::TestCollision(const Transform *transform, const BoxCollider *collider,
                                     const Transform *boxTransform) const
{
    // TODO : Implement
    return Manifold::Empty();
}

Manifold AabbCollider::TestCollision(const Transform *transform, const CircleCollider *collider,
                                     const Transform *circleTransform) const
{
    return algo::FindAabbCircleManifold(this, transform, collider, circleTransform);
}

Manifold AabbCollider::TestCollision(const Transform *transform, const AabbCollider *collider,
                                     const Transform *aabbTransform) const
{
    return algo::FindAabbAabbManifold(this, transform, collider, aabbTransform);
}

Vector2 AabbCollider::FindFurthestPoint(const Transform *transform, const Vector2 &direction) const
{
    return {};
}

Vector2 AabbCollider::GetBoundingBoxSize() const
{
    return {halfWidth * 2.0f, halfHeight * 2.0f};
}
#pragma endregion
} // namespace stw
