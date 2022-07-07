Integration with SFML
=====================

In this section of the wiki, I will explain how to integrate the physics engine with SFML.
I will show some example code, but I will only show how to use the ``DynamicsWorld``.
The logic is the same with the ``CollisionWorld``.

The first thing to do is to have a basic SFML project.
I will not go in detail on how to do this here,
but the basic idea of how I did it, is that I created a ``Game`` class 
that contains the main game data and the SFML ``sf::RenderWindow``.

The Entity
----------

Before we create the world, we're gonna create a class that will be able to be drawn by SFML.
It's also gonna hold its ``Rigidbody`` and a reference to the world.
The reference is used to remove the rigidbody from the world in the destructor of the entity.

.. code-block:: cpp

    class Entity
        : public sf::Drawable, public sf::Transformable
    {
    public:
        explicit Entity(DynamicsWorld& dynWorld);
        Entity(DynamicsWorld& dynWorld, Vector2 pos);
        ~Entity() override;

        Rigidbody* RigidBody() const;

        virtual void Update(sf::Time deltaTime);

    protected:
        DynamicsWorld& _dynWorld;
        std::unique_ptr<Rigidbody> _rb;
    };

This is the structure of our Entity.
In the constructor, we will set its position and say 
that we want the body to be affected by gravity and responses.
In the destructor, we remove the body from the world.

.. code-block:: cpp

    Entity::Entity(DynamicsWorld& dynWorld, const Vector2 pos)
        : _dynWorld(dynWorld), _rb(std::make_unique<Rigidbody>())
    {
        _rb->SetTransform({ pos, Vector2(1, 1), 0 });
        // Makes the objects affected by gravity
        _rb->SetTakesGravity(true);
        // Indicates that the body is affected by collision responses
        _rb->SetIsKinematic(true);
        _rb->SetRestitution(0.5f);
    }

    Entity::~Entity()
    {
        _dynWorld.RemoveCollisionBody(RigidBody());
    }

We also need to update the ``sf::Drawabe`` in the update method.

.. code-block:: cpp

    void Entity::Update(sf::Time deltaTime)
    {
        setPosition(SpePosToSfml(_rb->Trans()->position));
        setScale(SpeVecToSfml(_rb->Trans()->scale));
        setRotation(_rb->Trans()->rotation);
    }

This is basically all we need for the Entity class.
We will now look at a child of it, the ``Circle`` class.

.. code-block:: cpp

    class Circle final : public Entity
    {
    public:
        Circle(DynamicsWorld& dynWorld, float radius, Vector2 pos);
        void draw(sf::RenderTarget& target, sf::RenderStates states) const override;
    private:
        sf::CircleShape _shape;
        std::unique_ptr<CircleCollider> _collider;
    };

This class contains the shape that will be drawn and overrides the draw method for SFML.
Here is its constructor : 

.. code-block:: cpp

    Circle::Circle(DynamicsWorld& dynWorld, const float radius, const Vector2 pos)
        : Entity(dynWorld, pos),
        _shape(radius),
        _collider(std::make_unique<CircleCollider>())
    {
        _collider->radius = radius;
        _dynWorld.AddRigidbody(RigidBody());
        _rb->SetCollider(_collider.get());
        _shape.setOrigin(radius, radius);
    }

That's all for the entity, we will now talk about the physics world.

Physics World
----------------------

The data that the physics engine needs is a world to have bodies in.
It also needs a list of Entities and solvers.

Here is how they are stored :

.. code-block:: cpp

    class DemoBallsAndCube
    {
    public:
        DemoBallsAndCube();
        void StartMainLoop();
    
    private:
        sf::RenderWindow _window;
        DynamicsWorld _world;
        std::vector<std::unique_ptr<Entity>> _entities;
        std::unique_ptr<ImpulseSolver> _impulseSolver;
        std::unique_ptr<SmoothPositionSolver> _smoothPositionSolver;
    };

Then in the main loop, the entities have to be updated alongside the physics world.

.. code-block:: cpp

    // Step the physics
    _world.Step(deltaTime.asSeconds());
    
    // Update the entites
    for (const auto& entity : _entities)
    {
        entity->Update(deltaTime);
    }

The entities also have to be drawn.

.. code-block:: cpp

    // Render all the entities
    for (const auto& entity : _entities)
    {
        _window.draw(*entity);
    }

And that is all for the link between the physics engine and SFML.