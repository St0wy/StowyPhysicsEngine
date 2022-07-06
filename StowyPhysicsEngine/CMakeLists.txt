cmake_minimum_required (VERSION 3.15)

project("StowyPhysicsEngine"
    VERSION 0.1.0
    DESCRIPTION "A basic physics engine in c++"
)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC)

target_sources(${PROJECT_NAME} 
    PRIVATE
    src/collision/Collider.cpp
    src/collision/CollisionBody.cpp
    src/collision/CollisionWorld.cpp
    "src/collision/ManifoldFactory.cpp"
    src/collision/Simplex.cpp
    src/dynamics/DynamicsWorld.cpp
    src/dynamics/ImpulseSolver.cpp
    src/dynamics/Rigidbody.cpp
    src/dynamics/SmoothPositionSolver.cpp
    src/math/Vector2.cpp
 "src/collision/Manifold.cpp"  "src/collision/Edge.cpp" "src/collision/Projection.cpp")

target_include_directories(${PROJECT_NAME}
    PRIVATE
        # where the library itself will look for its internal headers
        ${CMAKE_CURRENT_SOURCE_DIR}/src
    PUBLIC
        # where top-level project will look for the library's public headers
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        # where external projects will look for the library's public headers
        $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
)

set(public_headers
    include/Solver.hpp
    include/Transform.hpp
    include/collision/Collider.hpp
    include/collision/Collision.hpp
    include/collision/CollisionBody.hpp
    include/collision/CollisionWorld.hpp
    include/collision/ManifoldFactory.hpp
    include/collision/Manifold.hpp
    include/collision/Simplex.hpp
    include/dynamics/DynamicsWorld.hpp
    include/dynamics/ImpulseSolver.hpp
    include/dynamics/Rigidbody.hpp
    include/dynamics/SmoothPositionSolver.hpp
    include/math/Vector2.hpp
    include/collision/Edge.hpp
    include/collision/Projection.hpp
)

# not for MSVC
if(CMAKE_COMPILER_IS_GNUCXX)
    # compile options for this target only
    # treat warnings as errors
    target_compile_options(${PROJECT_NAME} PRIVATE -Werror)
endif()

# where to find our CMake modules
set(CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
message(STATUS "CMake module path: ${CMAKE_MODULE_PATH}")
include(Installing)

# Get spdlog
find_package(spdlog REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)
