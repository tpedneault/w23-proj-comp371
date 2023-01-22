#include "Engine.h"

#pragma region ERROR_CALLBACKS
/**
 * Base error callback for all libraries.
 * @param lib the name of the library from which the error originates.
 * @param error the error code.
 * @param description description of the error.
 */
void LogLibraryError(const char *lib, int error, const char *description) {
  // TODO: Output errors to a log file.
  std::cerr << "[" << lib << "] [ERROR] " << error << ": " << description << std::endl;
}

void ErrorCallbackGLFW(int error, const char *description) {
  LogLibraryError("GLFW", error, description);
}

void GLAPIENTRY ErrorCallbackOpenGL(GLenum source,
                                    GLenum type,
                                    GLuint id,
                                    GLenum severity,
                                    GLsizei length,
                                    const GLchar *message,
                                    const void *userParam) {
  std::stringstream ss;
  std::string errorTag = (type == GL_DEBUG_TYPE_ERROR) ? "Error" : "";
  ss << errorTag << " Type=0x" << type << ", severity=0x" << severity
     << ": " << message << std::endl;
  LogLibraryError("OPENGL", id, ss.str().c_str());
}
#pragma endregion

namespace sc {

Engine::Engine() = default;

void Engine::Start() {
  glfwSetErrorCallback(ErrorCallbackGLFW);
  if(!glfwInit()) {
    LogLibraryError("GLFW", -1, "Failed to initialize GLFW.");
    return;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  m_Window = glfwCreateWindow(1920, 1080, "Spacecraft Tracker", nullptr, nullptr);
  glfwMakeContextCurrent(m_Window);
  glfwSwapInterval(1); // enables v-sync

  GLenum glewInitResult = glewInit();
  if(glewInitResult) {
    LogLibraryError("GLEW", -1, reinterpret_cast<const char *>(glewGetErrorString(glewInitResult)));
  }

  glEnable(GL_DEBUG_OUTPUT);
  glDebugMessageCallback(ErrorCallbackOpenGL, nullptr);

  glViewport(0, 0, 1920, 1080);

  // Initialize modules.
  IMGUI_CHECKVERSION();
  m_GuiManager.Start(m_Window);

  while(!glfwWindowShouldClose(m_Window)) {
    glClearColor(0.07f, 0.13f, 0.17f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    // Perform tasks.
    m_GuiManager.Update();

    glfwSwapBuffers(m_Window);
    glfwPollEvents();
  }

  // Free all running modules.
  m_GuiManager.Close();

  glfwDestroyWindow(m_Window);
  glfwTerminate();
}

};