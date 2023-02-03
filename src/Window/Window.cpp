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

void Window::OnInitialization(void* specs) {
  glfwSetErrorCallback(ErrorCallbackGLFW);
  if (!glfwInit()) {
    std::cerr << "Failed to initialize GLFW." << std::endl;
    exit(EXIT_FAILURE);
  }

  /** Set the OpenGL version to use. **/
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

  /** Create the GLFW window and set it as the current OpenGL context. **/
  const auto [width, height, title] =
      *(static_cast<WindowSystemSpecifications*>(specs));
  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

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

void Window::OnUpdate() {
  glfwPollEvents();
  glfwSwapBuffers(m_Window);

  // Check if the window has been closed.
  if (glfwWindowShouldClose(m_Window)) {
    PublishEvent({EventCode::ExitApplication});
  }
}

void Window::OnDestroy() {
  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

std::vector<std::shared_ptr<System>> Window::GetDependencies() const {
  return {};
}

bool Window::IsOpen() const { return !glfwWindowShouldClose(m_Window); }

GLFWwindow* Window::GetWindow() const { return m_Window; }

void Window::ProcessEvent(const Event& e) {}

};  // namespace Zoom