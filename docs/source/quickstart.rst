Quickstart
==========

The engine does not handle memory itself, everything is handled with raw pointers.
The user is responsible for the handling of memory.

The engine has been separated into two parts : with dynamics and without.
You can have a world with only collisions and also a world with dynamics.

Without Dynamics
----------------

Here are the steps to make a world with collisions :

#. Create a collision world
#. Create a vector of `CollisionBody`
#. Create bodies and give them colliders
#. Add a callback to the body if you want to detect the collision
#. Step the world in a loop

.. code-block:: cpp

    CollisionWorld world;

    std::vector<std::unique_ptr<CollisionBody>> bodies;

    auto body = std::make_unique<CollisionBody>();
    auto collider = std::make_unique<CircleCollider>(1.0f); // radius = 1
    body->SetCollider(collider.get());
    body->SetCollisionCallback([](const Collision &col, float deltaTime)
    { 
        std::cout << "Collision happened !\n"; }
    );

    bodies.push_back(std::move(body));

    while (true)
    {
        world.ResolveCollisions(deltaTime);
    }

With Dynamics
-------------

Creating a world with dynamics is pretty similar to one without

Here are the steps to make a world with collisions :

#. Create a dynamics world
#. Add solvers to the world
#. Create a vector of `Rigidbody`
#. Create bodies and give them colliders
#. Step the world in a loop

.. code-block:: cpp

    DynamicsWorld world;

    auto impulseSolver = std::make_unique<ImpulseSolver>();
    auto smoothPositionSolver = std::make_unique<SmoothPositionSolver>();
    world.AddSolver(impulseSolver.get());
    world.AddSolver(smoothPositionSolver.get());

    std::vector<std::unique_ptr<Rigidbody>> bodies;

    auto body = std::make_unique<Rigidbody>();
    auto collider = std::make_unique<CircleCollider>(1.0f); // radius = 1
    body->SetCollider(collider.get());

    bodies.push_back(std::move(body));

    while (true) 
    {
        world.Step(deltaTime);
    }
