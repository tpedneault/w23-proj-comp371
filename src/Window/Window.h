#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Core/System.h"

namespace ambr {

constexpr float WINDOW_TARGET_FPS = 60.0f;

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
  String GetName() override { return "Window"; }

  /**
   * \brief Initializes the Window subsystem with the given specification.
   * Handles the initialization of GLFW and GLEW.
   * \param specs Any specifications to be passed to the Window, nullptr if
   * none.
   */
  void OnInitialization(void *specs) override;

  /**
   * \brief Handles GLFW window events and swaps the buffers.
   */
  void OnUpdate() override;

  /**
   * \brief Destroys the GLFW window and terminates GLFW.
   */
  void OnDestroy() override;

  [[nodiscard]] std::vector<std::shared_ptr<System>> GetDependencies()
  const override;

  /**
   * Gets the timestep since the last frame.
   */
  [[nodiscard]] float GetDeltaTime() const;

  /**
   * \brief Verifies if the GLFW window should remain opened.
   * \return true if the window is open.
   */
  [[nodiscard]] bool IsOpen() const;

  /**
   * \brief Gets the handle to the GLFW window.
   * \return ptr to the GLFW window instance.
   */
  [[nodiscard]] GLFWwindow *GetWindow() const;

  /**
   * \brief Processes the given event.
   * \param e event to handle
   */
  void ProcessEvent(const Event &e) override;

  void ToggleFullscreen() const;

 private:
  float m_DeltaTime = 0.0f;
  double m_TimeLastFrame = 0.0f;
  GLFWwindow *m_Window = nullptr;
};

};  // namespace ambr