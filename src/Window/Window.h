#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/System.h"

namespace Zoom {
/**
 * \brief Contains any specifications to be passed to the Window during
 * initialization.
 */
struct WindowSystemSpecifications {
  U16 width, height;
  String title;
};

/**
 * \brief Implementation of the Window subsystem. Handles everything related
 * to creating, updating and destroying the GLFW window.
 */
class Window final : public System {
 public:
  /**
   * \brief Initializes the Window subsystem with the given specification.
   * Handles the initialization of GLFW and GLEW.
   * \param specs Any specifications to be passed to the Window, nullptr if none.
   */
  void Initialization(void* specs) override;

  /**
   * \brief Handles GLFW window events and swaps the buffers.
   */
  void Update() override;

  /**
   * \brief Destroys the GLFW window and terminates GLFW.
   */
  void Destroy() override;

  /**
   * \brief Verifies if the GLFW window should remain opened.
   * \return true if the window is open.
   */
  [[nodiscard]] bool IsOpen() const;

  /**
   * \brief Gets the handle to the GLFW window.
   * \return ptr to the GLFW window instance.
   */
  [[nodiscard]] GLFWwindow* GetWindow() const;

 private:
  GLFWwindow* m_Window = nullptr;
};

};  // namespace Zoom