cmake_minimum_required(VERSION 3.6)
project(simple-raytracer)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}")
set(CMAKE_CXX_FLAGS "-O3")

find_package(GLFW 3.0.0)
if (GLFW_FOUND)
    add_definitions( -DGLFW_FOUND )
    message("- GLFW Located")
else()
    message("- GLFW not located\n->Windowed Mode Disabled")
endif()
if(GLFW_FOUND AND (GLFW_VERSION VERSION_EQUAL 3.0 OR GLFW_VERSION VERSION_GREATER 3.0))
    add_definitions( -DGLFW_VERSION_3 )
endif()

find_package(OPENGL)
if (OPENGL_FOUND)
    add_definitions( -DOPENGL_FOUND )
    message("- OpenGL Located")
else()
    message("- OpenGL not located\n->Windowed Mode Disabled")
endif()

find_package(PNG)
if (PNG_FOUND)
    add_definitions( -DPNG_FOUND )
    message("- LibPNG Located")
else()
    message("- LibPNG not located\n->Image Mode Disabled")
endif()

find_package(YAMLCPP REQUIRED)

add_definitions(${PNG_DEFINITIONS})

set(SOURCE_FILES Source/main.cpp Source/Application.h Source/Application.cpp Source/Includes/glad.c Source/Raymarcher.cpp Source/Raymarcher.h Source/Geometry/Sphere.cpp Source/Geometry/Sphere.h Source/Geometry/SceneObject.h Source/Geometry/Vec3f.h Source/Geometry/Vec3f.cpp Source/Geometry/Ray.h Source/Geometry/Ray.cpp Source/Color.cpp Source/Color.h Source/Camera.h Source/Scene.cpp Source/Scene.h Source/PixelBufferBase.h Source/Screen.h Source/Camera.cpp Source/Util/NonCopyable.h Source/Util/Shader.h Source/Util/Shader.cpp Source/ScreenBuffer.cpp Source/ScreenBuffer.h Source/Lighting/LightBase.cpp Source/Lighting/LightBase.h Source/Material.h Source/Geometry/Intersection.cpp Source/Geometry/Intersection.h Source/Geometry/Vec4f.cpp Source/Geometry/Vec4f.h Source/Includes/glad.h Source/ConfigManager.cpp Source/ConfigManager.h Source/Constants.h Source/Lighting/DirectionalLight.cpp Source/Lighting/DirectionalLight.h Source/ImageBuffer.h Source/ImageBuffer.cpp Source/ByteColor.h Source/Geometry/Plane.cpp Source/Geometry/Plane.h Source/Geometry/Box.cpp Source/Geometry/Box.h)
add_executable(${CMAKE_PROJECT_NAME} ${SOURCE_FILES})
include_directories(${GLFW_INCLUDE_DIR} ${YAMLCPP_INCLUDE_DIR} ${OPENGL_INCLUDE_DIR})
target_link_libraries(${CMAKE_PROJECT_NAME} ${GLFW_LIBRARY}
        ${OPENGL_LIBRARY} ${YAMLCPP_LIBRARY} ${PNG_LIBRARIES} ${PNG_INCLUDE_DIRS})