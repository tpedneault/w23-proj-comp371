#include "Window/Window.h"

#include "Renderer/Renderer.h"

namespace ambr {

void ErrorCallbackGLFW(int error, const char* description) {
  std::cerr << description << std::endl;
}

void FramebufferSizeCallback(GLFWwindow* window, const I32 width,
                             const I32 height) {
  SystemLocator<Renderer>::Get()->SetViewportSize(width, height);
}

void KeyCallback(GLFWwindow* window, I32 key, I32 scanCode, I32 action, I32 mods) {
  // Forward W, A, S, D events to the other subsystems.
  switch(key) {
    case GLFW_KEY_A:
    case GLFW_KEY_W:
    case GLFW_KEY_S:
    case GLFW_KEY_D:
      SystemLocator<Window>::Get()->PublishEvent({ EventCode::KeyPressed, new I32(key) });
      break;
  }
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

  /** Create the GLFW window and set it as the current OpenGL context. **/
  const auto [width, height, title] =
      *(static_cast<WindowSystemSpecifications*>(specs));
  m_Window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);

  glfwSetKeyCallback(m_Window, ambr::KeyCallback);

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

  m_TimeLastFrame = glfwGetTime();
}

void Window::OnUpdate() {
  double m_CurrentTime = glfwGetTime();
  m_DeltaTime = (m_CurrentTime - m_TimeLastFrame);
  m_TimeLastFrame = m_CurrentTime;

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

void Window::ToggleFullscreen() const { AMBR_LOG_TRACE("Toggling fullscreen"); }

float Window::GetDeltaTime() const {
  return m_DeltaTime;
}

};  // namespace ambr