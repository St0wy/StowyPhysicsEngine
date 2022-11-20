cmake_minimum_required (VERSION 3.24)

include(FetchContent)

project("Benchmark" VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

# Get Google Benchmark
set(BENCHMARK_VERSION "v1.7.1")

FetchContent_Declare(
    benchmark
    GIT_REPOSITORY "https://github.com/google/benchmark.git"
    GIT_TAG        "${BENCHMARK_VERSION}"
)
set(BENCHMARK_DOWNLOAD_DEPENDENCIES ON)
FetchContent_MakeAvailable(benchmark)

include_directories(include/)

set(SOURCE
    "src/main.cpp"
    "src/AabbBox.cpp"
    "src/Circle.cpp"
    "src/Entity.cpp"
)

add_executable(${PROJECT_NAME} ${SOURCE})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE StowyPhysicsEngine)

target_link_libraries(${PROJECT_NAME} PRIVATE benchmark::benchmark)
