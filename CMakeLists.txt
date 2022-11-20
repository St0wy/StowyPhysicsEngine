cmake_minimum_required (VERSION 3.24)

# Name of the solution
project("DemoPhysicsEngine" VERSION 0.1.0)

if ( NOT CMAKE_BUILD_TYPE )
    message("Build Type not set, defaulting to Debug...")
    set( CMAKE_BUILD_TYPE Debug )
else()
    message(STATUS "Build Type is : ${CMAKE_BUILD_TYPE}")
endif()

add_subdirectory("StowyPhysicsEngine")

add_subdirectory("Demo")

add_subdirectory("benchmark")
