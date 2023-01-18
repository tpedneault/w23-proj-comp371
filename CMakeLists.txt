cmake_minimum_required(VERSION 3.24)
project(spacecraft-tracker)

set(CMAKE_BUILD_TYPE Debug)
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
file(GLOB imgui_srcs "extern/imgui/*.cpp")
include_directories(extern/imgui)

# Include header files.
include_directories(src)

# Find source files.
file(GLOB_RECURSE SRCS "src/**.cpp")

# Create executable and link libraries.
add_executable(spacecraft-tracker ${SRCS} ${imgui_srcs} src/systems/Gui.h src/systems/Gui.h)
target_link_libraries(spacecraft-tracker ${OPENGL_LIBRARIES} glfw libglew_static glm EnTT::EnTT)

# Copy the shaders directory to the build directory.
file(COPY shaders DESTINATION .)