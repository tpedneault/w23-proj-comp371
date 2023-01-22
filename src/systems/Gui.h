/**
  * @file Gui.h
  *  
  * @brief Handles the GUI for the application.
  *
  * @author Thomas Pedneault [thomas@pedneault.dev]
  */

#pragma once

#include <iostream>
#include <GLFW/glfw3.h>

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

namespace sc {

class GuiManager {
 public:
  GuiManager();
  virtual ~GuiManager();

  void Start(GLFWwindow *window);
  void Update();
  void Close();
 private:
  GLFWwindow *m_Window;

  // All individual UI components should be rendered within their own function.
  void CreateViewportWindow();
};

};