# GPR4400-PhysicsEngine

This project is a 2D physics engine written in C++.

Please note that this is an old project that I did with less than 1 year of experience with C++. I would not make the same choices today if I had to make a project like that again :)

The wiki is hosted on [Read The Docs](https://stowy-physics-engine.readthedocs.io/en/latest/)
and the API Documentation (Doxygen) on [GitHub Pages](https://st0wy.github.io/StowyPhysicsEngine/).

It has :

-   Circle -> Circle collisions
-   Circle -> [AABB](https://en.wikipedia.org/wiki/Minimum_bounding_box#Axis-aligned_minimum_bounding_box) collisions
-   AABB -> AABB collisions
-   A failed attempt at [SAT](https://en.wikipedia.org/wiki/Hyperplane_separation_theorem)
-   A failed attempt at [GJK](https://en.wikipedia.org/wiki/Gilbert%E2%80%93Johnson%E2%80%93Keerthi_distance_algorithm)
-   Broad phase collision detection with a grid

## Getting started

1. Get a C++20 compiler
2. Build with CMake :

```bash
cmake -S . -B .\build\
cmake --build .\build\
```

When building in Debug mode, you need to rename `freetyped.dll` to `freetype.dll` in the folder where `Demo.exe` is located.
I don't know why this is necessary, but I guess it's a problem with my CMake setup with SFML.

By default the demo isn't built and only the library is. To change that you must switch the CMake option `SPE_BUILD_DEMO` to `ON`.
This can be done either in the GUI, or in the terminal by adding `-DSPE_BUILD_DEMO=ON` to the command.
You could also change the line in the `CMakeLists.txt`.

## Dependencies

The physics engine doesn't have any dependencies, and can be built alone as a library.

The demo scene has a dependency on [SFML](https://www.sfml-dev.org/) but it is retrieved using CMake's [FetchContent](https://cmake.org/cmake/help/latest/module/FetchContent.html)
so you don't have to use something like vcpkg.

## Folder structure

There are two main folders in this project :

-   StowyPhysicsEngine
-   Demo

`StowyPhysicsEngine` is the physics engine in itself.
It is setup as a CMake library.

`Demo` is the SFML project to visualise the physics engine.

They each have their own `CMakeList.txt` but there is
also a main one that includes both to be able to build
everything at once.
