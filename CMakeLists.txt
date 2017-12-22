cmake_minimum_required(VERSION 3.6)
project(simple-raytracer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")

find_package(GLFW 3.0.0 REQUIRED)
if(GLFW_FOUND AND (GLFW_VERSION VERSION_EQUAL 3.0 OR GLFW_VERSION VERSION_GREATER 3.0))
    add_definitions( -DGLFW_VERSION_3 )
endif()

find_package(OPENGL REQUIRED)

set(SOURCE_FILES Source/main.cpp Source/Application.h Source/Application.cpp Source/Includes/GetGL.h Source/Includes/glad.c Source/Raymarcher.cpp Source/Raymarcher.h Source/Geometry/Sphere.cpp Source/Geometry/Sphere.h Source/Geometry/SceneObject.h Source/Geometry/Vec3f.h Source/Geometry/Vec3f.cpp Source/Geometry/Ray.h Source/Geometry/Ray.cpp Source/Color.cpp Source/Color.h Source/Camera.h Source/Scene.cpp Source/Scene.h Source/Pixel_Stream_Base.h Source/Screen.h Source/Camera.cpp Source/Util/NonCopyable.h Source/Util/Shader.h Source/Util/Shader.cpp Source/Screen_Stream.cpp Source/Screen_Stream.h Source/Light.cpp Source/Light.h Source/Material.h Source/Geometry/Intersection.cpp Source/Geometry/Intersection.h)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
include_directories(${GLFW_INCLUDE_DIR})
include_directories(${OPENCL_INCLUDE_DIRS})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GLFW_LIBRARY}
        ${OPENGL_LIBRARY})