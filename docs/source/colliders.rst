Colliders and Transforms
========================

Colliders
---------

Every colliders is a child of the ``Collider`` struct.
It is virutal pure and has methods to test collisions agains't every other collider type.
It also has a method to find the furthest point in a direction. This can be used for colliders that want to be compatible with the GJK algorithm.

Here are the available colliders : 

Circle collider
^^^^^^^^^^^^^^^

This is a collider in the shape of a circle.
It is defined by its center and radius. It can collide with itself and the AABB collider.
It could collider with the Box Collider, if GJK and SAT worked.

AABB Collider
^^^^^^^^^^^^^

This is an Axis Aligned Bounding Box.
This means it cannot rotate and can only be aligned with the X and Y axes.

Box Collider (WIP)
^^^^^^^^^^^^^^^^^^

A box that can be rotated.
It is defined by its center, half width and half height.
The collision of this collider must be done by an algorithm like SAT or GJK.
Unfortunatly they both don't work in the current version of this project, which makes it unusable.

Transform
---------

A transform is the struct that represents the location, scale and rotation in space of an object.
It has position and scale vectors and a rotation float.
Every object should use the transform as its position in the world.

Colliders use transform to know where they are in the world, that's why methods require it to know if a collision happenned.
Don't move an object by moving the center of its collider.