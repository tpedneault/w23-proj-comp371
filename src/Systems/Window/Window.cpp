#include "Systems/Window/Window.h"

namespace Zoom {

void
ErrorCallbackGLFW(int error, const char* description)
{
  std::cerr << description << std::endl;
}

void GLAPIENTRY
ErrorCallbackOpenGL(GLenum source,
                    GLenum type,
                    GLuint id,
                    GLenum severity,
                    GLsizei length,
                    const GLchar* message,
                    const void* userParam)
{
  std::cerr << ((type == GL_DEBUG_TYPE_ERROR) ? "Error" : "") << " Type=0x"
            << type << ", severity=0x" << severity << ": " << message
            << std::endl;
}

void
FramebufferSizeCallback(GLFWwindow* window, const I32 width, const I32 height)
{
  glViewport(0, 0, width, height);
}

void
Window::Initialize(void* specs)
{
  glfwSetErrorCallback(ErrorCallbackGLFW);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  /** Create the GLFW window and set it as the current OpenGL context. **/
  const auto data = *(static_cast<WindowSystemSpecifications*>(specs));
  m_Window = glfwCreateWindow(
    data.width, data.height, data.title.c_str(), nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1); // Enables V-Sync.
  glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

  const GLenum result = glewInit();
  if (result) {
    std::cerr << "Failed to initialize GLEW. err="
              << reinterpret_cast<const char*>(glewGetErrorString(result))
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void
Window::Update()
{
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void
Window::Destroy()
{
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

bool
Window::IsOpen() const
{
  return !glfwWindowShouldClose(m_Window);
}

GLFWwindow*
Window::GetWindow() const
{
  return m_Window;
}

};