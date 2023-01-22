/**
  * @file Gui.h
  *  
  * @brief Handles the GUI for the application.
  *
  * @author Thomas Pedneault [thomas@pedneault.dev]
  */

#pragma once

#include <iostream>
#include "GLFW/glfw3.h"

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

#include "core/SystemManager.h"

namespace sc {

class GuiManager : public SystemManager {
 public:
  explicit GuiManager(GLFWwindow *window);
  virtual ~GuiManager();

  void Start() override;
  void Update() override;
  void Close() override;
 private:
  static void ConfigureIO();
  static void ConfigureStyle();

  GLFWwindow *m_Window;

  // All individual UI components should be rendered within their own function.
  void CreateViewportWindow();
  void CreateSceneWindow();
  void CreateConsoleWindow();
  void CreatePropertiesWindow();
};

};