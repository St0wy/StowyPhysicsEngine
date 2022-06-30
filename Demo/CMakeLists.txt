cmake_minimum_required (VERSION 3.15)

project("Demo" VERSION 0.1.0)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED True)

set_property(GLOBAL PROPERTY USE_FOLDERS On)

# Add data files
file(GLOB_RECURSE DATA_FILES data/*)
source_group("data/" FILES ${DATA_FILES})
foreach(DATA ${DATA_FILES})
    get_filename_component(FILE_NAME ${DATA} NAME)
    get_filename_component(PATH_NAME ${DATA} DIRECTORY)
    get_filename_component(EXTENSION ${DATA} EXT)
    file(RELATIVE_PATH PATH_NAME "${PROJECT_SOURCE_DIR}" ${PATH_NAME})
    set(DATA_OUTPUT "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}")
    add_custom_command(
            OUTPUT ${DATA_OUTPUT}
            DEPENDS ${DATA}
            DEPENDS
            COMMAND ${CMAKE_COMMAND} -E copy ${DATA} "${PROJECT_BINARY_DIR}/${PATH_NAME}/${FILE_NAME}"
    )
    list(APPEND DATA_BINARY_FILES ${DATA_OUTPUT})
endforeach()

add_custom_target(
        DataTarget-${PROJECT_NAME}
        DEPENDS ${DATA_BINARY_FILES} ${DATA_FILES})

# Get SFML and box2d libraries
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics main CONFIG REQUIRED)
find_package(spdlog REQUIRED)

include_directories(include/)

add_executable(${PROJECT_NAME})
# add_executable(${PROJECT_NAME} win32)

target_sources(${PROJECT_NAME}
    PRIVATE
    src/main.cpp
    src/Game.cpp
)

# Add data dependencies
add_dependencies(${PROJECT_NAME} DataTarget-${PROJECT_NAME})

# Link libraries
target_link_libraries(${PROJECT_NAME} PRIVATE StowyPhysicsEngine)
target_link_libraries(${PROJECT_NAME} PRIVATE spdlog::spdlog)

target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main sfml-graphics sfml-audio sfml-window sfml-system)

if(MSVC)
    target_link_libraries(${PROJECT_NAME} PRIVATE sfml-main FLAC OpenAL OpenGL Vorbis)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE X11 FLAC UDev OpenAL  ${OPENGL_LIBRARIES} )
endif()
