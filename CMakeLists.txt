cmake_minimum_required(VERSION 3.20)
project(spacecraft-tracker)

set(CMAKE_CXX_STANDARD 20)

# Add OpenGL.
find_package(OpenGL REQUIRED)
include_directories(${OPENGL_INCLUDE_DIRS})

# Only build the GLFW library.
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

# Add dependencies.
add_subdirectory(extern/glfw)
add_subdirectory(extern/glew-cmake)
add_subdirectory(extern/glm)
add_subdirectory(extern/entt)

# Include the ImGui library.
file(GLOB imgui_srcs "extern/imgui-docking/*.cpp")
include_directories(extern/imgui-docking)
file(GLOB imgui_backends
        "extern/imgui-docking/backends/imgui_impl_glfw.cpp"
        "extern/imgui-docking/backends/imgui_impl_glfw.h"
        "extern/imgui-docking/backends/imgui_impl_opengl3.cpp"
        "extern/imgui-docking/backends/imgui_impl_opengl3.h"
        "extern/imgui-docking/backends/imgui_impl_opengl3_loader.h"
        )

# Include header files.
include_directories(src)

# Find source files.
file(GLOB_RECURSE SRCS "src/**.cpp")

# Create executable and link libraries.
add_executable(spacecraft-tracker ${SRCS} ${imgui_srcs} ${imgui_backends} src/core/EventBus.cpp src/core/EventBus.h)
target_link_libraries(spacecraft-tracker ${OPENGL_LIBRARIES} glfw libglew_static glm EnTT::EnTT)

# Copy the shaders directory to the build directory.
file(COPY shaders DESTINATION .)
file(COPY assets DESTINATION .)