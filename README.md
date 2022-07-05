#  GPR4400-PhysicsEngine

This project is a 2D physics engine written in C++.
It uses SFML to display the demo scenes, but the physics engine in itself doesn't rely on any library.

## Getting started

1. Install [Vcpkg](https://vcpkg.io/)
2. Build with CMake :

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