#include "Window/Window.h"

#include "Renderer/Renderer.h"

namespace Zoom {

void ErrorCallbackGLFW(int error, const char* description) {
  std::cerr << description << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, const I32 width,
                             const I32 height) {
  SystemLocator<Renderer>::Get()->SetViewportSize(width, height);
}

void Window::Initialization(void* specs) {
  glfwSetErrorCallback(ErrorCallbackGLFW);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  /** Set the OpenGL version to use. **/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  /** Create the GLFW window and set it as the current OpenGL context. **/
  const auto [width, height, title] = *(static_cast<WindowSystemSpecifications*>(specs));
  m_Window = glfwCreateWindow(width, height, title.c_str(),
                              nullptr, nullptr);

  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1);  // Enables V-Sync.
  glfwSetFramebufferSizeCallback(m_Window, FramebufferSizeCallback);

  const GLenum result = glewInit();
  if (result) {
    std::cerr << "Failed to initialize GLEW. err="
              << reinterpret_cast<const char*>(glewGetErrorString(result))
              << std::endl;
    exit(EXIT_FAILURE);
  }
}

void Window::Update() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);
}

void Window::Destroy() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

bool Window::IsOpen() const { return !glfwWindowShouldClose(m_Window); }

GLFWwindow* Window::GetWindow() const { return m_Window; }

};  // namespace Zoom