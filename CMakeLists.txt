# CMakeList.txt : Top-level CMake project file, do global configuration
# and include sub-projects here.
cmake_minimum_required (VERSION 3.8)

# Name of the solution
project ("physics-engine")

# Include sub-projects.
set(EXECUTABLE_CUSTOM_NAME "MathEngine")
add_subdirectory ("MathEngine")

set(EXECUTABLE_CUSTOM_NAME "Exo")
add_subdirectory ("Exo")

set(EXECUTABLE_CUSTOM_NAME "PhysicsEngine")
add_subdirectory ("PhysicsEngine")
