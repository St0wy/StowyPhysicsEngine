CollisionWorld world;

std::vector<std::unique_ptr<CollisionBody>> bodies;

auto body = std::make_unique<CollisionBody>();
auto collider = std::make_unique<CircleCollider>(1.0f); // radius = 1
body->SetCollider(collider.get());
body->SetCollisionCallback([](const Collision &col, float deltaTime)
                           { std::cout << "Collision happened !\n"; });

bodies.push_back(std::move(body));

while (true)
{
    world.ResolveCollisions(deltaTime);
}