# CMakeList.txt : CMake project for Formative10, include source and define
# project specific logic here.
cmake_minimum_required (VERSION 3.8)

set (CMAKE_CXX_STANDARD 20)
set (CMAKE_CXX_STANDARD_REQUIRED ON)

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
        DataTarget-${EXECUTABLE_CUSTOM_NAME}
        DEPENDS ${DATA_BINARY_FILES} ${DATA_FILES})

# Get SFML and box2d libraries
find_package(OpenGL REQUIRED)
find_package(SFML COMPONENTS system window graphics main CONFIG REQUIRED)
find_package(box2d CONFIG REQUIRED)
include_directories(include/)

# Add source to this project's executable.  
file(GLOB_RECURSE PROJECT_SRC src/*.cpp include/*.h)

# TODO: use the line with "win32" in it if you don't want the console
add_executable(${EXECUTABLE_CUSTOM_NAME} ${PROJECT_SRC})
# add_executable(${EXECUTABLE_CUSTOM_NAME} win32 ${PROJECT_SRC})

# Add data dependencies
add_dependencies(${EXECUTABLE_CUSTOM_NAME} DataTarget-${EXECUTABLE_CUSTOM_NAME})

# Link libraries
target_link_libraries(${EXECUTABLE_CUSTOM_NAME} PRIVATE sfml-main sfml-graphics sfml-audio sfml-window sfml-system)

if(MSVC)
target_link_libraries(${EXECUTABLE_CUSTOM_NAME} PRIVATE sfml-main FLAC OpenAL OpenGL Vorbis)
else()
target_link_libraries(${EXECUTABLE_CUSTOM_NAME} PRIVATE X11 FLAC UDev OpenAL  ${OPENGL_LIBRARIES} )
endif()

target_link_libraries(${EXECUTABLE_CUSTOM_NAME} PRIVATE box2d::box2d)