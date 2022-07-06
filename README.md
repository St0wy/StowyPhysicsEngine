#  GPR4400-PhysicsEngine

This project is a 2D physics engine written in C++.
It uses SFML to display the demo scenes, but the physics engine in itself doesn't rely on any library.

The wiki is hosted on [Read The Docs](https://stowy-physics-engine.readthedocs.io/en/latest/)
and the API Documentation on [GitHub Pages](https://st0wy.github.io/GPR4400-PhysicsEngine/).


It has :

- Circle -> Circle collisions
- Circle -> [AABB](https://en.wikipedia.org/wiki/Minimum_bounding_box#Axis-aligned_minimum_bounding_box) collisions
- AABB -> AABB collisions
- A failed attempt at [SAT](https://en.wikipedia.org/wiki/Hyperplane_separation_theorem)
- A failed attempt at [GJK](https://en.wikipedia.org/wiki/Gilbert%E2%80%93Johnson%E2%80%93Keerthi_distance_algorithm)

## Getting started

1. Install [Vcpkg](https://vcpkg.io/)
2. Get a C++20 compiler
3. Build with CMake :

```bash
cmake -S . -B .\build\
cmake --build .\build\
```

## Folder structure

There are two main folders in this project : 

- StowyPhysicsEngine
- Demo

`StowyPhysicsEngine` is the physics engine in itself.
It is setup as a CMake library.

`Demo` is the SFML project to visualise the physics engine.

They each have their own `CMakeList.txt` but there is
also a main one that includes both to be able to build
everything at once.

For more informations about the physics engine, check out the [Wiki](https://github.com/St0wy/GPR4400-PhysicsEngine/wiki)