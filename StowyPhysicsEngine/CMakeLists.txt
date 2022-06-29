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
    src/Collider.cpp
    src/CollisionBody.cpp
    src/CollisionWorld.cpp
    src/Collisions.cpp
    src/DynamicsWorld.cpp
    src/Edge.cpp
    src/Game.cpp
    src/ImpulseSolver.cpp
    src/Projection.cpp
    src/Rigidbody.cpp
    src/Simplex.cpp
    src/SmoothPositionSolver.cpp
    src/Vector2.cpp
    src/main.cpp
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

set(public_headers
    include/Collider.hpp
    include/CollisionBody.hpp
    include/CollisionPoints.hpp
    include/CollisionWorld.hpp
    include/Collisions.hpp
    include/Consts.hpp
    include/DynamicsWorld.hpp
    include/Edge.hpp
    include/Game.hpp
    include/ImpulseSolver.hpp
    include/Projection.hpp
    include/Rigidbody.hpp
    include/Simplex.hpp
    include/SmoothPositionSolver.hpp
    include/Solver.hpp
    include/Transform.hpp
    include/VecUtils.hpp
    include/Vector2.hpp
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

# Get SFML
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics main CONFIG REQUIRED)
find_package(spdlog REQUIRED)

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-audio sfml-window sfml-system)

if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main FLAC OpenAL OpenGL Vorbis)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE X11 FLAC UDev OpenAL  ${OPENGL_LIBRARIES} )
endif()