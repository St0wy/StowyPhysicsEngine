cmake_minimum_required (VERSION 3.24)

project("StowyPhysicsEngine"
    VERSION 0.1.0
    DESCRIPTION "A basic physics engine in c++"
)

include(FetchContent)

if (NOT CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
    message(STATUS "This project has a top-level one called [${CMAKE_PROJECT_NAME}]")
else()
    message(STATUS "This project is a top-level one")
endif()

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

add_library(${PROJECT_NAME} STATIC)

set(public_headers
    include/Transform.hpp
    include/collision/BroadPhaseGrid.hpp
    include/collision/Collider.hpp
    include/collision/Collision.hpp
    include/collision/CollisionBody.hpp
    include/collision/CollisionWorld.hpp
    include/collision/Edge.hpp
    include/collision/Manifold.hpp
    include/collision/ManifoldFactory.hpp
    include/collision/Projection.hpp
    include/collision/Simplex.hpp
    include/dynamics/Solver.hpp
    include/dynamics/DynamicsWorld.hpp
    include/dynamics/Rigidbody.hpp
    include/math/Vector2.hpp
)

target_sources(${PROJECT_NAME} 
    PRIVATE
    "src/collision/BroadPhaseGrid.cpp"
    "src/collision/Collider.cpp"
    "src/collision/CollisionBody.cpp"
    "src/collision/CollisionWorld.cpp"
    "src/collision/Edge.cpp"
    "src/collision/Manifold.cpp"  
    "src/collision/ManifoldFactory.cpp"
    "src/collision/Projection.cpp" 
    "src/collision/Simplex.cpp"
    "src/dynamics/DynamicsWorld.cpp"
    "src/dynamics/Rigidbody.cpp"
    "src/dynamics/Solver.cpp"
    "src/math/Vector2.cpp"
    ${public_headers}
)

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