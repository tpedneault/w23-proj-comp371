#pragma once

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "Systems/System.h"

namespace Zoom {

struct WindowSystemSpecifications
{
  U16 width, height;
  String title;
};

class Window final : public System
{
public:
  void Initialize(void* specs) override;
  void Update() override;
  void Destroy() override;

  bool IsOpen() const;
  GLFWwindow* GetWindow() const;

private:
  GLFWwindow* m_Window = nullptr;
};

};