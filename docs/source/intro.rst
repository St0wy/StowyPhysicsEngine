Introduction
============

This is a 2D physics engine made for the GPR4400 module at SAE Institute.

You can see the doxygen documentation `here <https://st0wy.github.io/GPR4400-PhysicsEngine/>`_.

Core concepts
-------------

**Body**

A body is an object in the physics engine.
The engine has a collision body and a rigid body.

**Rigidbody** 

A rigidbody is a body affected by dynamics.
It cannot be deformed, that is the distance between any two points on the body is constant.

**World**

In this engine, the word world refers to the class that contains the list of bodies and handle the collisions
and / or dynamics between them.

**Collider**

A collider is the thing that defines the shape that will collide with other collider. 
It can be of many shapes and they dictate how collisions are solved between objects.

**Manifold**

In this physics engine, the term manifold refers to the points that are usefull to solve a collision.

**Solver**

A solver is responsible for reacting to collisions and moving the objects away from eachother.

**Transform**

The transform of an object is its position, scale and rotation.