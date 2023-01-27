#pragma once

#include "imgui.h"
#include "imgui_internal.h"
#include "backends/imgui_impl_opengl3.h"
#include "backends/imgui_impl_glfw.h"

namespace Zoom {

class Widget
{
public:
  virtual void Render() = 0;

  Widget() = default;
  virtual ~Widget() = default;
  Widget(Widget const&) = default;
  Widget(Widget&&) = default;
  Widget& operator=(Widget const&) = default;
  Widget& operator=(Widget&&) = default;
};

};