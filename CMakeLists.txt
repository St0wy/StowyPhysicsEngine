cmake_minimum_required(VERSION 3.24)

# Name of the solution
project("DemoPhysicsEngine" VERSION 0.1.0)

if(NOT CMAKE_BUILD_TYPE)
  message("Build Type not set, defaulting to Debug...")
  set(CMAKE_BUILD_TYPE Debug)
endif()

option(SPE_BUILD_DEMO "Set this to ON to build the SFML demo of the project.")

add_subdirectory("StowyPhysicsEngine")

if(SPE_BUILD_DEMO)
  add_subdirectory("Demo")
endif()
