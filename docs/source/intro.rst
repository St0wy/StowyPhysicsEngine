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
Technically the manifold is all the points that are involved in a collision,
but in my case, it's more of a `MTV <https://gamedev.stackexchange.com/a/32550/158616>`_ (Minimum Translation Vector)

**Solver**

A solver is responsible for reacting to collisions and moving the objects away from eachother.

**Transform**

The transform of an object is its position, scale and rotation.

**Dynamics**

In this documentation I often mention "With Dynamics" and "Without Dynamics".
Having dynamics means that after a collision is detected, 
it is solved by a solver to make the objects not collide anymore.
Using the "Without Dynamics" version means that the collisions will be detected, but that's all.