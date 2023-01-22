/**
  * @file Engine.h
  *  
  * @brief Handles the logic of the entire project. Manages all the resources and services.
  *
  * @author Thomas Pedneault [thomas@pedneault.dev]
  */

#pragma once

#include <iostream>
#include <string>
#include <sstream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <entt/entt.hpp>

#include "systems/Gui.h"

namespace sc {

class Engine {
 public:
  Engine();
  virtual ~Engine() = default;

  void Start();

 private:
  entt::registry m_Registry;
  GLFWwindow* m_Window;
  GLint m_FramebufferWidth, m_FramebufferHeight;

  // Add managers here
  GuiManager m_GuiManager;
};

};