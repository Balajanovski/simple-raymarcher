cmake_minimum_required(VERSION 3.6)
project(simple-raytracer CXX C)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O3 -Wall")

find_package(GLFW 3.0.0 REQUIRED)
if (GLFW_FOUND)
    add_definitions( -DGLFW_FOUND )
    message("- GLFW Located")
    include_directories(${GLFW_INCLUDE_DIR})
else()
    message("- GLFW not located\n->Windowed Mode Disabled")
endif()
if(GLFW_FOUND AND (GLFW_VERSION VERSION_EQUAL 3.0 OR GLFW_VERSION VERSION_GREATER 3.0))
    add_definitions( -DGLFW_VERSION_3 )
endif()

find_package(OpenGL)
if (OPENGL_FOUND)
    add_definitions( -DOPENGL_FOUND )
    message("- OpenGL Located")
    include_directories(${OPENGL_INCLUDE_DIR})
else()
    message("- OpenGL not located\n->Windowed Mode Disabled")
endif()

find_package(PNG)
if (PNG_FOUND)
    add_definitions( -DPNG_FOUND )
    message("- LibPNG Located")
    include_directories(${PNG_INCLUDE_DIRS})
    add_definitions(${PNG_DEFINITIONS})
else()
    message("- LibPNG not located\n->Image Mode Disabled")
endif()

find_package(YamlCpp REQUIRED)
message("YamlCpp found\n->Include dir: ${YAMLCPP_INCLUDE_DIR}\n->Library: ${YAMLCPP_LIBRARY}")

link_directories("${YAMLCPP_INCLUDE_DIR}")

set(PROJECT_SOURCE_DIR ${CMAKE_SOURCE_DIR}/Source)

file(GLOB SOURCE_FILES
        "${PROJECT_SOURCE_DIR}/*.h"
        "${PROJECT_SOURCE_DIR}/*.cpp"

        "${PROJECT_SOURCE_DIR}/Includes/glad/*.h"
        "${PROJECT_SOURCE_DIR}/Includes/glad/*.c"

        "${PROJECT_SOURCE_DIR}/Geometry/*.h"
        "${PROJECT_SOURCE_DIR}/Geometry/*.cpp"

        "${PROJECT_SOURCE_DIR}/Lighting/*.h"
        "${PROJECT_SOURCE_DIR}/Lighting/*.cpp"

        "${PROJECT_SOURCE_DIR}/Util/*.h"
        "${PROJECT_SOURCE_DIR}/Util/*.cpp"
        )

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

target_link_libraries(${PROJECT_NAME} LINK_PUBLIC
        ${YAMLCPP_LIBRARY}
        ${PNG_LIBRARIES}
        ${GLFW_LIBRARIES}
        )

target_include_directories(${PROJECT_NAME} PUBLIC
        ${PROJECT_SOURCE_DIR}/Includes
        ${PROJECT_SOURCE_DIR}
        )
