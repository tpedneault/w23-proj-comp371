cmake_minimum_required(VERSION 3.20)
project(ambrosia)

# Set the C++ version to use.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Only build the GLFW library.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

set(ASSIMP_BUILD_ZLIB ON CACHE BOOL "" FORCE)
set(ASSIMP_INSTALL OFF CACHE BOOL "" FORCE)
set(ASSIMP_SHARED_LIBS OFF CACHE BOOL "" FORCE)

set(FMT_DOC OFF CACHE BOOL "" FORCE)
set(FMT_TEST OFF CACHE BOOL "" FORCE)

# Find OpenGL
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Build dependencies.
add_subdirectory(extern/glfw)
add_subdirectory(extern/glew-cmake)
add_subdirectory(extern/glm)
add_subdirectory(extern/assimp)
add_subdirectory(extern/fmt)
#add_subdirectory(extern/scene-import-and-export)

#include_directories(extern/scene-import-and-export/src)
include_directories(extern/stb)

# Add the ImGui library with the appropriate backends.
include_directories(extern/imgui-docking)
file(GLOB imgui_src "extern/imgui-docking/*.cpp")
file(GLOB imgui_backends
        "extern/imgui-docking/backends/imgui_impl_glfw.cpp"
        "extern/imgui-docking/backends/imgui_impl_glfw.h"
        "extern/imgui-docking/backends/imgui_impl_opengl3.cpp"
        "extern/imgui-docking/backends/imgui_impl_opengl3.h"
        "extern/imgui-docking/backends/imgui_impl_opengl3_loader.h"
        "extern/imgui-docking/misc/cpp/imgui_stdlib.cpp"
        )

include_directories(extern/ImGuiColorTextEdit)
file(GLOB imgui_text_edit_src "extern/ImGuiColorTextEdit/*.cpp")

include_directories(extern/imnodes)
file(GLOB imnodes_src "extern/imnodes/*.cpp")

# Add Zoom Engine source files.
include_directories(src)
file(GLOB_RECURSE ambrosia_src "src/**.cpp")

add_executable(ambrosia ${ambrosia_src} ${imgui_src} ${imgui_backends} ${imgui_text_edit_src} ${imnodes_src})
target_link_libraries(ambrosia ${OPENGL_LIBRARIES} glfw libglew_static glm assimp fmt)
